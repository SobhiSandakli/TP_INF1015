#pragma once
#include <iostream>
#include <memory>
#include <cassert>
#include "gsl/span"
#include "cppitertools/range.hpp"
using namespace std;

template <typename T>
class Liste
{
public:
	//TODO: Constructeurs et surcharges d'opérateurs
	Liste() : nElements_(0), capacite_(0) {}

	Liste(const Liste<T>& other)
		: nElements_(other.nElements_), capacite_(other.capacite_), elements(make_unique<shared_ptr<T>[]>(capacite_))
	{
		for (unsigned i = 0; i < nElements_; ++i) {
			elements[i] = other.elements[i];
		}
	}

	const shared_ptr<T> operator [](int index) const {
		return elements[index];
	}

	shared_ptr<T>& operator [](int index) {
		return elements[index];
	}

	//TODO: Méthode pour ajouter un élément à la liste
	void ajouterElement(shared_ptr<T>& element)
	{
		if (nElements_ == capacite_)
			changerCapacite(capacite_ == 0 ? 1 : capacite_ *2);
		elements[nElements_++] = element;
	}

	// Pour size, on utilise le même nom que les accesseurs de la bibliothèque standard, qui permet d'utiliser certaines fonctions de la bibliotheque sur cette classe.
	unsigned size() const { return nElements_; }
	unsigned getCapacite() const { return capacite_; }

	//TODO: Méthode pour changer la capacité de la liste
	void changerCapacite(int taille)
	{
		unique_ptr<shared_ptr<T>[]> nouveauTableau = make_unique<shared_ptr<T>[]>(taille);
		for (int i = 0; i < nElements_; i++) {
			nouveauTableau[i] = elements[i];
		}
		elements = move(nouveauTableau);
		capacite_ = taille;
	}

	//TODO: Méthode pour trouver une élément selon un critère (lambda).
	shared_ptr<T> trouverElement(function<bool(const shared_ptr<T>&)> func)
	{
		for (int i = 0; i < nElements_ ; i++) {
			if (func(elements[i])) {
				return elements[i];
			}
		}
		return nullptr;

	}

private:
		unsigned nElements_;
		unsigned capacite_;
		//TODO: Attribut contenant les éléments de la liste.
		unique_ptr<shared_ptr<T>[]> elements;
};