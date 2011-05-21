#include "SessionManager.h"

SessionManager* SessionManager::Pointer = 0;

SessionManager* SessionManager::Instance()
{
	return SessionManager::Pointer;
}

SessionManager* SessionManager::Create(unsigned int SessionTimeout, unsigned int ServerTimeout)
{
	if (SessionManager::Pointer == 0)
	{
		SessionManager::Pointer = new SessionManager(SessionTimeout, ServerTimeout);
	}
	return SessionManager::Pointer;
}

SessionManager::SessionManager(unsigned int SessionTimeout, unsigned int ServerTimeout)
{
	this->SessionTimeout = SessionTimeout;
	this->ServerTimeout = ServerTimeout;
}

SessionManager::~SessionManager()
{
}

unsigned long long SessionManager::GenerateSession(const char* AccountName, signed long long UID)
{
	unsigned long long SessionID;
	unsigned int SessionID1;
	unsigned int SessionID2;
	SessionID = GenerateUniqueKey();
	SessionID1 = (unsigned int)(SessionID & 0xFFFFFFFF);
	SessionID2 = (unsigned int)(SessionID >> 32);
	std::stringstream converter;
	std::stringstream query;
	std::string sSessionID1;
	std::string sSessionID2;
	std::string sUID;
	converter << SessionID1; converter >> sSessionID1; converter.clear();
	converter << SessionID2; converter >> sSessionID2; converter.clear();
	converter << UID; converter >> sUID; converter.clear();
	query << "INSERT INTO sessions (session_id1, session_id2, uid, account, checktime) VALUES(";
	query << sSessionID1 << ",";
	query << sSessionID2 << ",";
	query << sUID << ",";
	query << "'" << std::string(AccountName) << "',";
	query << "NULL" << ")";
	DBManager::Instance()->Query(query.str().c_str());
	// ToDo: Error Checking
	return SessionID;
}

unsigned long long SessionManager::GenerateUniqueKey()
{
	unsigned long long Key;
	
	unsigned int GenTime = GetTickCount();
	Key = rand() + GenTime;
	for (int i=0; i<30; i++)
	{
		Key = (Key<<2) | (Key>>62);
		Key += rand();
		Key += GenTime / (i+1);
	}

	return Key;
}

void SessionManager::WipeSessions()
{
	Thread::LockMutex();
	DBManager::Instance()->Query("DELETE FROM sessions");
	Thread::UnlockMutex();
}

void SessionManager::WipeServers()
{
	Thread::LockMutex();
	DBManager::Instance()->Query("DELETE FROM game_servers WHERE static='0'");
	Thread::UnlockMutex();
}

void SessionManager::RemoveExpiredSessions()
{
	std::stringstream converter;
	std::string Timeout;
	converter << SessionManager::SessionTimeout; converter >> Timeout; converter.clear();

	std::string Query = std::string("");
	Query += "DELETE FROM sessions WHERE (TIMESTAMPDIFF(SECOND, checktime,CURRENT_TIMESTAMP())) > ";
	Query += Timeout;
	Thread::LockMutex();
	DBManager::Instance()->Query(Query.c_str());
	Thread::UnlockMutex();
}

void SessionManager::RemoveExpiredServers()
{
	std::stringstream converter;
	std::string Timeout;
	converter << SessionManager::ServerTimeout; converter >> Timeout; converter.clear();

	std::string Query = std::string("");
	Query += "DELETE FROM game_servers WHERE (TIMESTAMPDIFF(SECOND, check_time, CURRENT_TIMESTAMP())) > ";
	Query += Timeout;
	Thread::LockMutex();
	DBManager::Instance()->Query(Query.c_str());
	Thread::UnlockMutex();
}

// DELETE FROM sessions WHERE checktime > (CURRENT_TIMESTAMP() - 50)