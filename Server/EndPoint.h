/*
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

#ifndef ENDPOINT_H
#define ENDPOINT_H

class EndPoint
{
private:
	const int backlog;
	int connection_port;
	bool init_winsocks;
#ifdef _WIN32
	SOCKET connection_socket;
#else
	int connection_socket;
#endif
	

public:
	EndPoint(int, const int, bool);
	~EndPoint();

	bool open();
#ifdef _WIN32
	SOCKET accept_connection();
#else
	int accept_connection();
#endif
	bool close();
};

#endif
*/