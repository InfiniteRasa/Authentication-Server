// ToDo
// Add IP to sessions for checking
// Maybe change struct for class
#pragma once

#ifdef _WIN32
	#include <windows.h>
#endif
#include <math.h>
#include <stdio.h>
#include <sstream>
#include <string>
#include "DBManager.h"
#include "ThreadsUtils.h"

class SessionManager
{
	public:
		static SessionManager* Instance();
		static SessionManager* Create(unsigned int SessionTimeout, unsigned int ServerTimeout);
		
		~SessionManager();

		unsigned long long GenerateSession(const char* AccountName, signed long long UID);
		void WipeSessions();
		void WipeServers();
		void RemoveExpiredSessions();
		void RemoveExpiredServers();

		unsigned int SessionTimeout;
		unsigned int ServerTimeout;

	protected:
		SessionManager(unsigned int SessionTimeout, unsigned int ServerTimeout);

	private:
		static SessionManager* Pointer;

		unsigned long long GenerateUniqueKey();
};


