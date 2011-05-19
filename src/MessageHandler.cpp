#include "MessageHandler.h"

void HandleMessage::ErrorAccBlocked(Player* player, CryptManager* Crypt)
{
	Packet::ErrorAccBlocked packet;
	packet.PacketLength = 0x07;
	packet.OPCode		= OPCode::AuthEAB;
	packet.ErrorID		= 0x00;

	Net::SendEncrypted(player->socket, (char*)&packet, 0x07, Crypt);
	return;
}

void HandleMessage::AuthError(Player* player, TR_BYTE ErrorCode, CryptManager* Crypt)
{
	Packet::AuthError packet;
	packet.PacketLength = 0x07;
	packet.OPCode		= OPCode::AuthE;
	packet.ErrorID		= ErrorCode;

	Net::SendEncrypted(player->socket, (char*)&packet, 0x07, Crypt);
	return;
}

void HandleMessage::AuthHello(Player* player)
{
	Packet::AuthHello packet;
	packet.PacketLength = 0x0B;
	packet.OPCode		= OPCode::AuthH;
	packet.Unknown1		= 0xDEAD0E01;
	packet.Unknown2		= 0x00;

	Net::SendPlain(player->socket, (char*)&packet, 0x0B);
	return;
}

void HandleMessage::AuthLogin(Player* player, CryptManager* Crypt, DBManager* DB, pthread_mutex_t* Mutex)
{
	Thread::LockMutex(Mutex);
	for(int i=0; i<(0x32-2)/8; i++)
	{
		Crypt->BFDecrypt((unsigned long*)&player->RecvBuffer[2+i*8], 
						 (unsigned long*)&player->RecvBuffer[2+i*8+4]);
	}

	Packet::AuthLogin packet;
	memcpy((void*)&packet, (void*)player->RecvBuffer, sizeof(Packet::AuthLogin));

	if (packet.OPCode != OPCode::AuthL)
	{ Net::Close(player->socket); Thread::UnlockMutex(Mutex); Thread::Exit(); return; }

	// Check the GameID and CDKey, both are hardcoded
	if (packet.GameID != 0x08 || packet.CDKey != 0x01)
	{ Net::Close(player->socket); Thread::UnlockMutex(Mutex); Thread::Exit(); return; }

	Crypt->TRDecrypt((unsigned char*)&packet.UserData, 30);
	memcpy((void*)player->Account,	(void*)(char*)packet.UserData,    14);
	memcpy((void*)player->Password, (void*)((char*)packet.UserData+14), 16);

	int LoginOK = DB->ValidatePlayer((char*)player->Account, 
									  Crypt->GenMD5((char*)player->Password, strlen(player->Password)).c_str(), &player->AccUID);
	Thread::UnlockMutex(Mutex);

	switch (LoginOK)
	{
		case -1: // Account not found
			HandleMessage::AuthError(player, AuthError::INVALID_PASSWORD, Crypt);
			Net::Close(player->socket); Thread::Exit(); return;
			break;
		case 0:
			break;
		case 1: // Account blocked
			HandleMessage::ErrorAccBlocked(player, Crypt);
			Net::Close(player->socket); Thread::Exit(); return;
			break;
		case 2: // Account already logged
			HandleMessage::AuthError(player, AuthError::ALREADY_LOGGED_IN, Crypt);
			Net::Close(player->socket); Thread::Exit(); return;
			break;
	}
	// Logged
	return;
}

void HandleMessage::AuthLoginOk(Player* player, CryptManager* Crypt)
{
	// related to subscription, need info
	Packet::AuthLoginOk packet;
	packet.PacketLength = 0x28;
	packet.OPCode		= OPCode::AuthLO;
	packet.Unknown1		= 0x00;
	packet.Unknown2		= 0x00;
	packet.Unknown3		= 0x00;
	packet.Unknown4		= 0x00;
	packet.Unknown5		= 0x00;
	packet.Unknown6		= 0x00;
	packet.Unknown7		= 0x00;
	packet.Unknown8		= 0x00;
	packet.Unknown9		= 0x00;
	packet.Unknown10	= 0x00;

	Net::SendEncrypted(player->socket, (char*)&packet, 0x28, Crypt);
	return;
}

void HandleMessage::AuthRequestServerList(Player* player, pthread_mutex_t* Mutex)
{
		Thread::LockMutex(Mutex);
		Packet::AuthRequestServerList packet;
		memcpy((void*)&packet, (void*)player->RecvBuffer, sizeof(Packet::AuthRequestServerList));

		if (packet.OPCode != OPCode::AuthRSL)
		{ Net::Close(player->socket); Thread::UnlockMutex(Mutex); Thread::Exit(); return; }
		Thread::UnlockMutex(Mutex);
		// Add something here? 
		return;
}

void HandleMessage::AuthServerListEx(Player* player, CryptManager* Crypt, DBManager* DB, pthread_mutex_t* Mutex)
{
	Thread::LockMutex(Mutex);
	MYSQL_ROW row;
	DB->Query("SELECT * FROM `game_servers`");
	MYSQL_RES* result = DB->StoreResult();
	unsigned char NumberOfServers = (unsigned char)DB->NumRows(result);
	char* buffer;
	buffer = (char*)malloc(sizeof(Packet::AuthServerListEx) + (sizeof(Packet::SLServer) * NumberOfServers));
	Packet::AuthServerListEx* packet = (Packet::AuthServerListEx*)buffer;
	packet->PacketLength				= 0xFF;
	packet->OPCode						= OPCode::AuthSLE;
	packet->ServerCount					= NumberOfServers;
	packet->LastServerID				= 0x35;
	
	if (NumberOfServers > 0)
	{
		for (int i=0; i<packet->ServerCount; i++)
		{
			Packet::SLServer* server = (Packet::SLServer*)(buffer + sizeof(Packet::AuthServerListEx) + (sizeof(Packet::SLServer) * i));
			row = DB->FetchRow(result);
			server->ServerID			= (unsigned char)atoi(row[0]);
			server->Host				= strtoul(row[1],NULL,10);
			server->Port				= atoi(row[2]);
			server->AgeLimit			= (unsigned char)atoi(row[3]);
			server->PKFlag				= (unsigned char)atoi(row[4]);
			server->CurrentUserCount	= (unsigned short)atoi(row[5]);
			server->MaxUserCount		= (unsigned short)atoi(row[6]);
			server->ServerStatus		= (unsigned char)atoi(row[7]);
		}
	}
	Thread::UnlockMutex(Mutex);
	Net::SendEncrypted(player->socket, buffer, sizeof(Packet::AuthServerListEx) + (sizeof(Packet::SLServer) * NumberOfServers), Crypt);
	free(buffer);
	return;
}

unsigned char HandleMessage::AuthSelectServer(Player* player, pthread_mutex_t* Mutex)
{
	Thread::LockMutex(Mutex);
	Packet::AuthSelectServer packet;
	memcpy((void*)&packet, (void*)player->RecvBuffer, sizeof(Packet::AuthSelectServer));
	Thread::UnlockMutex(Mutex);
	if (packet.OPCode != OPCode::AuthSS)
	{ Net::Close(player->socket); Thread::UnlockMutex(Mutex); Thread::Exit(); return -1; }
	// Something more?
	return (unsigned char)packet.ServerID;
}

void HandleMessage::LastPacket(Player* player, unsigned char ServerID, CryptManager* Crypt, SessionManager* Sessions, DBManager* DB, pthread_mutex_t* Mutex)
{
	Thread::LockMutex(Mutex);
	unsigned long long sessionID = Sessions->GenerateSession(player->Account, player->AccUID, DB);
	Packet::LastPacket packet;
	packet.PacketLength = 0x0C;
	packet.OPCode = OPCode::AuthLP;
	packet.SessionID1 = (unsigned int)(sessionID & 0xFFFFFFFF);
	packet.SessionID2 = (unsigned int)(sessionID >> 32);
	packet.ServerID = ServerID;	
	Thread::UnlockMutex(Mutex);
	Net::SendEncrypted(player->socket, (char*)&packet, 0xC, Crypt);
	return;
}