#include <fstream>
#include "affichable.hpp"
#include "Personnage.hpp"
#include "Heros.hpp"
#include "Villain.hpp"
#include "VillainHeros.hpp"
#include "bibliotheque_cours.cpp"
#include <cppitertools/range.hpp>

using UInt8 = uint8_t;
using UInt16 = uint16_t;

UInt8 lireUint8(std::istream& fichier)
{
	UInt8 valeur = 0;
	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
	return valeur;
}

UInt16 lireUint16(std::istream& fichier)
{
	UInt16 valeur = 0;
	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
	return valeur;
}

std::string lireString(std::istream& fichier)
{
	std::string texte;
	texte.resize(lireUint16(fichier));
	fichier.read(reinterpret_cast<char*>(&texte[0]), std::streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}

using namespace std;

Heros lireHero(istream& f) {

	string nom = lireString(f);
	string titreDuJeu = lireString(f);
	string ennemi = lireString(f);
	int nAllies = lireUint8(f);
	vector<string> allies;

	Heros hero(nom, titreDuJeu, ennemi, allies);
	for (int i = 0; i < nAllies; i++) {
		hero.ajouterAllies(lireString(f));
	}
	return hero;
};

vector<Heros> lireHeros(istream& f) {
	vector<Heros> listeHeros;
	Heros hero;
	int nHeros = lireUint16(f);
	for (int i = 0; i < nHeros; i++) {
		hero = lireHero(f);
		listeHeros.push_back(hero);
	}
	return listeHeros;
}

Villain lireVilain(istream& f) {
	string nom = lireString(f);
	string parution = lireString(f);
	string objectif = lireString(f);

	Villain vilain(nom, parution, objectif);
	return vilain;
}

vector<Villain> lireVilains(istream& f) {
	vector<Villain> listeVilains;
	Villain vilain;
	int nVilains = lireUint16(f);
	for (int i = 0; i < nVilains; i++) {
		vilain = lireVilain(f);
		listeVilains.push_back(vilain);
	}
	return listeVilains;
}

int main()
{
	#pragma region "Bibliothèque du cours"
	// Permet sous Windows les "ANSI escape code" pour changer de couleur
	// https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
	// les supportent normalement par défaut.
	bibliotheque_cours::activerCouleursAnsi();
	#pragma endregion
	
	// Trait de separation
	static const string trait =
		"═════════════════════════════════════════════════════════════";

	// Ouverture des fichiers binaires
	ifstream fichierHeros("heros.bin", ios::binary);
	ifstream fichierVilains("vilains.bin", ios::binary);
	fichierHeros.exceptions(ios::failbit);
	fichierVilains.exceptions(ios::failbit);

	//TODO: Votre code pour le main commence ici
	vector<Villain> ListeVilains = lireVilains(fichierVilains);
	vector<Heros> listeHeros = lireHeros(fichierHeros);
	vector<Personnage> vecPersonnage;
	
	for (auto&& Hero: listeHeros) {
		Hero.afficher(cout, 'b');
		vecPersonnage.push_back(Hero);
	}

	for (auto&& Vilain : ListeVilains) {
		Vilain.afficher(cout, 'r');
		vecPersonnage.push_back(Vilain);
	}

	for (auto&& Pers : vecPersonnage) {
		Pers.afficher(cout);
	}

	VilainHeros vilainHeros(ListeVilains[2], listeHeros[0]);
	vilainHeros.afficher(cout, 'p');
}

