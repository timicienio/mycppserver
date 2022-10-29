#include "Client.h"

void Client::init()
{
}

void Client::run()
{
	this->sd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->sd < 0)
	{
		std::cerr << "Error creating socket" << std::endl;
		exit(0);
	}

	bzero((char *)&(this->servAddr), sizeof((this->servAddr)));
	this->servAddr.sin_family = AF_INET;
	this->servAddr.sin_addr.s_addr = inet_addr(this->server_ip.c_str());
	this->servAddr.sin_port = htons(this->port);

	int err = connect(this->sd, (struct sockaddr *)&this->servAddr, sizeof(this->servAddr));
	if (err == -1)
	{
		std::cerr << "Error connecting to server" << std::endl;
		exit(0);
	}

	std::string message;
	while (true)
	{
		std::cin >> message;
		if (message == "quit")
			break;
		int sendErr = send(this->sd, message.c_str(), sizeof(message.c_str()), 0);
		if (sendErr == -1)
		{
			std::cout << "Error sending message" << std::endl;
			exit(1);
		}
		std::cout << "Message sent to server" << std::endl;

		recv(this->sd, this->buf, sizeof(this->buf), 0);
		if (sendErr == -1)
		{
			std::cout << "Error receiving message" << std::endl;
			exit(1);
		}
		std::cout << "Server emit: " << this->buf << std::endl;
	}
	std::cout << "Quitting\n";
	close(this->sd);
}

Client::Client()
{
	this->init();
}

Client::~Client()
{
}