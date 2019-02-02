#pragma once

#include <stdio.h>
#include <string>
#ifdef _WIN32
	#include <windows.h>
#else
	#include <stdlib.h>
#endif
#include <mysql.h>

#include "ThreadsUtils.h"

class DBManager
{
	public:
		static DBManager* Instance();
		static DBManager* Create(const char* dbHost, unsigned int dbPort, const char* dbUser, const char* dbPass, const char* dbName);
		
		~DBManager();

		bool Query(const char* query);
		MYSQL_RES* StoreResult();
		int NumRows(MYSQL_RES* result);
		MYSQL_ROW FetchRow(MYSQL_RES* result);
		void FreeResult(MYSQL_RES* result);
		int ValidatePlayer(const char* Name, const char* Password, signed long long* UID);

	protected:
		DBManager(const char* dbHost, unsigned int dbPort, const char* dbUser, const char* dbPass, const char* dbName);

	private:
		static DBManager* Pointer;

		MYSQL*				dbHandle;
		std::string			dbHost;
		unsigned int		dbPort;
		std::string			dbUser;
		std::string			dbName;
		std::string			dbPass;
		std::string			UsersTable;
};
