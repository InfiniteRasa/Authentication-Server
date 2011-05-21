#ifndef TR_MESSAGES_H
#define TR_MESSAGES_H

#include <vector>
#include "ThreadsUtils.h"
#include "NetUtils.h"
#include "NetObjects.h"
#include "DBManager.h"
#include "SessionManager.h"
#include "CryptManager.h"

namespace HandleMessage
{
	void ErrorAccBlocked(Player* player);						// By Server
	void AuthError(Player* player, TR_BYTE ErrorCode);			// By Server
	void AuthHello(Player* player);								// By Server
	void AuthLogin(Player* player);								// By Client
	void AuthLoginOk(Player* player);							// By Server
	void AuthRequestServerList(Player* player);					// By Client
	void AuthServerListEx(Player* player);						// By Server
	unsigned char AuthSelectServer(Player* player);				// By Client 
	void LastPacket(Player* player, unsigned char ServerID);	// By Server
}

#endif