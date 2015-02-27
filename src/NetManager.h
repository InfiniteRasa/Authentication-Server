#ifndef TR_NET_MANAGER_H
#define TR_NET_MANAGER_H

#ifdef _WIN32
	#include <winsock2.h>
#else
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <sys/select.h>
	#include <netinet/in.h>
	
	#define SOCKET_ERROR -1
	typedef unsigned int SOCKET;
	typedef sockaddr_in SOCKADDR_IN;
	typedef sockaddr SOCKADDR;
	typedef fd_set FD_SET;
#endif
#include <stdio.h>
#include "NetObjects.h"
#include "NetUtils.h"
#include "ThreadsUtils.h"

class NetManager
{
	public:
		NetManager(unsigned int Port);
		~NetManager();

		void ResetFD();
		SOCKET WaitForClient();

	private:
		unsigned int Port;
		SOCKET Socket;
		FD_SET fd;
		timeval Timeout;

		SOCKET CreateSocket(unsigned short Port);

};

#endif