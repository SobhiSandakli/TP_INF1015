#pragma once
#include <string>
#include <vector>
#include "ListeJeux.hpp"
using namespace std;

class Developpeur
{
public:
    Developpeur(string nom);
    ~Developpeur();
    string getNomDeveloppeur() const;
    int compterJeuxDansListe(const ListeJeux& listeJeux) const;
    void mettreAJourListeJeux(const ListeJeux& listeJeux);
    void afficherJeuxDeveloppes() const;

private:
    pair<string, ListeJeux> paireNomJeux_;
};
