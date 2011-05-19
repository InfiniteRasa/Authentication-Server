// ToDo
// Add IP to sessions for checking
// Maybe change struct for class
// Maybe move SESSION_TIMEOUT for dynamic assignation

#ifndef TR_SESSION_MANAGER_H
#define TR_SESSION_MANAGER_H

#ifdef _WIN32
	#include <windows.h>
#endif
#include <math.h>
#include <stdio.h>
#include <sstream>
#include <string>
#include "DBManager.h"

struct SESSION
{
	union
	{
		struct
		{
			unsigned int SessionID1;
			unsigned int SessionID2;
		};
		unsigned long long SessionID;
	};
	union
	{
		struct
		{
		unsigned int UID1;
		unsigned int UID2;
		};
		signed long long UID;
	};
	std::string AccountName;
	unsigned int CheckTime;
};

class SessionManager
{
	public:
		SessionManager(unsigned int SessionTimeout = 50000);
		~SessionManager();

		unsigned long long GenerateSession(const char* AccountName, signed long long UID, DBManager* DB);

	private:
		unsigned int SessionTimeout;

		unsigned long long GenerateUniqueKey();
		void RemoveExpiredSessions();
};

#endif
