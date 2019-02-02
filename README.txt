To run it:
	- Generate solution/makefiles with premake5
	- Setup a MySQL database
	- Import the sql/auth.sql file
	- Modify the config.ini file to fit your configuration
	- Launch irauth executable
	- Open Tabula Rasa client
	- Log in as test/test
	- ??????

	Note for Linux:
	- Install (default-)libmysqlclient-dev
	- Run `mysql_config --cflags` and `mysql_config --libs` to find relevant folders
	- Tested in Debian Stretch
	
==================================

Classes/Namespaces explanation:

DBManager      - Handles the DB connection and querys, also validates players
Cryptmanager   - Contains the Blowfish and custom algorithms functions
SessionManager - Handles the generation and deletion of sessions
INIParser      - Parses the ini file
NetManager     - along NetUtils, abstracts socket functions for crossplatfom work
ThreadUtils    - Simplifies threads usage
MessageHandler - All the specific logic goes here, handles all the packets
NetObjects     - Simplifies the opcode, packet and errors usage

==================================

ToDo:
	- Check birthday and server age limit
	- Maybe commands/interface in the main thread
	- Comments
	
Love, Salsa Crew
