#include "bibliotheque_cours.hpp"
#include "verification_allocation.hpp"
#include "Liste.hpp"
#include "Concepteur.hpp"
#include "Jeu.hpp"
#include "lectureFichierJeux.hpp"
#include <iostream>
#include <fstream>
using namespace std;

//TODO: Vos surcharges d'opérateur <<
template <typename T>
ostream& operator<<(std::ostream& os, const Liste<T>& liste) {
	for (int i = 0; i < liste.size(); i++) {
		os << *(liste[i]) << "\n";
	}
	return os;
}
//
ostream& operator<<(std::ostream& os, const Jeu& jeu) {
	os << "Nom du jeu: " << jeu.getTitre() << "\n";
	os << "Année de sortie: " << jeu.getAnneeSortie() << "\n";
	os << "Developpeur: " << jeu.getDeveloppeur() << "\n";
	return os;
}

ostream& operator<<(ostream& os, const Concepteur& concepteur)
{
	os << "Nom: " << concepteur.getNom() << ", "
		<< "Annee de naissance: " << concepteur.getAnneeNaissance() << ", "
		<< "Pays: " << concepteur.getPays();
	return os;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
	#pragma region "Bibliothèque du cours"
	// Permet sous Windows les "ANSI escape code" pour changer de couleur
	// https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
	// les supportent normalement par défaut.
	bibliotheque_cours::activerCouleursAnsi(); 
	#pragma endregion
	
	Liste<Jeu> lj = creerListeJeux("jeux.bin");
	static const string ligneSeparation = "\n\033[92m"
		"══════════════════════════════════════════════════════════════════════════"
		"\033[0m\n";

	////TODO: Les l'affichage et l'écriture dans le fichier devraient fonctionner.
	cout << ligneSeparation << lj;
	ofstream("sortie.txt") << lj;

	////TODO: Compléter le main avec les tests demandés
	
	cout << "----------------------------------------------------------------------------" << endl  << endl;
	cout << "Test Question 3" << endl;
	cout << "Nombre de jeux : " << lj.size() << endl;
	cout << "Capacite : " << lj.getCapacite() << endl << endl;

	cout << "----------------------------------------------------------------------------" << endl << endl;
	cout << "Test Question 4" << endl;
	cout << "Titre du jeu à l’indice 2 est : " <<  lj[2]->getTitre() << endl;
	cout << "Le nom de son concepteur à l’indice 1 est " << lj[2]->getListeConcepteur()[1]->getNom()  << endl << endl;

	cout << "----------------------------------------------------------------------------" << endl  << endl;
	cout << "Test Question 5" << endl;
	auto searchLambda = [&](shared_ptr<Concepteur> concepteur) {return concepteur->getNom() == "Yoshinori Kitase"; };
	shared_ptr<Concepteur> concepteur1 = lj[0]->trouverConcepteur(searchLambda);
	shared_ptr<Concepteur> concepteur2 = lj[1]->trouverConcepteur(searchLambda);
	cout << "Adresse du premier concepteur: " << concepteur1 << ", son annee de naissance est : " << concepteur1->getAnneeNaissance() << endl;
	cout << "Adresse du deuxieme concepteur: " << concepteur2 << ", son annee de naissance est : " << concepteur2->getAnneeNaissance() << endl << endl;

	cout << "----------------------------------------------------------------------------" << endl << endl;
	cout << "Test Question 7" << endl;
	Jeu copieJeu = *lj[2];
	shared_ptr<Concepteur> newConcepteur = make_shared<Concepteur>(*lj[0]->getListeConcepteur()[0]);
	copieJeu.getListeConcepteur()[1] = newConcepteur;
	cout << "Liste concepteurs du jeu originale: " << endl;
	cout << lj[2]->getListeConcepteur() << endl;
	cout << "Liste concepteurs de copieJeu: " << endl;
	cout << copieJeu.getListeConcepteur() << endl;
	cout << "Address du premier dans la liste originale : " << lj[2]->getListeConcepteur()[0] << endl;
	cout << "Address du premier dans la liste de copie : " << copieJeu.getListeConcepteur()[0] << endl;

	//TODO: S'assurer qu'aucune ligne de code est non couverte.
	//NOTE: Il n'est pas nécessaire de couvrir les getters/setters simples fournis; il faut tester si vous en ajoutez ou les modifiez.
	//NOTE: Pour Liste, qui est générique, on demande de couvrir uniquement pour Liste<Jeu>, pas pour tous les types.
}