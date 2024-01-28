#pragma once
#include <string>
using namespace std;

class Concepteur
{
public:
	//TODO: Un constructeur par défaut et un constructeur paramétré.
	Concepteur() {}
	Concepteur(string nom, unsigned annee, string pays) {
		nom_ = nom;
		anneeNaissance_ = annee;
		pays_ = pays;
	}
	const std::string& getNom() const     { return nom_; }
	void setNom(const std::string& nom)   { nom_ = nom; }
	int getAnneeNaissance() const         { return anneeNaissance_; }
	void setAnneeNaissance(int annee)     { anneeNaissance_ = annee; }
	const std::string& getPays() const    { return pays_; }
	void setPays(const std::string& pays) { pays_ = pays; }

private:
	std::string nom_;
	unsigned anneeNaissance_;
	std::string pays_;
};
