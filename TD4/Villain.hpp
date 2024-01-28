#ifndef VILLAIN_HPP
#define VILLAIN_HPP
#include <iostream>
#include "affichable.hpp"
#include "Personnage.hpp"
#include <vector>

using namespace std;

class Villain : public virtual Personnage {
public:
	Villain(const string& nom = " ", const string& titreDuJeu = " ", const string& objectif = " ") : Personnage(nom, titreDuJeu), objectif_(objectif) {};

	void afficher(ostream& os, char couleur = ' ') const {
		Personnage::afficher(os, couleur);
		changerCouleur(os, couleur);
		os << "Objectif: " << objectif_ << endl;
		changerCouleur(os);
		os << endl;
	}

	string getObjectif() const { return objectif_; }
private:
	string objectif_;
};
#endif