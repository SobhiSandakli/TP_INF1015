#include "ListeDeveloppeurs.hpp"
#include "Developpeur.hpp"
#include <iostream>
using namespace std;

ListeDeveloppeurs::ListeDeveloppeurs() {
	nElements = 0;
	capacite = 1;
	elements = new Developpeur * [capacite];
} 

ListeDeveloppeurs::~ListeDeveloppeurs() {
	delete[] elements;
}


void ListeDeveloppeurs::afficher() const {
	for (int i = 0; i < nElements; i++) {
		elements[i]->afficherJeuxDeveloppes() ;
		cout << endl;
	}
}

void ListeDeveloppeurs::ajouterDeveloppeur(Developpeur& dev) {
	bool existe = false;
	for (int i = 0; i < nElements; i++) {
		if (elements[i] == &dev) {
			existe = true;
		}
	}
	if (existe == false) {
		if (nElements == capacite) {
			augmenterCapacite(capacite == 0 ? 1 : capacite * 2);
		}
		elements[nElements++] = &dev;
	}
}

void ListeDeveloppeurs::retirerDeveloppeur(Developpeur& dev) {
	for (int i = 0; i < nElements; i++) {
		if (elements[i] == &dev) {
			elements[i] = elements[nElements-- - 1];
			break;
		}
	}
}

void ListeDeveloppeurs::augmenterCapacite(int taille) {
	Developpeur** nouvelleListe = new Developpeur * [taille];
	for (int i = 0; i < nElements; i++) {
		nouvelleListe[i] = elements[i];
	}
	delete[] elements;
	elements = nouvelleListe;
	capacite = taille;
}