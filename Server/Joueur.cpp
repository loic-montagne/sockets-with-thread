#include "Joueur.h"
#include <list>
#include "Client.h"

Joueur::Joueur(Client* client) : client(client) {

}

int Joueur::getId()
{
	return id;
}

void Joueur::setId(int newId)
{
	id = newId;
}

void Joueur::setPointJoueur(int newPoint)
{
	point += newPoint;
}

void Joueur::setCarteJoueur()
{
	Carte *carte = new Carte();
}

std::list<Carte> Joueur::getCarteJoueur()
{
	std::list<Carte> cartes;
	return cartes;
}

int Joueur::getPointJoueur()
{
	return point;
}
