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
	memset(&(this->buf), 0, sizeof(this->buf));
	int curBytesRead = recv(this->sd, (char *)&this->buf, sizeof(this->buf), 0);
	this->bytesRead += curBytesRead;
	if (!curBytesRead)
	{
		std::cout << "Client has quit the session" << std::endl;
		return;
	}

	int i;

	for (i = 0; i < curBytesRead; i++)
		if (this->buf[i] == '\r' || this->buf[i] == '\n')
			this->buf[i] = 0;

	if (strncmp(this->buf, "GET ", 4) && strncmp(this->buf, "get ", 4))
		exit(3);

	for (i = 4; i < sizeof(this->buf); i++)
	{
		if (this->buf[i] == ' ')
		{
			this->buf[i] = 0;
			break;
		}
	}

	// strcpy(this->sendBuf, ("I heard you, you said: " + std::string(this->buf)).c_str());
	// int curBytesWritten = send(this->sd, this->sendBuf, sizeof(this->sendBuf), 0);
	// this->bytesWritten += curBytesWritten;

	for (int j = 0; j < i - 1; j++)
		if (this->buf[j] == '.' && this->buf[j + 1] == '.')
		{
			close(this->sd);
			return;
		}

	if (!strncmp(&this->buf[0], "GET /\0", 6) || !strncmp(&this->buf[0], "get /\0", 6))
		strcpy(this->buf, "GET /index.html\0");

	int buflen = strlen(this->buf);
	char *fstr = (char *)0;

	for (i = 0; extensions[i].ext != 0; i++)
	{
		int len = strlen(extensions[i].ext);
		if (!strncmp(&this->buf[buflen - len], extensions[i].ext, len))
		{
			fstr = extensions[i].filetype;
			break;
		}
	}

	if (fstr == 0)
	{
		fstr = extensions[i - 1].filetype;
	}

	int file_fd;

	if ((file_fd = open(&this->buf[5], O_RDONLY)) == -1)
	{
		sprintf(this->buf, "HTTP/1.0 404 Not Found\r\nContent-Type: text/plain\r\n\r\n404 Not Found\r\n");
		write(this->sd, this->buf, strlen(this->buf));
	}
	else
	{
		sprintf(this->buf, "HTTP/1.0 200 OK\r\nContent-Type: %s\r\n\r\n", fstr);
		write(this->sd, this->buf, strlen(this->buf));
	}

	int curBytesWritten = 0;

	while ((curBytesWritten = read(file_fd, this->buf, sizeof(this->buf))) > 0)
	{
		this->bytesWritten += curBytesWritten;
		write(this->sd, this->buf, curBytesWritten);
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
