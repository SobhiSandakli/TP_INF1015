#ifndef PERSONNAGE_HPP
#define PERSONNAGE_HPP
#include <iostream>
#include "affichable.hpp"
using namespace std;

class Personnage : public Affichable {
public:
    Personnage(const string& nom, const string& titreDuJeu) : nom_(nom), titreDuJeu_(titreDuJeu) {}

    virtual ~Personnage() = default;

    void changerCouleur(ostream& os, char couleur = ' ') const  {
        switch (couleur) {
        case 'r':
            os << "\033[91m";
            break;
        case 'b':
            os << "\033[94m";
            break;
        case 'p':
            os << "\033[35m";
            break;
        default:
            os << "\033[0m";
        }
    }

    void afficher(ostream& os, char couleur = ' ') const {
        changerCouleur(os, couleur);
        os << "Nom : " << nom_ << endl;
        os << "Parution : " << titreDuJeu_ << endl;
        changerCouleur(os);

    }

    string getNom() const {
        return nom_;
    }

    string getTitre() const {
        return titreDuJeu_;
    }

private:
    string nom_;
    string titreDuJeu_;
};
#endif