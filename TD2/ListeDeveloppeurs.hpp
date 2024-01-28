#pragma once
#include "Developpeur.hpp"

class ListeDeveloppeurs
{
public:
    ListeDeveloppeurs(); 
    ~ListeDeveloppeurs(); 
    void afficher() const;
    void ajouterDeveloppeur(Developpeur& dev);
    void retirerDeveloppeur(Developpeur& dev);
    void augmenterCapacite(int taille);

private:
    unsigned nElements;
    unsigned capacite;
    Developpeur** elements;

};
