#include "NetManager.h"


NetManager::NetManager(unsigned int Port)
{
	this->Port = Port;
	this->Socket = CreateSocket(this->Port);
	if (this->Socket == SOCKET_ERROR)
	{
		printf("Error: Could not open communication port\n");
		Thread::Wait(10*1000);
	}
}

NetManager::~NetManager()
{

}

void NetManager::ResetFD()
{
	FD_ZERO(&this->fd);
	FD_SET(this->Socket, &this->fd);
}

SOCKET NetManager::WaitForClient()
{
	SOCKET ret = accept(this->Socket, 0, 0);
	return ret;
}

SOCKET NetManager::CreateSocket(unsigned short Port)
{
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(SOCKADDR_IN));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(Port);
	addr.sin_addr.s_addr = 0;//ADDR_ANY;
	if( bind(s, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR )
	{
		Net::Close(s);
		return SOCKET_ERROR;
	}
	listen(s, 16);

	return s;
}