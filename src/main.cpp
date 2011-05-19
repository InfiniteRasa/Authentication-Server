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
pthread_mutex_t Mutex;

DBManager*		DB;
CryptManager*	Crypt;
SessionManager* Sessions;

unsigned int PlayersPort;
unsigned int ServersPort;

void* ServersThread(void* Parameter);
void* PlayersThread(void* Parameter);
void* PlayerHandling(void* Parameter);
void* ServersHandling(void* Parameter);

int main()
{
	printf(" ==============================================================================\r\n");
	printf("                                 Infinite Rasa                                 \r\n");
	printf("                             Authentication Server                             \r\n\r\n");
	printf("  Version 0.3                                         http://infiniterasa.com/ \r\n");
	printf(" ==============================================================================\r\n");
	printf("Loading...\r\n");

#ifdef _WIN32
	WSADATA Winsock;
	WSAStartup(MAKEWORD(2,2), &Winsock);
#endif

	Thread::InitMutex(&Mutex);

	printf("Reading configuration file...\r\n\r\n");
	INIParser* Parser = new INIParser("config.ini");

	PlayersPort = Parser->GetInt("Auth Server", "PlayersPort", 2106);
	ServersPort = Parser->GetInt("Auth Server", "ServersPort", 9887);
	printf("Authentication port: %i\r\n", PlayersPort);
	printf("Game Servers port:   %i\r\n\r\n", ServersPort);

	std::string dbhost	= Parser->GetString("Database",	"host",		"localhost");
	unsigned int dbport = Parser->GetInt("Database",	"port",		10061);
	std::string dbuser	= Parser->GetString("Database",	"user",		"root");
	std::string dbpass	= Parser->GetString("Database",	"password", "usbw");
	std::string dbname	= Parser->GetString("Database",	"name",		"test");

	printf("Database Host: %s\r\n", dbhost.c_str());
	printf("Database Port: %u\r\n", dbport);
	printf("Database User: %s\r\n", dbuser.c_str());
	printf("Database Pass: %s\r\n", dbpass.c_str());
	printf("Database Name: %s\r\n\r\n", dbname.c_str());

	printf("Loading Database Manager...");
	DB = new DBManager(dbhost.c_str(), dbport, dbuser.c_str(), dbpass.c_str(), dbname.c_str());
	printf("Done\r\n");

	printf("Loading Sessions Manager...");
	Sessions = new SessionManager();
	printf("Done\r\n");

	printf("Loading Cryptography Manager...");
	Crypt = new CryptManager();
	printf("Done\r\n\r\n");

	printf("Creating Threads...");

	pthread_t PlayersThreadID, ServersThreadID;
	if (Thread::New(&PlayersThreadID, PlayersThread, NULL) && 
		Thread::New(&ServersThreadID, ServersThread, NULL))
	{ printf("Done\r\n\r\n"); } else { printf("Error\r\n\r\n"); }

	printf("Authentication Server running\r\n");
	printf("Type q to close the server\r\n");
	char c;
	while(ServerRunning)
	{
		c = getchar();
		if (c == 'q')
		{
			Thread::LockMutex(&Mutex);
			ServerRunning = false;
			Thread::UnlockMutex(&Mutex);
		}
	}
	printf("Finishing threads...");
	Thread::Join(ServersThreadID);
	Thread::Join(PlayersThreadID);
	printf("Done\r\n");
	printf("Exiting Server...");
	return 0;
}

void* PlayersThread(void* Parameter)
{
	NetManager* NetMgr = new NetManager(PlayersPort);
	while(ServerRunning)
	{
		NetMgr->ResetFD();
		SOCKET NewClient = NetMgr->WaitForClient();
		if (NewClient != -1)
		{
			printf("New Player: ");
			Net::PrintIP(Net::NumericIP(NewClient));
			printf("\r\n");
			pthread_t ThreadID; // save this? nah
			if (!Thread::New(&ThreadID, PlayerHandling, (void*)NewClient))
			{
				printf("Error creating Thread for player handling\r\n");
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
	{ Net::Close(player.socket); Thread::Exit(); return 0; }
	HandleMessage::AuthLogin(&player, Crypt, DB, &Mutex);
	HandleMessage::AuthLoginOk(&player, Crypt);
	// This part is the <different packets allowed>
	int start = GetTickCount();
	unsigned char ServerID;
	while (1)
	{ 
		if ((GetTickCount() - start) > (10*1000))
		{ 
			HandleMessage::AuthError(&player, AuthError::KICKED, Crypt);
			Net::Close(player.socket); Thread::Exit(); return 0; 
		}
		if (Net::Receive(player.socket, (char*)player.RecvBuffer, 0x1A, true) > 0)
		{
			if (*(unsigned short*)player.RecvBuffer != 0x1A)
			{ Net::Close(player.socket); Thread::Exit(); return 0; }
			for(int i=0; i<(0x1A-2)/8; i++)
			{
				Crypt->BFDecrypt((unsigned long*)&player.RecvBuffer[2+i*8], 
								 (unsigned long*)&player.RecvBuffer[2+i*8+4]);
			}
			if (player.RecvBuffer[2] == OPCode::AuthRSL)
			{
					start = GetTickCount(); // Reset timeout
					HandleMessage::AuthRequestServerList(&player, &Mutex);
					HandleMessage::AuthServerListEx(&player, Crypt, DB, &Mutex);
			}
			if (player.RecvBuffer[2] == OPCode::AuthSS)
			{
				ServerID = HandleMessage::AuthSelectServer(&player, &Mutex);
				if (ServerID > 0)
				{
					HandleMessage::LastPacket(&player, ServerID, Crypt, Sessions, DB, &Mutex);
					break;
				}
			}
		}
	}
	printf("Bye Player: "); Net::PrintIP(Net::NumericIP(player.socket)); printf("\r\n");
	Thread::Exit();
	return 0;
}

void* ServersThread(void* Parameter)
{
	// ToDo
	// All this
	Thread::Exit();
	return 0;
}
