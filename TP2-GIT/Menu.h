/*
* Titre : Menu.h - Travail Pratique #2
* Date : 18 Janvier 2019
* Auteur : Allan BEDDOUK
*/

#ifndef MENU_H
#define MENU_H

#include "Plat.h"
#include <fstream>
#include <vector>

enum TypeMenu { Matin, Midi, Soir };
const int MAXPLAT = 5;
class Menu {
public:
	/// constructeurs
	Menu();
	Menu(string fichier, TypeMenu type);
	Menu(Menu& menuCopie);

	///destructeur
	~Menu();

	///methodes en plus
	Plat* trouverPlat(const string& nom) const; // A MODIFIER
	Plat * trouverPlatMoinsCher() const; // Utilise les vecteurs (NE PAS MODIFIER)
	Menu& operator+=(const Plat & plat); // A MODIFIER
	bool lireMenu(const string& fichier);
	Menu& operator=(const Menu menuCopie);
	friend ostream& operator<<(ostream& o, Menu const& ceMenu);

private:
	vector<Plat*> listePlats_;
	TypeMenu type_;

};

#endif // !MENU_H