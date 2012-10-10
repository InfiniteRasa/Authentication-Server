#include <stdio.h>
#include "ThreadsUtils.h"
#include "INIParser.h"
#include "NetManager.h"
#include "NetUtils.h"
#include "MessageHandler.h"
#include "DBManager.h"
#include "SessionManager.h"
#include "CryptManager.h"

bool ServerRunning = true;

pthread_mutex_t gMutex;

unsigned int Port;
unsigned int MaxClients;
unsigned int AcceptedLogins;

void* MaintenanceThread(void* Parameter);
void* PlayersThread(void* Parameter);
void* PlayerHandling(void* Parameter);
unsigned int ClientsNow();

int main()
{
	printf(" ==============================================================================\r\n");
	printf("                                  Tabula Rasa                                  \r\n");
	printf("                             Authentication Server                             \r\n\r\n");
	printf("  Version 0.4.1                                                     Salsa Crew \r\n");
	printf(" ==============================================================================\r\n");
	printf("Loading...\r\n");

#ifdef _WIN32
	WSADATA Winsock;
	WSAStartup(MAKEWORD(2,2), &Winsock);
#endif

	Thread::InitMutex();

	printf("Reading configuration file...\r\n\r\n");
	INIParser* Parser = new INIParser("config.ini");

	Port = Parser->GetInt("Auth Server", "port", 2106);
	printf("Authentication port: %i\r\n", Port);

	MaxClients = Parser->GetInt("Auth Server", "maxclients", 25);
	printf("Allowed simultaneous clients: %i\r\n", MaxClients);

	unsigned int sessiontimeout = Parser->GetInt("Auth Server",	"sessiontimeout", 50);
	printf("Time before sessions expire: %i\r\n", sessiontimeout);
	unsigned int servertimeout = Parser->GetInt("Auth Server",	"servertimeout", 120);
	printf("Time before servers expire: %i\r\n\r\n", servertimeout);

	std::string dbhost	= Parser->GetString("Auth Server Database",	"host",		"localhost");
	unsigned int dbport = Parser->GetInt("Auth Server Database",	"port",		10061);
	std::string dbname	= Parser->GetString("Auth Server Database",	"name",		"ir_authentication");
	std::string dbuser	= Parser->GetString("Auth Server Database",	"user",		"root");
	std::string dbpass	= Parser->GetString("Auth Server Database",	"password", "usbw");

	printf("Database Host: %s\r\n", dbhost.c_str());
	printf("Database Port: %u\r\n", dbport);
	printf("Database Name: %s\r\n\r\n", dbname.c_str());
	printf("Database User: %s\r\n", dbuser.c_str());
	printf("Database Pass: %s\r\n", dbpass.c_str());
	
	printf("Loading Database Manager...");
	DBManager::Create(dbhost.c_str(), dbport, dbuser.c_str(), dbpass.c_str(), dbname.c_str());
	printf("Done\r\n");

	printf("Loading Sessions Manager...");
	SessionManager::Create(sessiontimeout, servertimeout);
	printf("Done\r\n");

	printf("Loading Cryptography Manager...");
	CryptManager::Create();
	printf("Done\r\n\r\n");

	printf("Deleting old sessions...");
	SessionManager::Instance()->WipeSessions();
	printf("Done\r\n");
	printf("Deleting old servers...");
	SessionManager::Instance()->WipeServers();
	printf("Done\r\n\r\n");

	AcceptedLogins = 0;

	printf("Creating Threads...");

	pthread_t PlayersThreadID, MaintenanceThreadID;
	if (Thread::New(&PlayersThreadID, PlayersThread, NULL) && 
		Thread::New(&MaintenanceThreadID, MaintenanceThread, NULL))
	{ printf("Done\r\n\r\n"); } else { printf("Error\r\n\r\n"); }

	printf("Authentication Server running\r\n");
	printf("Type q to close the server\r\n");
	char c;
	while(ServerRunning)
	{
		c = getchar();
		if (c == 'q')
		{
			Thread::LockMutex();
			ServerRunning = false;
			Thread::UnlockMutex();
		}
	}
	printf("Finishing threads...");
	Thread::Join(MaintenanceThreadID);
	Thread::Join(PlayersThreadID);
	printf("Done\r\n");
	printf("Exiting Server...");
	return 0;
}

void* PlayersThread(void* Parameter)
{
	NetManager* NetMgr = new NetManager(Port);
	while(ServerRunning)
	{
		NetMgr->ResetFD();
		SOCKET NewClient = NetMgr->WaitForClient();
		if (NewClient != -1)
		{
			AcceptedLogins++;
			printf("Login %u: ", AcceptedLogins);
			Net::PrintIP(Net::NumericIP(NewClient));
			printf("\r\n");
			if (ClientsNow() < MaxClients)
			{
				pthread_t ThreadID; // save this? nah
				if (!Thread::New(&ThreadID, PlayerHandling, (void*)NewClient))
				{
					printf("Error creating Thread for player handling\r\n");
					Net::Close(NewClient);
				}
			}
			else
			{
				printf("Clients limit reached: %u vs %u\r\n", ClientsNow(), MaxClients);
				Net::Close(NewClient);
			}
		}
		Sleep(100);
	}
	Thread::Exit();
	return 0;
}

void* PlayerHandling(void* Parameter)
{
	Player player;
	player.socket = (SOCKET)Parameter;
	Net::SetTimeout(player.socket, 3); // 3 seconds of timeout for each recv

	HandleMessage::AuthHello(&player);
	if (Net::Receive(player.socket, (char*)player.RecvBuffer, 0x32, true) < 1)
	{ 
		printf("Error receiving AuthLogin packet\r\n");
		int ret = WSAGetLastError();
		printf("WSA Last Error: %i\r\n", ret);
		Net::Close(player.socket); Thread::Exit(); return 0; 
	}
	HandleMessage::AuthLogin(&player);
	HandleMessage::AuthLoginOk(&player);
	// This part is the <different packets allowed>
	int start = GetTickCount();
	unsigned char ServerID;
	while (1)
	{ 
		if ((GetTickCount() - start) > (10*1000))
		{ 
			HandleMessage::AuthError(&player, AuthError::KICKED);
			printf("Time limit reached, kicking\r\n");
			Net::Close(player.socket); Thread::Exit(); return 0; 
		}
		if (Net::Receive(player.socket, (char*)player.RecvBuffer, 0x1A, true) > 0)
		{
			if (*(unsigned short*)player.RecvBuffer != 0x1A)
			{ 
				printf("Error receiving Server request\r\n");
				Net::Close(player.socket); Thread::Exit(); return 0; 
			}
			for(int i=0; i<(0x1A-2)/8; i++)
			{
				CryptManager::Instance()->BFDecrypt((unsigned long*)&player.RecvBuffer[2+i*8], 
								 (unsigned long*)&player.RecvBuffer[2+i*8+4]);
			}
			if (player.RecvBuffer[2] == OPCode::AuthRSL)
			{
					start = GetTickCount(); // Reset timeout
					HandleMessage::AuthRequestServerList(&player);
					HandleMessage::AuthServerListEx(&player);
			}
			if (player.RecvBuffer[2] == OPCode::AuthSS)
			{
				ServerID = HandleMessage::AuthSelectServer(&player);
				if (ServerID > 0)
				{
					HandleMessage::LastPacket(&player, ServerID);
					break;
				}
			}
		}
	}
	printf("Connection Closed: "); Net::PrintIP(Net::NumericIP(player.socket)); printf("\r\n");
	Thread::Exit();
	return 0;
}

void* MaintenanceThread(void* Parameter)
{
	unsigned int SessionTimeout = SessionManager::Instance()->SessionTimeout;
	unsigned int ServerTimeout = SessionManager::Instance()->ServerTimeout;

	// This loop makes a lot of not useful calls to the DB
	while(ServerRunning)
	{		
		SessionManager::Instance()->RemoveExpiredSessions();
		SessionManager::Instance()->RemoveExpiredServers();
		Sleep(SessionTimeout * 500);
	}
	Thread::Exit();
	return 0;
}

unsigned int ClientsNow()
{
	return Thread::Count() - 3; // - 3 with the maintenance thread running
}
