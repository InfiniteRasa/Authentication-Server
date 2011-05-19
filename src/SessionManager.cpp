#include "SessionManager.h"

SessionManager::SessionManager(unsigned int SessionTimeout)
{
	this->SessionTimeout = SessionTimeout;
}

SessionManager::~SessionManager()
{
}

unsigned long long SessionManager::GenerateSession(const char* AccountName, signed long long UID, DBManager* DB)
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
	DB->Query(query.str().c_str());
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

void SessionManager::RemoveExpiredSessions()
{
	/*
	unsigned int CurrentTime = GetTickCount();
	unsigned int index = 0;
	while (index < this->Sessions.size())
	{
		unsigned int TimeAlive = CurrentTime - this->Sessions[index].CheckTime;
		if (TimeAlive >= this->SessionTimeout)
		{
			RemoveSession(index);
		}
		else
		{
			index++;
		}
	}
	*/
}