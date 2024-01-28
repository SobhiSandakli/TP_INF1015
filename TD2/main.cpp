#include "Jeu.hpp"
#include <iostream>
#include <fstream>
#include "cppitertools/range.hpp"
#include "gsl/span"
#include "bibliotheque_cours.hpp"
#include "verification_allocation.hpp"
#include "debogage_memoire.hpp"  //NOTE: Incompatible avec le "placement new", ne pas utiliser cette entête si vous utilisez ce type de "new" dans les lignes qui suivent cette inclusion.
#include "ListeDeveloppeurs.hpp"

using namespace std;
using namespace iter;
using namespace gsl;

//bibliotheque_cours::BreakpointSurAllocations breakpointSurAllocations = { 40U, 51U, 76U, 90U, 113U, 123U, 134U, 156U, 170U, 181U, 260U, 268U, 290U, 301U, 323U, 334U, 345U, 369U, 383U, 408U, 419U, 433U, 457U, 468U, 512U, 535U, 546U, 570U, 581U, 602U, 616U, 642U, 653U, 664U, 688U, 699U, };

#pragma region "Fonctions de base pour vous aider"
typedef uint8_t UInt8;
typedef uint16_t UInt16;
UInt8 lireUint8(istream& fichier)
{
	UInt8 valeur = 0;
	fichier.read((char*)&valeur, sizeof(valeur));
	return valeur;
}
UInt16 lireUint16(istream& fichier)
{
	UInt16 valeur = 0;
	fichier.read((char*)&valeur, sizeof(valeur));
	return valeur;
}
string lireString(istream& fichier)
{
	string texte;
	texte.resize(lireUint16(fichier));
	fichier.read((char*)&texte[0], streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}
gsl::span<Jeu*> spanListeJeux(const ListeJeux& liste)
{
	return gsl::span(liste.elements, liste.nElements);
}
gsl::span<Designer*> spanListeDesigners(const ListeDesigners& liste)
{
	return gsl::span(liste.elements, liste.nElements);
}
#pragma endregion

//TODO: Fonction qui cherche un designer par son nom dans une ListeJeux.
// Cette fonction renvoie le pointeur vers le designer si elle le trouve dans un des jeux de la ListeJeux. 
// En cas contraire, elle renvoie un pointeur nul.
Designer* trouverDesigner(string nom, const ListeJeux& liste) {
	for (Jeu* jeu : spanListeJeux(liste)) {
		for (Designer* designer : spanListeDesigners(jeu->designers)) {
			if (designer->nom == nom) {
				return designer;
			}
		}
	}
	return nullptr;
}

Designer* lireDesigner(istream& fichier, const ListeJeux& liste)
{
	Designer designer = {}; // On initialise une structure vide de type Designer.
	designer.nom = lireString(fichier);
	designer.anneeNaissance = lireUint16(fichier);
	designer.pays = lireString(fichier);
	// Rendu ici, les champs précédents de la structure designer sont remplis
	// avec la bonne information.

	//TODO: Ajouter en mémoire le designer lu. Il faut revoyer le pointeur créé.
	// Attention, valider si le designer existe déjà avant de le créer, 
	// sinon on va avoir des doublons car plusieurs jeux ont des designers en commun dans le fichier binaire. 
	// Pour ce faire, cette fonction aura besoin de la liste de jeux principale en paramètre.
	// Afficher un message lorsque l'allocation du designer est réussie.

	Designer* des = trouverDesigner(designer.nom, liste);
	if (des == nullptr) {
		des = new Designer();
		des->nom = designer.nom;
		des->anneeNaissance = designer.anneeNaissance;
		des->pays = designer.pays;
	}

	return des; //TODO: Retourner le pointeur vers le designer crée.
}

//TODO: Fonction qui change la taille du tableau de jeux de ListeJeux.
// Cette fonction doit recevoir en paramètre la nouvelle capacité du nouveau tableau. 
// Il faut allouer un nouveau tableau assez grand, copier ce qu'il y avait dans l'ancien, et éliminer l'ancien trop petit.
// N'oubliez pas, on copie des pointeurs de jeux. Il n'y a donc aucune nouvelle allocation de jeu ici !
void changeTailleTableau(ListeJeux& liste, int taille) {
	Jeu** nouvelleListe = new Jeu * [taille];
	int i = 0;
	for (Jeu* jeu : spanListeJeux(liste)) {
		nouvelleListe[i++] = jeu;
	}
	delete[] liste.elements;
	liste.elements = nouvelleListe;
	liste.capacite = taille;
}

//TODO: Fonction pour ajouter un Jeu à ListeJeux.
// Le jeu existant déjà en mémoire, on veut uniquement ajouter le pointeur vers le jeu existant. 
// De plus, en cas de saturation du tableau elements, cette fonction doit doubler la taille du tableau elements de ListeJeux.
// Utilisez la fonction pour changer la taille du tableau écrite plus haut.
void ajouterJeuListeJeux(ListeJeux& liste, Jeu* jeu) {
	if (liste.nElements == liste.capacite) {
		changeTailleTableau(liste, liste.capacite == 0 ? 1 : liste.capacite * 2);
	}
	liste.elements[liste.nElements++] = jeu;
}

//TODO: Fonction qui enlève un jeu de ListeJeux.
// Attention, ici il n'a pas de désallocation de mémoire. Elle enlève le pointeur de la ListeJeux, mais le jeu pointé existe encore en mémoire.
// Puisque l'ordre de la ListeJeux n'a pas être conservé, on peut remplacer le jeu à être retiré par celui présent en fin de liste et 
// décrémenter la taille de celle-ci.
void enleveJeuListeJeux(ListeJeux& liste, Jeu* jeu) {
	for (int i = 0; i < liste.nElements; i++) {
		if (liste.elements[i] == jeu) {
			liste.elements[i] = liste.elements[liste.nElements-- - 1];
			break;
		}
	}
}


Jeu* lireJeu(istream& fichier, ListeJeux& liste) {
	Jeu jeu = {}; // Initialisez une structure vide de type Jeu
	jeu.titre = lireString(fichier);
	jeu.anneeSortie = lireUint16(fichier);
	jeu.developpeur = lireString(fichier);
	jeu.designers.nElements = lireUint8(fichier);

	// Vérifiez si l'allocation du jeu a réussi.
	Jeu* nouveauJeu = new Jeu(jeu);
	nouveauJeu->designers.elements = new Designer * [jeu.designers.nElements];
	// Parcourez les designers et ajoutez-les au jeu.
	for (int i = 0; i < jeu.designers.nElements; i++) {
		Designer* des = lireDesigner(fichier, liste);
		nouveauJeu->designers.elements[i] = des;

		// Ajoutez le jeu à la liste des jeux auxquels le designer a participé.
		ajouterJeuListeJeux(des->listeJeuxParticipes, nouveauJeu);
	}

	return nouveauJeu;
}


ListeJeux creerListeJeux(const string& nomFichier) {
	ifstream fichier(nomFichier, ios::binary);
	int nElements = lireUint16(fichier);
	ListeJeux listeJeux = {};

	for (int i = 0; i < nElements; i++) {
		Jeu* jeu = lireJeu(fichier, listeJeux);

		// Assurez-vous que la lecture du jeu a réussi avant de l'ajouter à la liste.
		if (jeu) {
			ajouterJeuListeJeux(listeJeux, jeu);
		}
	}

	return listeJeux;
}
//TODO: Fonction pour détruire un designer (libération de mémoire allouée).
// Lorsqu'on détruit un designer, on affiche son nom pour fins de débogage.
void detruireDesigner(Designer* designer) {
	if (designer) {
		cout << "Destruction du designer : " << designer->nom << endl;
		delete[] designer->listeJeuxParticipes.elements;

		delete designer;
	}
}



//TODO: Fonction qui détermine si un designer participe encore à un jeu.
bool designerEtJeu(const Designer& des, const Jeu& jeu) {
	for (int i = 0; i < jeu.designers.nElements; i++) {
		if (jeu.designers.elements[i]->nom == des.nom) {
			return true;
		}
	}
	return false;
}

//TODO: Fonction pour détruire un jeu (libération de mémoire allouée).
// Attention, ici il faut relâcher toute les cases mémoires occupées par un jeu.
// Par conséquent, il va falloir gérer le cas des designers (un jeu contenant une ListeDesigners).
// On doit commencer par enlever le jeu à détruire des jeux qu'un designer a participé (listeJeuxParticipes). 
// Si le designer n'a plus de jeux présents dans sa liste de jeux participés, il faut le supprimer.  
// Pour fins de débogage, affichez le nom du jeu lors de sa destruction.
void detruireJeu(Jeu* jeu) {
	cout << "Destruction du jeu : " << jeu->titre << endl;

	for (int i = 0; i < jeu->designers.nElements; i++) {
		Designer* designer = jeu->designers.elements[i];

		enleveJeuListeJeux(designer->listeJeuxParticipes, jeu);

		if (designer->listeJeuxParticipes.nElements == 0) {
			detruireDesigner(designer);
		}
	}

	delete[] jeu->designers.elements;

	delete jeu;
}



void detruireListeJeux(ListeJeux& liste) {

	for (int i = 0; i < liste.nElements; i++) {
		detruireJeu(liste.elements[i]);
	}

	delete[] liste.elements;


}

void afficherDesigner(const Designer& d)
{
	cout << "\t" << d.nom << ", " << d.anneeNaissance << ", " << d.pays << endl;
}

//TODO: Fonction pour afficher les infos d'un jeu ainsi que ses designers.
// Servez-vous de la fonction afficherDesigner ci-dessus.
void afficherInfoJeu(Jeu jeu) {
	cout << "Titre: " << jeu.titre << ", Année de sortie: " << jeu.anneeSortie << ", Développeur: " << jeu.developpeur << endl;
	for (Designer* designer : spanListeDesigners(jeu.designers))
		afficherDesigner(*designer);
}

//TODO: Fonction pour afficher tous les jeux de ListeJeux, séparés par un ligne.
// Servez-vous de la fonction d'affichage d'un jeu crée ci-dessus. 
// Votre ligne de séparation doit être différent de celle utilisée dans le main.
void afficherTousJeux(ListeJeux liste) {
	for (Jeu* jeu : spanListeJeux(liste)) {
		afficherInfoJeu(*jeu);
		cout << "-----------------------------------------------------------" << endl;
	}
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
#pragma region "Bibliothèque du cours"
	// Permet sous Windows les "ANSI escape code" pour changer de couleur
	// https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
	// les supportent normalement par défaut.
	bibliotheque_cours::activerCouleursAnsi();
#pragma endregion

	int* fuite = new int;  

	ListeJeux maListe = creerListeJeux("jeux.bin"); 

	static const string ligneSeparation = "\n\033[35m════════════════════════════════════════\033[0m\n";
	cout << ligneSeparation << endl;
	cout << "Premier jeu de la liste :" << endl;
	//TODO: Afficher le premier jeu de la liste (en utilisant la fonction).  Devrait être Chrono Trigger.
	afficherInfoJeu(*maListe.elements[0]);
	cout << ligneSeparation << endl;

	afficherTousJeux(maListe);

	detruireListeJeux(maListe); 

	delete fuite; 

	

	cout << endl << "-------------- Test pour partie 2 --------------" << endl << endl;

	// Create some games
	Jeu jeu1{ "Game1", 2020, "Elon Musk", ListeDesigners() };
	Jeu jeu2{ "Game2", 2021, "Elon Musk", ListeDesigners() };
	Jeu jeu3{ "Game3", 2019, "Steve Jobs", ListeDesigners() };
	Jeu jeu4{ "Game4", 2012, "Steve Jobs", ListeDesigners() };
	Jeu jeu5{ "Game5", 2014, "Elon Musk", ListeDesigners() };
	Jeu jeu6{ "Game6", 2000, "Steve Jobs", ListeDesigners() };

	ListeJeux liste1{ 4, 4, new Jeu * [4]{&jeu1, &jeu2, &jeu3, &jeu4} };
	ListeJeux liste2{ 2, 2, new Jeu * [2]{&jeu5, &jeu6} };


	Developpeur dev1("Elon Musk");
	Developpeur dev2("Steve Jobs");

	cout << "Nom du premier developpeur 1: " << dev1.getNomDeveloppeur() << endl;
	cout << "Nom du premier developpeur 2: " << dev2.getNomDeveloppeur() << endl << endl;

	dev1.mettreAJourListeJeux(liste1);
	dev2.mettreAJourListeJeux(liste1);

	ListeDeveloppeurs listeDev;

	listeDev.ajouterDeveloppeur(dev1);
	listeDev.ajouterDeveloppeur(dev2);
	cout << "Affichage de la liste des développeurs : " << endl;
	listeDev.afficher();

	dev1.mettreAJourListeJeux(liste2);
	dev2.mettreAJourListeJeux(liste2);
	cout << endl << "Affichage de la liste des développeurs après la mise à jour : " << endl;
	listeDev.afficher();

	listeDev.retirerDeveloppeur(dev1);
	cout << endl << "Affichage de la liste des développeurs après avoir retiré le premier développeur :" << endl;
	listeDev.afficher();

	delete[] liste1.elements;
	delete[] liste2.elements;

	return 0;
}