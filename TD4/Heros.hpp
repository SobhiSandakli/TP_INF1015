#ifndef HEROS_HPP
#define HEROS_HPP
#include <iostream>
#include "affichable.hpp"
#include "Personnage.hpp"
#include <vector>

using namespace std;

class Heros : public virtual Personnage {
public:
	Heros(const string& nom = " ", const string& titreDuJeu = " ", const string& ennemi = " ", vector<string> allies = {}) : Personnage(nom, titreDuJeu), ennemi_(ennemi), allies_(allies) {};

	void ajouterAllies(const string& allie)  {
		allies_.push_back(allie);
	}

	void afficher(ostream& os, char couleur = ' ') const {
		Personnage::afficher(os, couleur);
		changerCouleur(os, couleur);
		os << "Ennemi : " << ennemi_ << endl;
		os << "Allies: ";
		for (const string& allie : allies_) {
			os << "    " << allie << endl;
		}
		changerCouleur(os);
		os << endl;
	}
	string getNom() const { return Personnage::getNom(); }
	string getTitre() const { return Personnage::getTitre(); }
	string getEnnemi() const { return ennemi_; }
	vector<string> getAllies() const { return allies_; }
private:
	string ennemi_;
	vector<string> allies_;
};
#endif