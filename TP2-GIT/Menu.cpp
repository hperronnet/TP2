/*
* Titre : Menu.cpp - Travail Pratique #2
* Date : 18 Janvier 2019
* Auteur : Allan BEDDOUK
*/

#include "Menu.h"
#include <vector>
//constructeurs

Menu::Menu()
{
	type_ = Matin;

}

Menu::Menu(Menu& menuCopie)
{
	type_ = menuCopie.type_;

	for (unsigned i = 0; i < menuCopie.listePlats_.size(); i++)
	{
		listePlats_.push_back(new Plat(*menuCopie.listePlats_[i]));
	}
}


Menu::Menu(string fichier, TypeMenu type) {
	type_ = type;

	//lecture du fichier -- creation du menu
	lireMenu(fichier);
}

//destructeur
Menu::~Menu() {
	for (int i = 0; i < listePlats_.size(); i++)
		delete listePlats_[i];
	listePlats_.clear();
}

//autres methodes

bool Menu::lireMenu(const string& fichier) {
	ifstream file(fichier, ios::in);

	if (!file) {
		//cout << "ERREUR : le fichier n'a pas pu etre ouvert" << endl;
		return false;
	}
	else {
		string type;
		switch (type_) {
		case Matin:
			type = "-MATIN";
			break;
		case Midi:
			type = "-MIDI";
			break;
		case Soir:
			type = "-SOIR";
			break;
		}
		string ligne;

		string nom;

		string prixString;
		double prix;

		string coutString;
		int leCout;


		// lecture
		while (!file.eof()) {
			getline(file, ligne);
			//trouver le bon type de menu (section)
			if (ligne == type) {
				//commencer a lire -- s'arrete si fin du fichier ou encore si on arrive a une nouvelle section du menu
				getline(file, ligne);
				int curseur = 0;
				while (ligne[0] != '-' && !file.eof()) {
					//trouver le nom
					for (int i = 0; i < int(ligne.size()); i++) {
						if (ligne[i] == ' ') {
							curseur = i;
							break;
						}
						nom += ligne[i];
					}
					//trouver le prix

					for (int i = curseur + 1; i < int(ligne.size()); i++) {
						if (ligne[i] == ' ') {
							curseur = i;
							break;
						}
						prixString += ligne[i];

					}
					//passer le prixString en double --- indice dans l'enonce
					prix = stof(prixString.c_str());

					for (int i = curseur + 1; i < int(ligne.size()); i++) {
						if (ligne[i] == ' ')
							break;
						coutString += ligne[i];
					}

					leCout = int(stof(coutString.c_str()));

					Plat newPlat(nom, prix, leCout);
					*this += newPlat;
					nom = "";
					prixString = "";
					coutString = "";

					getline(file, ligne);
				}
			}
		}

		file.close();
		return true;
	}
}

Menu & Menu::operator=(const Menu menuCopie)
{
	type_ = menuCopie.type_;

	listePlats_.clear();

	for (unsigned i = 0; i < menuCopie.listePlats_.size(); i++)
	{
		listePlats_.push_back(new Plat(*menuCopie.listePlats_[i]));
	}
	return *this;
}

Plat * Menu::trouverPlatMoinsCher() const
{
	Plat minimum(*listePlats_[0]);
	int found = -1;

	for (unsigned i = 0; i < listePlats_.size(); ++i)
	{
		if (*listePlats_[i] < minimum)
		{
			minimum = *listePlats_[i];
			found = i;
		}
	}

	return listePlats_[found];

}

Menu& Menu::operator+=(const Plat & plat)
{
	listePlats_.push_back(new Plat(plat));
	return *this;
}

Plat* Menu::trouverPlat(const string& nom) const {

	for (unsigned i = 0; i < listePlats_.size(); i++) {
		if (listePlats_[i]->getNom() == nom)
			return listePlats_[i];
	}
	return nullptr;
}

ostream & operator<<(ostream & o, Menu const & ceMenu)
{
	for (unsigned i = 0; i < ceMenu.listePlats_.size(); i++) {
		o << "   " << *ceMenu.listePlats_[i] << "\n";
	}
	o << "\n";
	return o;
}
