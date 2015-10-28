#include "PlayerComm.hpp"

using namespace std;

int PlayerComm :: getHost(char *serverName){
    server = gethostbyname(serverName);
    if (server == NULL) {
        cerr << "No host found!\n";
        return -1;
    }
}

int PlayerComm :: createSocket() {
    serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverfd < 0) {
		cerr << "ERROR opening socket\n";
		return -1;
	}

    clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd < 0) {
		cerr << "ERROR opening socket\n";
		return -1;
	}
	return 0;
}

int PlayerComm :: connectSocket() {
    if (connect(clientfd,(struct sockaddr *) &serverAddress,sizeof(serverAddress)) < 0) {
		cerr << "ERROR connecting\n";
		return -1;
	}
	return 0;
}

int PlayerComm :: bindSocket() {
	if (bind(serverfd, (struct sockaddr *) &myServerAddress, sizeof(myServerAddress)) < 0) {
        cerr << "ERROR opening socket\n";
		return -1;
	}
	return 0;
}

void PlayerComm :: listenSocket() {
	listen(serverfd,5);
	clientLength = sizeof(clientLength);
}

int PlayerComm ::acceptSocket() {
	int bytes;

	newsockfd = accept(serverfd, (struct sockaddr *) &clientAddress, &clientLength);
	if (newsockfd < 0) {
		cerr << "ERROR on accept\n";
		return -1;
	}

	return 0;
}

PlayerComm :: PlayerComm(char *serverName, int portToConnect,int portToListen): clientPort(portToConnect), serverPort(portToListen) {

    this->getHost(serverName);
	/* Initialize player's socket information */
	bzero((char *) &serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serverAddress.sin_addr.s_addr, server->h_length);
	serverAddress.sin_port = htons(portToConnect);

	bzero((char *) &myServerAddress, sizeof(myServerAddress));
    myServerAddress.sin_family = AF_INET;
	myServerAddress.sin_addr.s_addr = INADDR_ANY;
	myServerAddress.sin_port = htons(portToListen);
}

PlayerComm :: ~PlayerComm() {
	close(serverfd);
	close(clientfd);
}

int PlayerComm :: sendMessage(const char *message) {
    int bytes;

	bytes = write(newsockfd, message, strlen(message));
	if (bytes < 0) {
		cerr << "ERROR writing to socket\n";
		return -1;
	}
	return 0;
}

string * PlayerComm :: readMessage() {
    int bytes;

	bzero(buffer,sizeof(buffer));
	bytes = read(clientfd,buffer,sizeof(buffer) - 1);
	if (bytes < 0) {
		cerr << "ERROR reading from socket\n";
		return NULL;
	}

	string* str = new string(buffer);
	//cout<<"str = "<< *str<<endl;
	return str;
}

void  PlayerComm :: init(int who) {
    this->createSocket();
    this->bindSocket();
    this->listenSocket();
    cout<<"I reached here "<<who<<endl;
    if(who == 1){
        this->acceptSocket();
        this->connectSocket();
        cout<<"Connected successful "<<who<<endl;
    }else{
        this->connectSocket();
        this->acceptSocket();
        cout<<"Connected successful "<<who<<endl;
    }
}