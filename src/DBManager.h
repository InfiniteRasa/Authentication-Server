#ifndef TR_DB_MANAGER_H
#define TR_DB_MANAGER_H

#include <stdio.h>
#include <string>
#ifdef _WIN32
	#include <windows.h>
#endif
#include <mysql.h>

class DBManager
{
	public:
		DBManager(const char* dbHost, unsigned int dbPort, const char* dbUser, const char* dbPass, const char* dbName);
		~DBManager();

		bool Query(const char* query);
		MYSQL_RES* StoreResult();
		int NumRows(MYSQL_RES* result);
		MYSQL_ROW FetchRow(MYSQL_RES* result);
		void FreeResult(MYSQL_RES* result);
		int ValidatePlayer(const char* Name, const char* Password, signed long long* UID);

	private:
		MYSQL*				dbHandle;
		std::string			dbHost;
		unsigned int		dbPort;
		std::string			dbUser;
		std::string			dbName;
		std::string			dbPass;
		std::string			UsersTable;
};
#endif