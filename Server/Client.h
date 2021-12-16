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

#ifndef CLIENT_H
#define CLIENT_H

class Client
{
private:
	Joueur *joueur;
	Game *game;
	const int MAXDATASIZE;
	int id;
	bool is_alive;
#ifdef _WIN32
	SOCKET socket;
#else
	int socket;
#endif
	std::thread thread;
	char* buffer;

	bool send_message(const char*);
	int recv_message();
	bool close_socket();
	void execute_thread();


public:
#ifdef _WIN32
	Client(int, SOCKET, const int MAXDATASIZE, Game *game);
#else
	Client(int, int, const int MAXDATASIZE, Game *game);
#endif
	~Client();

	void start_thread();
	void end_thread();
	void join_thread();
};

#endif
