#ifdef _WIN32
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
#include <thread>
#include "Joueur.h"
#include "Game.h"
#include "ThreadedSocket.h"

#ifndef CLIENT_H
#define CLIENT_H

class Client : public ThreadedSocket
{
private:
	Joueur *joueur;
	Game *game;
	const int MAXDATASIZE;
protected:
	int id;
	char* buffer;

	void execute_thread();

	bool send_message(const char*);
	int recv_message();
	

public:
#ifdef _WIN32
	Client(int, SOCKET, const int MAXDATASIZE, Game *game);
#else
	Client(int, int, const int MAXDATASIZE, Game *game);
#endif
	~Client();
	void end_thread();
};

#endif
