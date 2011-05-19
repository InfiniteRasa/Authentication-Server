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
	void ErrorAccBlocked(Player* player, CryptManager* Crypt);												// By Server
	void AuthError(Player* player, TR_BYTE ErrorCode, CryptManager* Crypt);									// By Server
	void AuthHello(Player* player);																			// By Server
	void AuthLogin(Player* player, CryptManager* Crypt, DBManager* DB, pthread_mutex_t* Mutex);				// By Client
	void AuthLoginOk(Player* player, CryptManager* Crypt);													// By Server
	void AuthRequestServerList(Player* player, pthread_mutex_t* Mutex);										// By Client
	void AuthServerListEx(Player* player, CryptManager* Crypt, DBManager* DB, pthread_mutex_t* Mutex);		// By Server
	unsigned char AuthSelectServer(Player* player, pthread_mutex_t* Mutex);									// By Client 
	void LastPacket(Player* player, unsigned char ServerID, CryptManager* Crypt, SessionManager* Sessions, DBManager* DB, pthread_mutex_t* Mutex);	// By Server
}

#endif