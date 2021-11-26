/*
#ifdef _WIN32
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
//#include <thread>
//#include <mutex>
//#include <cstdarg>
//#include <vector>

#include "Output.h"
#include "Client.h"
#include "EndPoint.h"


// Valeurs constantes utilisées dans le programme
// ----------------------------------------------------------------------------------------------------------------

// Nombre maximal de connexions en attente
#define BACKLOG 10

// Nombre maximal d'octets à envoyer ou à lire en une fois
#define MAXDATASIZE 100


// Prototypes des fonctions disponibles dans le programme
// (l'implémentation est faite dans ce fichier)
// ----------------------------------------------------------------------------------------------------------------

bool strtoi(char*, int*);


// Variables globales
// ----------------------------------------------------------------------------------------------------------------

// Liste des threads en cours d'exécution



// Fonctions
// ----------------------------------------------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    std::cout << "*********************************************************" << std::endl;
    std::cout << "*           Simple socket server application            *" << std::endl;
    std::cout << "*********************************************************" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    // Lecture des paramètres en cours
    int port;
    if (argc != 2 || !strtoi(argv[1], &port)) {
        std::cout << "Invalid parameters !" << std::endl;
        std::cout << "program usage : " << argv[0] << " connection_port" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Ouverture de la socket de connexion
    std::cout << "Trying to open connection socket on the port " << port << "..." << std::endl;
    EndPoint connection(port, BACKLOG, true);
    if (!connection.open()) {
        exit(EXIT_FAILURE);
    }
    std::cout << "Connection socket opened successfully !" << std::endl;

    // Boucle pour accepter les connexions entrantes
    int threads_count = 0;
    while (1)
    {
        Output::GetInstance()->print("\nWaiting for client connection...\n");

        threads_count++;
        Client c(threads_count, connection.accept_connection(), MAXDATASIZE);
        c.start_thread();
    }

    if (!connection.close())
        exit(EXIT_FAILURE);

    return EXIT_SUCCESS;
}

bool strtoi(char* value, int* result)
{
    char* p;
    errno = 0;
    long arg = strtol(value, &p, 10);
    if (*p != '\0' || errno != 0) {
        return false;
    }

    if (arg < INT_MIN || arg > INT_MAX) {
        return false;
    }

    *result = arg;
    return true;
}
*/