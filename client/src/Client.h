#pragma once

#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
#include <vector>

class Client
{
private:
	// data
	const std::string server_ip = "127.0.0.1";
	sockaddr_in servAddr;
	const int port = 3000;
	char buf[2000];

	int sd;

	void init();

public:
	void run();

	Client();
	~Client();
};
