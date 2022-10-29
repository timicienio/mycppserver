#include "Connection.h"

void Connection::printConnectionStats()
{
	std::cout << "********Session********" << std::endl;
	std::cout << "Bytes written: " << this->bytesWritten << " Bytes read: " << this->bytesRead << std::endl;
	std::cout << "Elapsed time: " << (this->end1.tv_sec - this->start1.tv_sec)
						<< " secs" << std::endl;
	std::cout << "Connection closed..." << std::endl;
}

void Connection::init()
{
	gettimeofday(&(this->start1), NULL);
	this->bytesRead = 0;
	this->bytesWritten = 0;

	std::cout << "A new connection was established!" << std::endl;
}

void Connection::handle()
{
	while (true)
	{
		memset(&(this->buf), 0, sizeof(this->buf));
		int curBytesRead = recv(this->sd, (char *)&this->buf, sizeof(this->buf), 0);
		this->bytesRead += curBytesRead;
		if (!curBytesRead)
		{
			std::cout << "Client has quit the session" << std::endl;
			break;
		}

		std::cout << "Client says: " << this->buf << std::endl;

		strcpy(this->sendBuf, ("I heard you, you said: " + std::string(this->buf)).c_str());
		int curBytesWritten = send(this->sd, this->sendBuf, sizeof(this->sendBuf), 0);
		this->bytesWritten += curBytesWritten;
	}

	gettimeofday(&end1, NULL);

	this->printConnectionStats();
	close(this->sd);
}

Connection::Connection(int sd) : sd(sd)
{
	this->init();
}

Connection::~Connection()
{
}
