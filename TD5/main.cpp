#include "Personnage.hpp"
#include "Heros.hpp"
#include "Vilain.hpp"
#include "VilainHeros.hpp"
#include "ListeLiee.hpp"
#include "Iterateur.hpp"
#include <fstream>
#include <vector>
#include <functional>
#include "cppitertools/range.hpp"
#include "bibliotheque_cours.hpp"
#include <map>
using namespace std;
using namespace iter;

using UInt8  = uint8_t;
using UInt16 = uint16_t;

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

template <typename T>
vector<T> lireFichier(istream& fichier)
{
	vector<T> elements;
	for ([[maybe_unused]] int i : range(lireUint16(fichier)))
		elements.push_back(T(fichier));
	return elements;
}

ifstream ouvrirLectureFichierBinaire(const string& nomFichier)
{
	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);
	return fichier;
}

// Permet d'avoir une référence non-const à un objet temporaire.
template <typename T> T& temporaireModifiable(T&& objet) { return objet; }

template <typename T>
vector<T> lireFichier(const string& nomFichier)
{
	return lireFichier<T>(temporaireModifiable(
		ouvrirLectureFichierBinaire(nomFichier)));
}

template <typename T>
Iterateur<T> trouverParNom(ListeLiee<T>& liste, const string& nom)
{
	Iterateur<T> fin = liste.end();
	for (Iterateur<T> pos = liste.begin(); pos != fin; pos.avancer()) {
		if ((*pos).getNom() == nom)
			return pos;
	}
	return fin;
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
		"═════════════════════════════════════════════════════════════════════════";

	static const string separateurSections = "\033[95m" + trait + "\033[0m\n";
	static const string separateurElements = "\033[33m" + trait + "\033[0m\n";

	//{ Solutionnaire du TD4:
	vector<Heros> heros = lireFichier<Heros>("heros.bin");
	vector<Vilain> vilains = lireFichier<Vilain>("vilains.bin");
	vector<unique_ptr<Personnage>> peronnages;  // Doit être des pointeurs pour le polymorphisme, l'énoncé ne force pas les unique_ptr.

	#if 1 //TODO: Vous n'avez pas à conserver ces affichages pour le TD5, ils sont pour le solutionnaire du TD4:
	cout << separateurSections << "Heros:" << endl;
	for (auto& h : heros) {
		cout << separateurElements;
		h.changerCouleur(cout, 0);
		h.afficher(cout);
	}

	cout << separateurSections << "Vilains:" << endl;
	for (auto& v : vilains) {
		cout << separateurElements;
		v.changerCouleur(cout, 0);
		v.afficher(cout);
	}

	for (auto& h : heros)
		peronnages.push_back(make_unique<Heros>(h));

	for (auto& v : vilains)
		peronnages.push_back(make_unique<Vilain>(v));

	peronnages.push_back(make_unique<VilainHeros>(vilains[1], heros[2]));

	cout << separateurSections << "Personnages:" << endl;
	for (auto& p : peronnages) {
		cout << separateurElements;
		p->changerCouleur(cout, 0);
		p->afficher(cout);
	}
	cout << separateurSections << "Un autre vilain heros (exemple de l'énoncé du TD):" << endl;
	VilainHeros kefkaCrono(vilains[2], heros[0]);
	kefkaCrono.changerCouleur(cout,1);
	kefkaCrono.afficher(cout);
	#endif
	//}
	cout << endl << endl << "----------------------------------------------------------" << endl;
	cout << "Début des TODOS"  << endl;
	cout << "----------------------------------------------------------" << endl << endl;

	//TODO: Transférez les héros du vecteur heros dans une ListeLiee.
	ListeLiee<Heros> listeHeros;
	for (auto&& hero : heros) {
		listeHeros.push_back(hero); 
	}

	cout << "Taille de la liste au début est : " << listeHeros.size() << endl << endl;

	//TODO: Créez un itérateur sur la liste liée à la position du héros Alucard
	// Servez-vous de la fonction trouverParNom définie plus haut
	Iterateur<Heros> iterAlucard = trouverParNom(listeHeros, "Alucard");


	//TODO: Servez-vous de l'itérateur créé précédemment pour trouver l'héroine Aya Brea, en sachant qu'elle se trouve plus loin dans la liste.
	Iterateur<Heros> itAyaBrea;
	Iterateur<Heros> fin = listeHeros.end();

	for (Iterateur<Heros> pos = iterAlucard; pos != fin; pos.avancer()) {
		if ((*pos).getNom() == "Aya Brea"){itAyaBrea = pos;}
	}


	//TODO: Ajouter un hero bidon à la liste avant Aya Brea en vous servant de l'itérateur.
	//TODO: Assurez-vous que la taille de la liste est correcte après l'ajout.
	Heros herotest("Hero Test", "Jeu imaginaire", "Ennemi Test");
	listeHeros.insert(itAyaBrea, herotest);
	cout << "Taille de la liste après l'ajout est : " << listeHeros.size() << endl << endl;

	//TODO: Reculez votre itérateur jusqu'au héros Mario et effacez-le en utilisant l'itérateur, puis affichez le héros suivant dans la liste (devrait êter "Naked Snake/John").
	//TODO: Assurez-vous que la taille de la liste est correcte après le retrait.
	cout << "Le héros suivant dans la liste: " << endl;
	for (Iterateur<Heros> pos = itAyaBrea; pos != listeHeros.begin(); pos.reculer()) {
		if ((*pos).getNom() == "Mario"){
			pos = listeHeros.erase(pos);
			(*pos).afficher(cout);
			}
	}
	cout << endl << "Taille de la liste après le retrait est : " << listeHeros.size() << endl << endl;

	//TODO: Effacez le premier élément de la liste.
	Iterateur<Heros> premierElement = listeHeros.begin();
	listeHeros.erase(premierElement);

	//TODO: Affichez votre liste de héros en utilisant un itérateur. La liste débute avec le héros Randi et n'a pas Mario.
	//Servez-vous des methodes begin et end de la liste...
	cout << endl << "Liste des heros (en utilisant un itérateur): " << endl << endl;
	for (Iterateur<Heros> it = listeHeros.begin(); it != listeHeros.end(); it.avancer()) {
		(*it).afficher(cout);
	}

	//TODO: Refaite le même affichage mais en utilisant une simple boucle "for" sur intervalle.
	cout << endl << endl <<  "Liste des heros (en utilisant une simple boucle for sur intervalle): " << endl<< endl;
	for (Heros& heros : listeHeros) {
		heros.afficher(cout);
	}

	//TODO: Utilisez un conteneur pour avoir les héros en ordre alphabétique (voir point 2 de l'énoncé).
	map<string, Heros> uneMap;
	for (Heros& hero: listeHeros) {
		uneMap.map::insert({hero.getNom(), hero});
	}
	cout << endl << endl <<  "Les éléments du conteneurs sont : " << endl;
	for(auto& hero: uneMap) {
		cout << "Hero: " << hero.first << endl;
	}

	//Question 2.2
	// La complexité de cette recherche est O(log(n)), où n représente la taille de la map.
	//  Cette efficacité est due au fait que les éléments de la map sont triés en fonction de 
	//  l'ordre alphabétique de leur clé (le nom du héros). 
	//  Le nombre d'opérations élémentaires nécessaires pour trouver un élément est en moyenne logarithmique par 
	//  rapport à la taille de la map. 

	//Question 2.3
	// La liste liée effectue ses recherches en O(n), où n représente la taille de la liste. 
	// Cela signifie que le temps nécessaire pour effectuer une recherche dépend directement de la taille de la liste. 
	// Comparativement, pour de grands ensembles de données, la complexité de O(log(n)) de la map serait plus performante 
	// que le O(n) de la liste liée. Même si dans ce cas particulier, il n'y a que 9 héros, le logarithme l'emporte en moyenne, 
	// car log(base 2) de n est toujours inférieur à n pour toute valeur de n. 

}
