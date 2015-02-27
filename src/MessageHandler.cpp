#include "MessageHandler.h"

void HandleMessage::ErrorAccBlocked(Player* player)
{
	Packet::ErrorAccBlocked packet;
	packet.PacketLength = 0x07;
	packet.OPCode		= OPCode::AuthEAB;
	packet.ErrorID		= 0x00;

	Net::SendEncrypted(player->socket, (char*)&packet, 0x07);
	return;
}

void HandleMessage::AuthError(Player* player, TR_BYTE ErrorCode)
{
	Packet::AuthError packet;
	packet.PacketLength = 0x07;
	packet.OPCode		= OPCode::AuthE;
	packet.ErrorID		= ErrorCode;

	Net::SendEncrypted(player->socket, (char*)&packet, 0x07);
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

void HandleMessage::AuthLogin(Player* player)
{
	Thread::LockMutex();
	for(int i=0; i<(0x32-2)/8; i++)
	{
		CryptManager::Instance()->BFDecrypt((unsigned long*)&player->RecvBuffer[2+i*8], 
						 (unsigned long*)&player->RecvBuffer[2+i*8+4]);
	}

	Packet::AuthLogin packet;
	memcpy((void*)&packet, (void*)player->RecvBuffer, sizeof(Packet::AuthLogin));

	if (packet.OPCode != OPCode::AuthL)
	{ Net::Close(player->socket); Thread::UnlockMutex(); Thread::Exit(); return; }

	// Check the GameID and CDKey, both are hardcoded
	if (packet.GameID != 0x08 || packet.CDKey != 0x01)
	{ Net::Close(player->socket); Thread::UnlockMutex(); Thread::Exit(); return; }

	CryptManager::Instance()->TRDecrypt((unsigned char*)&packet.UserData, 30);
	memcpy((void*)player->Account,	(void*)(char*)packet.UserData,    14);
	memcpy((void*)player->Password, (void*)((char*)packet.UserData+14), 16);

	int LoginOK = DBManager::Instance()->ValidatePlayer((char*)player->Account, 
									  CryptManager::Instance()->GenMD5((char*)player->Password, strlen(player->Password)).c_str(), &player->AccUID);
	Thread::UnlockMutex();

	switch (LoginOK)
	{
		case -1: // Account not found
			printf("Account not found: %s\n", player->Account);
			HandleMessage::AuthError(player, AuthError::INVALID_PASSWORD);
			Net::Close(player->socket); Thread::Exit(); return;
			break;
		case 0:
			break;
		case 1: // Account blocked
			printf("Account blocked: %s\n", player->Account);
			HandleMessage::ErrorAccBlocked(player);
			Net::Close(player->socket); Thread::Exit(); return;
			break;
		case 2: // Account already logged
			printf("Account already logged: %s\n", player->Account);
			HandleMessage::AuthError(player, AuthError::ALREADY_LOGGED_IN);
			Net::Close(player->socket); Thread::Exit(); return;
			break;
	}
	// Logged
	return;
}

void HandleMessage::AuthLoginOk(Player* player)
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

	Net::SendEncrypted(player->socket, (char*)&packet, 0x28);
	return;
}

void HandleMessage::AuthRequestServerList(Player* player)
{
		Thread::LockMutex();
		Packet::AuthRequestServerList packet;
		memcpy((void*)&packet, (void*)player->RecvBuffer, sizeof(Packet::AuthRequestServerList));

		if (packet.OPCode != OPCode::AuthRSL)
		{ Net::Close(player->socket); Thread::UnlockMutex(); Thread::Exit(); return; }
		Thread::UnlockMutex();
		// Add something here? 
		return;
}

void HandleMessage::AuthServerListEx(Player* player)
{
	Thread::LockMutex();
	MYSQL_ROW row;
	DBManager::Instance()->Query("SELECT * FROM `game_servers`");
	MYSQL_RES* result = DBManager::Instance()->StoreResult();
	unsigned char NumberOfServers = (unsigned char)DBManager::Instance()->NumRows(result);
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
			row = DBManager::Instance()->FetchRow(result);
			server->ServerID			= (unsigned char)atoi(row[0]);
			server->Host				= Net::IPtoHex(row[1]);
			server->Port				= atoi(row[2]);
			server->AgeLimit			= (unsigned char)atoi(row[3]);
			server->PKFlag				= (unsigned char)atoi(row[4]);
			server->CurrentUserCount	= (unsigned short)atoi(row[5]);
			server->MaxUserCount		= (unsigned short)atoi(row[6]);
			server->ServerStatus		= (unsigned char)atoi(row[7]);
		}
	}
	Thread::UnlockMutex();
	Net::SendEncrypted(player->socket, buffer, sizeof(Packet::AuthServerListEx) + (sizeof(Packet::SLServer) * NumberOfServers));
	free(buffer);
	return;
}

unsigned char HandleMessage::AuthSelectServer(Player* player)
{
	Thread::LockMutex();
	Packet::AuthSelectServer packet;
	memcpy((void*)&packet, (void*)player->RecvBuffer, sizeof(Packet::AuthSelectServer));
	Thread::UnlockMutex();
	if (packet.OPCode != OPCode::AuthSS)
	{ Net::Close(player->socket); Thread::UnlockMutex(); Thread::Exit(); return -1; }
	// Something more?
	return (unsigned char)packet.ServerID;
}

void HandleMessage::LastPacket(Player* player, unsigned char ServerID)
{
	Thread::LockMutex();
	unsigned long long sessionID = SessionManager::Instance()->GenerateSession(player->Account, player->AccUID);
	Packet::LastPacket packet;
	packet.PacketLength = 0x0C;
	packet.OPCode = OPCode::AuthLP;
	packet.SessionID1 = (unsigned int)(sessionID & 0xFFFFFFFF);
	packet.SessionID2 = (unsigned int)(sessionID >> 32);
	packet.ServerID = ServerID;	
	Thread::UnlockMutex();
	Net::SendEncrypted(player->socket, (char*)&packet, 0xC);
	return;
}