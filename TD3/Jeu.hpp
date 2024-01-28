#pragma once
#include "Liste.hpp"
#include "Concepteur.hpp"
#include <string>
#include <memory>
#include <functional>

class Jeu
{
public:
	//TODO: un constructeur par d�faut et un constructeur param�tr�.
	Jeu(){}
	Jeu(string titre, unsigned int annee, string dev) {
		titre_ = titre;
		anneeSortie_ = annee;
		developpeur_ = dev;
	}
	const std::string& getTitre() const     { return titre_; }
	void setTitre(const std::string& titre) { titre_ = titre; }
	unsigned getAnneeSortie() const         { return anneeSortie_; }
	void setAnneeSortie(unsigned annee)     { anneeSortie_ = annee; }
	const std::string& getDeveloppeur() const { return developpeur_; }
	void setDeveloppeur(const std::string& developpeur) { developpeur_ = developpeur; }

	//TODO: Pouvoir acc�der � la liste de concepteurs.
	const Liste<Concepteur>& getListeConcepteur() const {
		return concepteurs_;
	}

	Liste<Concepteur>& getListeConcepteur() {
		return concepteurs_;
	}

	//TODO: Votre m�thode pour trouver un concepteur selon un crit�re donn� par une lambda, en utilisant la m�thode de Liste.
	shared_ptr<Concepteur> trouverConcepteur(function<bool(const shared_ptr<Concepteur>&)> func) {
		return concepteurs_.trouverElement(func);
	}

	void ajouterConcepteur(shared_ptr<Concepteur> concepteur) {
		concepteurs_.ajouterElement(concepteur);
	}

private:
	std::string titre_;
	unsigned anneeSortie_;
	std::string developpeur_;
	//TODO: Attribut de la liste des concepteurs du jeu
	Liste<Concepteur> concepteurs_;
};
