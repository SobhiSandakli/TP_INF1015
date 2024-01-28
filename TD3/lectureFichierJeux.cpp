// Fonctions pour lire le fichier binaire.
#include "lectureFichierJeux.hpp"
#include <fstream>
#include "Jeu.hpp"
#include "cppitertools/range.hpp"
using namespace std;

#pragma region "Fonctions de lecture de base"
UInt8 lireUint8(istream& fichier)
{
	UInt8 valeur = 0;
	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
	return valeur;
}

UInt16 lireUint16(istream& fichier)
{
	UInt16 valeur = 0;
	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
	return valeur;
}

string lireString(istream& fichier)
{
	string texte;
	texte.resize(lireUint16(fichier));
	fichier.read(reinterpret_cast<char*>(&texte[0]), streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}
#pragma endregion

shared_ptr<Concepteur> chercherConcepteur(Liste<Jeu>& listeJeux, string nom)
{
	//TODO: Compléter la fonction (équivalent de trouverDesigner du TD2).
	auto searchLambda = [&](shared_ptr<Concepteur> concepteur) {return concepteur->getNom() == nom;};
	for (unsigned int i = 0; i < listeJeux.size(); i++) {
		shared_ptr<Concepteur> concepteur = listeJeux[i]->trouverConcepteur(searchLambda);
		if (concepteur != nullptr) {
			return concepteur;
		}
	}
	return nullptr;

}

shared_ptr<Concepteur> lireConcepteur(Liste<Jeu>& lj, istream& f)
{
	string nom              = lireString(f);
	unsigned anneeNaissance = lireUint16(f);
	string pays             = lireString(f);

	//TODO: Compléter la fonction (équivalent de lireDesigner du TD2).

	shared_ptr<Concepteur> concepteurExistant = chercherConcepteur(lj, nom);
	if (concepteurExistant != nullptr)
		return concepteurExistant;
	cout << "\033[92m" << "Allocation en mémoire du concepteur " << nom << "\033[0m" << endl;
	return make_shared<Concepteur> (nom, anneeNaissance, pays); 
}

shared_ptr<Jeu> lireJeu(istream& f, Liste<Jeu>& lj)
{
	string titre          = lireString(f);
	unsigned anneeSortie  = lireUint16(f);
	string developpeur    = lireString(f);
	unsigned nConcepteurs = lireUint8(f);
	//TODO: Compléter la fonction (équivalent de lireJeu du TD2).

	shared_ptr<Jeu> jeu = make_shared<Jeu>(titre, anneeSortie, developpeur);
	cout << "\033[96m" << "Allocation en mémoire du jeu " << titre << "\033[0m" << endl;

	for (unsigned int i = 0; i < nConcepteurs; i++)
		jeu->ajouterConcepteur(lireConcepteur(lj, f));
	return jeu;
}

Liste<Jeu> creerListeJeux(const string& nomFichier)
{
	ifstream f(nomFichier, ios::binary);
	f.exceptions(ios::failbit);
	int nElements = lireUint16(f);
	//TODO: Compléter la fonction.   
	Liste<Jeu> listeJeux;
	for (int i = 0; i < nElements; i++) {
		shared_ptr<Jeu> jeu = lireJeu(f, listeJeux);
		listeJeux.ajouterElement(jeu);
	}
	return listeJeux;
}
