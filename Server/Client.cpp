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
#include "Client.h"
#include "Output.h"
#include "Joueur.h"
#include "Game.h"
#ifdef _WIN32
Client::Client(int id, SOCKET socket, const int MAXDATASIZE, Game *game) : id(id), socket(socket), MAXDATASIZE(MAXDATASIZE), is_alive(true), game(game)
{
	joueur = new Joueur(this);
	game->addJoueur(joueur);
    buffer = new char[MAXDATASIZE];
}
#else
Client::Client(int id, int socket, const int MAXDATASIZE, Game *game) : id(id), socket(socket), MAXDATASIZE(MAXDATASIZE), is_alive(true), game(game)
{
	joueur = new Joueur();
    buffer = new char[MAXDATASIZE];
}
#endif

Client::~Client()
{
    end_thread();
    delete[] buffer;
	delete joueur;
}

bool Client::close_socket()
{
	if (socket == NULL || !is_alive)
		return true;

	int result;
	Output::GetInstance()->print("[CLIENT_", id, "] Closing client socket...\n");

#ifdef _WIN32
	result = closesocket(socket);
#else
	result = close(socket);
#endif

	if (result == -1) {
		char* error = new char[MAXDATASIZE];
		sprintf(error, "[CLIENT_%d] Error while closing socket ", id);
		Output::GetInstance()->print_error(error);
		Output::GetInstance()->print("\n");
		delete[] error;
		return false;
	}
	else {
		Output::GetInstance()->print("[CLIENT_", id, "] Client socket closed successfully.\n");
	}

	return true;
}
bool Client::send_message(const char* buffer)
{
	if (socket == NULL || !is_alive)
		return false;

	if (send(socket, buffer, strlen(buffer), 0) == -1) {
		char* error = new char[MAXDATASIZE];
		sprintf(error, "[CLIENT_%d] Error while sending message to client ", id);
		Output::GetInstance()->print_error(error);
		Output::GetInstance()->print("\n");
		delete[] error;
		return false;
	}

	return true;
}
int Client::recv_message()
{
	if (socket == NULL || !is_alive)
		return -1;

	int length;
	if ((length = recv(socket, buffer, MAXDATASIZE, 0)) == -1)
	{
		char* error = new char[MAXDATASIZE];
		sprintf(error, "[CLIENT_%d] Error while receiving message from client ", id);
		Output::GetInstance()->print_error(error);
		Output::GetInstance()->print("\n");
		delete[] error;
		return length;
	}

	// Suppression des retours chariots (\n et \r)
	while (length > 0 && (buffer[length - 1] == '\n' || buffer[length - 1] == '\r'))
		length--;
	// Ajout de backslash zero a la fin pour en faire une chaine de caracteres
	if (length >= 0 && length < MAXDATASIZE)
		buffer[length] = '\0';

	return length;
}

void Client::execute_thread()
{
    int length;
    time_t time_value;
    struct tm* time_info;

	Output::GetInstance()->print("[CLIENT_", id, "] Thread client starts with id=", id, ".\n");

    // Boucle infinie pour le client
    while (1) {

		if (socket == NULL || !is_alive)
			return;

        // On attend un message du client
        if ((length = recv_message()) == -1) {
            break;
        }

		if (socket == NULL || !is_alive)
			return;

        // Affichage du message
		Output::GetInstance()->print("[CLIENT_", id, "] Message received : ", buffer, "\n");
		
		//JSON a faire pour le buffer, le client envoie des JSON c'est mieux

        if (strcmp(buffer, "DISCONNECT") == 0) {
            break;
        }
        else {
            // On recupere l'heure et la date
            time(&time_value);
            time_info = localtime(&time_value);

            // Traitement du message reçu
            if (strcmp(buffer, "DATE") == 0)
                strftime(buffer, MAXDATASIZE, "%e/%m/%Y", time_info);
            else if (strcmp(buffer, "DAY") == 0)
                strftime(buffer, MAXDATASIZE, "%A", time_info);
            else if (strcmp(buffer, "MONTH") == 0)
                strftime(buffer, MAXDATASIZE, "%B", time_info);
			else if (strcmp(buffer, "READY") == 0) {
				game->setJoueurReady();
			}
            else
                sprintf(buffer, "%s is not recognized as a valid command", buffer);

			if (socket == NULL || !is_alive)
				return;

            // On envoie le buffer
			Output::GetInstance()->print("[CLIENT_", id, "] Sending message \"", buffer, "\" to client...\n");
            if (!send_message(buffer)) {
                break;
            }

			Output::GetInstance()->print("[CLIENT_", id, "] Message \"", buffer, "\" send to client successfully.\n");
        }
    }

	end_thread();
}

void Client::start_thread()
{
	join_thread();
	// Start client thread
	thread = std::thread(&Client::execute_thread, this);
}

void Client::end_thread()
{
	if (!is_alive)
		return;

	Output::GetInstance()->print("[CLIENT_", id, "] Thread client is ending...\n");

	// Sending close connection to client
	send_message("CONNECTION_CLOSED");

	is_alive = false;

	// End thread
	thread.detach();
	thread.~thread();

	// Close connection
	close_socket();

	Output::GetInstance()->print("[CLIENT_", id, "] Thread client ends.\n");
}

void Client::join_thread()
{
	if (thread.joinable()) {
		thread.join();
	}
}
