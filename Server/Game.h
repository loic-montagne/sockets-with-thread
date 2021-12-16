#pragma once
#include <list>
class Joueur;

class Game {

private:
	std::list<Joueur*> Joueurs;
	int nbTour;
	int nbJoueurReady;

	void startGame();
public:
	Game();
	void addJoueur(Joueur *newJoueur);
	void setJoueurReady();
};