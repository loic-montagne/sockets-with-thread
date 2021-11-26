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
#include "EndPoint.h"
#include "Output.h"

EndPoint::EndPoint(int connection_port, const int backlog, bool init_winsocks) : connection_port(connection_port), backlog(backlog), init_winsocks(init_winsocks)
{
}

EndPoint::~EndPoint()
{
	close();
}


#ifdef _WIN32
bool EndPoint::open()
{
    SOCKADDR_IN address;

    // Initialisation l'utilisation des WinSocks par un processus
    if (init_winsocks) {
        WSADATA WSAData;
        if (WSAStartup(MAKEWORD(2, 0), &WSAData) == -1) {
            Output::GetInstance()->print_error("Error while starting using WinSocks : ");
            return false;
        }
    }

    // Ouverture de la socket de connexion
    if ((connection_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        Output::GetInstance()->print_error("Error while creating connection socket : ");
        return false;
    }

    // Configuration de l'adresse de transport
    address.sin_addr.s_addr = INADDR_ANY;      // adresse, devrait être converti en reseau mais est egal à 0
    address.sin_family = AF_INET;              // type de la socket
    address.sin_port = htons(connection_port); // port, converti en reseau

    // Demarrage du point de connexion : on ajoute l'adresse de transport dans la socket
    if (bind(connection_socket, (SOCKADDR*)&address, sizeof(address)) == -1) {
        Output::GetInstance()->print_error("Error while binding connection socket : ");
        return false;
    }

    // Attente sur le point de connexion
    if (listen(connection_socket, backlog) == -1) {
        Output::GetInstance()->print_error("Error while listening connection socket : ");
        return false;
    }

    return true;
}

SOCKET EndPoint::accept_connection()
{
    SOCKET client_socket;
    SOCKADDR_IN client_address;
    int sinsize = sizeof(client_address);

    // Acceptation de la connexion
    if ((client_socket = accept(connection_socket, (SOCKADDR*)&client_address, &sinsize)) == -1) {
        Output::GetInstance()->print_error("Error while accepting client connection : ");
        return NULL;
    }

    // Affichage de la connexion
    Output::GetInstance()->print("[+] New connection from ", inet_ntoa(client_address.sin_addr), "\n");

    return client_socket;
}
#else
int EndPoint::open()
{
    int connection_socket;
    struct sockaddr_in address;
    int yes = 1;

    // Ouverture de la socket de connexion
    if ((connection_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        Output::GetInstance()->print_error("Error while creating connection socket : ");
        return false;
    }

    // Configuration de la socket de connexion
    if (setsockopt(connection_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        Output::GetInstance()->print_error("Error while configuring connection socket : ");
        return false;
    }

    // Configuration de l'adresse de transport        
    address.sin_addr.s_addr = INADDR_ANY;      // adresse, devrait être converti en reseau mais est egal à 0
    address.sin_family = AF_INET;              // type de la socket
    address.sin_port = htons(connection_port); // port, converti en reseau
    bzero(&(address.sin_zero), 8);             // mise a zero du reste de la structure

    // Demarrage du point de connexion : on ajoute l'adresse de transport dans la socket
    if (bind(connection_socket, (struct sockaddr*)&address, sizeof(struct sockaddr)) == -1) {
        Output::GetInstance()->print_error("Error while binding connection socket : ");
        return false;
    }

    // Attente sur le point de connexion
    if (listen(connection_socket, BACKLOG) == -1) {
        Output::GetInstance()->print_error("Error while listening connection socket : ");
        return false;
    }

    return true;
}

int accept_connection()
{
    int client_socket;
    struct sockaddr_in client_address;
    unsigned int sinsize = sizeof(struct sockaddr_in);

    // Acceptation de la connexion
    if ((client_socket = accept(connection_socket, (struct sockaddr*)&client_address, &sinsize)) == -1) {
        Output::GetInstance()->print_error("Error while accepting client connection : ");
        return NULL;
    }

    // Affichage de la connexion
    Output::GetInstance()->print("[+] New connection from ", inet_ntoa(client_address.sin_addr), "\n");

    return client_socket;
}
#endif

bool EndPoint::close()
{
	int result;
    Output::GetInstance()->print("Trying to close connection socket...\n");

#ifdef _WIN32
	result = closesocket(connection_socket);
#else
	result = close(connection_socket);
#endif

	if (result == -1) {
		Output::GetInstance()->print_error("Error while closing connection socket : ");
        Output::GetInstance()->print("\n");
		return false;
	}
	
#ifdef _WIN32
	if (init_winsocks && WSACleanup() == -1) {
		Output::GetInstance()->print_error("Error while cleaning WinSocks : ");
        Output::GetInstance()->print("\n");
		return false;
	}
#endif

    Output::GetInstance()->print("Connection socket closed successfully !\n");

	return true;
}
*/