#ifndef _PLAYERCOMM_HPP_
#define _PLAYERCOMM_HPP_

#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <ctime>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <sstream>

using namespace std;

class PlayerComm {

private :
	int serverfd;
	int clientfd;
	int newsockfd;

	int serverPort;
	int clientPort;

	struct sockaddr_in serverAddress;
	struct sockaddr_in myServerAddress;
	struct sockaddr_in clientAddress;

	struct hostent *server;

	socklen_t clientLength;

    char buffer[256];

	int getHost(char *serverName);
	int createSocket();
	int connectSocket();

	//server stuff
	int bindSocket();
	void listenSocket();
	int acceptSocket();

public:
		PlayerComm(char *serverName, int portToConnect,int portToListen);
		~PlayerComm();

        void init(int who);
		int sendMessage(const char *message);
		string* readMessage();

};

#endif