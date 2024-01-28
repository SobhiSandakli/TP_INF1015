#ifndef VILAINHEROS_HPP
#define VILAINHEROS_HPP
#include <iostream>
#include "Personnage.hpp"
#include "Villain.hpp"
#include "Heros.hpp"
#include <vector>

using namespace std;

class VilainHeros : public Villain, public Heros {
public:
    VilainHeros(const Villain& villain, const Heros& heros) :
        Personnage(villain.getNom() + "-" + heros.getNom(), villain.getTitre() + "-" + heros.getTitre()),
        Villain(villain), 
        Heros(heros),
        missionSpeciale_(villain.getObjectif() + "dans le monde de " + heros.getTitre()) {}

    void afficher(ostream& os, char couleur = ' ') const {
        Personnage::afficher(os, couleur);
        changerCouleur(os, 'r');
        os << "Objectif : " << Villain::getObjectif() << endl;
        changerCouleur(os);
        changerCouleur(os, 'b');
        os << "Ennemi : " << Heros::getEnnemi() << "\nAlliés : \n";
        for (auto&& elem : Heros::getAllies())
            os << "\t" << elem << endl;
        changerCouleur(os);
        os << "Mission spéciale : " << missionSpeciale_ << endl;
        changerCouleur(os);
    }

private:
    string missionSpeciale_;
};

#endif
