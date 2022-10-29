#pragma once
#include "Connection.h"
#define PORT 3000
class Server
{
protected:
	// data
	sockaddr_in servAddr;
	int listenSd;

	std::vector<Connection> connections;

	// initialization
	void initListenSocket();

public:
	// run
	void run();

	Server();
	~Server();
};
