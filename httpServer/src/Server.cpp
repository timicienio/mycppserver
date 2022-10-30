#include "Server.h"

void Server::initListenSocket()
{
	bzero((char *)&(this->servAddr), sizeof((this->servAddr)));
	this->servAddr.sin_family = AF_INET;
	this->servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	this->servAddr.sin_port = htons(PORT);

	// create socket
	this->listenSd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->listenSd < 0)
	{
		std::cerr << "Error establishing the server socket" << std::endl;
		exit(0);
	}

	// bind socket
	int bindStatus = bind(this->listenSd, (struct sockaddr *)&this->servAddr,
												sizeof(servAddr));
	if (bindStatus < 0)
	{
		std::cerr << "Error binding socket to local address" << std::endl;
		exit(0);
	}

	// socket listen
	listen(this->listenSd, 10);

	std::cout << "Server listening on port " << PORT << std::endl;
}

void Server::run()
{
	while (true)
	{
		sockaddr_in newSockAddr;
		socklen_t newSockAddrSize = sizeof(newSockAddr);
		int newSd = accept(this->listenSd, (sockaddr *)&newSockAddr, &newSockAddrSize);
		this->connections.emplace_back(newSd);
		this->connections.back().handle();
	}
}

Server::Server()
{
	this->initListenSocket();
}

Server::~Server()
{
}
