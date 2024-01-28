#include "Developpeur.hpp"
#include <iostream>
#include "Jeu.hpp"
using namespace std;

Developpeur::Developpeur(string nom) {
    paireNomJeux_.first = nom;
    paireNomJeux_.second.nElements = 0;
    paireNomJeux_.second.capacite = 1;
    paireNomJeux_.second.elements = nullptr;
}

Developpeur::~Developpeur() {
    if (paireNomJeux_.second.elements != nullptr) {
        delete[] paireNomJeux_.second.elements;
    }
}

string Developpeur::getNomDeveloppeur() const {
    return paireNomJeux_.first;
}

int Developpeur::compterJeuxDansListe(const ListeJeux& listeJeux) const {
    int compteur = 0;
    for (int i = 0; i < listeJeux.nElements; i++) {
        if (listeJeux.elements[i]->developpeur == paireNomJeux_.first) {
            compteur++;
        }
    }
    return compteur;
}

void Developpeur::mettreAJourListeJeux(const ListeJeux& listeJeux) {
    int jeuxDejaDeveloppes = compterJeuxDansListe(paireNomJeux_.second);
    int nouvelleTaille = jeuxDejaDeveloppes;

    for (int i = 0; i < listeJeux.nElements; i++) {
        if (listeJeux.elements[i]->developpeur == paireNomJeux_.first) {
            nouvelleTaille++;
        }
    }

    Jeu** nouvelleListe = new Jeu * [nouvelleTaille];

    for (int i = 0; i < jeuxDejaDeveloppes; i++) {
        nouvelleListe[i] = paireNomJeux_.second.elements[i];
    }

    int indexNouveauJeu = jeuxDejaDeveloppes;

    for (int i = 0; i < listeJeux.nElements; i++) {
        if (listeJeux.elements[i]->developpeur == paireNomJeux_.first) {
            nouvelleListe[indexNouveauJeu] = listeJeux.elements[i];
            indexNouveauJeu++;
        }
    }

    delete[] paireNomJeux_.second.elements;

    paireNomJeux_.second.elements = nouvelleListe;
    paireNomJeux_.second.nElements = nouvelleTaille;
}

void Developpeur::afficherJeuxDeveloppes() const {
    cout << "Jeux développés par " << paireNomJeux_.first << ":" << endl;
    for (int i = 0; i < paireNomJeux_.second.nElements; i++) {
        cout << "- " << paireNomJeux_.second.elements[i]->titre << endl;
    }
}