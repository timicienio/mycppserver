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

class Connection
{
private:
	// data
	int sd;
	struct timeval start1, end1;
	int bytesRead, bytesWritten;

	// buffer
	char buf[2000];
	char sendBuf[2000];

	void printConnectionStats();

	void init();

public:
	Connection(int sd);
	~Connection();

	void handle();
};
