#ifndef AFFICHABLE_HPP
#define AFFICHABLE_HPP
#include <iostream>
using namespace std;

class Affichable {
	virtual void afficher(ostream& os, char couleur = ' ') const = 0;
	virtual void changerCouleur(ostream& os, char couleur = ' ') const = 0;
};
#endif