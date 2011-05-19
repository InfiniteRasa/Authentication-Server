To run it on Windows:
	- Setup a MySQL database (i use usbwebserver)
	- Import the bin/auth.sql file
	- Modify the bin/config.ini file to fit your configuration
	- Open AuthServer.exe
	- Open Tabula Rasa client
	- Log in as manolo/manolo (lol)
	- Nothing more without a game server

==================================

Classes/Namespaces explanation:

DBManager - Handles the DB connection and querys, also validates players
Cryptmanager - Contains the Blowfish and custom algorithms functions
SessionManager - Handles the generation and deletion of sessions
INIParser - parses the ini file lol
NetManager - along NetUtils, abstracts socket functions for corssplatfom work
ThreadUtils - Simplifies threads usage
MessageHandler - All the specific logic goes here, handles all the packets
NetObjects - Simplifies the opcode, packet and errors usage

==================================

To compile in Windows (at least in MSVC):
-------------------------------------------
Include folders:
	.\pthreads\include
	.\mysql
-------------------------------------------
Lib folders:
	.\mysql
	.\pthreads\lib
-------------------------------------------
Libs
	libmysql.lib 
	ws2_32.lib 
	pthreadVC2.lib
-------------------------------------------
Preprocessor:
	_CRT_SECURE_NO_WARNINGS
	INI_ANSIONLY
	_TCHAR_DEFINED
	
==================================

There is some support for Linux,
but havent tried to compile it.

==================================

ToDo:
	- Servers Thread
		- Delete expired sessions
		- Delete expired servers
	- Check comments to find more

Note:
	The ip field from the game_servers table must be little endian

http://infiniterasa.com/