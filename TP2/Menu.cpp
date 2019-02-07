/*
* Titre : Menu.cpp - Travail Pratique #1
* Date : 31/01/2019
* Auteurs : Philippe Maisonneuve - 1959052
*			Hugo Perronnet - 1885263
*/


#include "Menu.h"
#include <fstream>

//constructeur par �faut
Menu::Menu() : capacite_(MAXPLAT), nbPlats_(0), type_(Matin)
{
	listePlats_ = new Plat*[capacite_];
}

//constructeur
Menu::Menu(string fichier, TypeMenu type) : capacite_(MAXPLAT), nbPlats_(0), type_(type)
{
	listePlats_ = new Plat*[capacite_];
	lireMenu(fichier);	
}

//D�structeur
Menu::~Menu() { //Destructeur

	for (int i = 0; i < nbPlats_; i++) {
		listePlats_[i] = nullptr;
	}		
	delete[] listePlats_;
}

/*
* retourne le nombre de plats d'un menu
* \return le nombre de plats
*/
int Menu::getNbPlats() const
{
	return nbPlats_;
}

/*
* Affiche le menu
*/
void Menu::afficher() const
{
	for (unsigned int i = 0; i < nbPlats_; i++) {
		{
			listePlats_[i]->afficher();
		}
	}
	cout << endl;
}

/*
* d�finit le moment de la journ�e
* \param nom : le nom du plat
* \return le plat si il est trouv�, ullptr sinon
*/
Plat * Menu::trouverPlat(string & nom)
{
	for (unsigned int i = 0; i < nbPlats_; i++) {
		if (nom == listePlats_[i]->getNom()) {
			return listePlats_[i];
		}
	}
	return nullptr;
}

/*
* Ajoute un plat au menu
* \param plat : le plat
*/
void Menu::ajouterPlat(Plat & plat)
{
	Plat* pointeurPlat = new Plat;
	*pointeurPlat = plat;
	listePlats_[nbPlats_] = pointeurPlat;
	nbPlats_++;
}

/*
* Ajoute un plat au menu
* \param nom : le nom du plat
*		 montant : montant du plat
*		 cout : le cout du plat pour le restaurant
*/
void Menu::ajouterPlat(string & nom, double montant, double cout)
{
	Plat* pointeurPlat = new Plat;
	Plat plat(nom, montant, cout);
	*pointeurPlat = plat;
	listePlats_[nbPlats_] = pointeurPlat;
	nbPlats_++;
}

/*
* Lit le fichier .txt et ajouter chaque plat au menu en fonction du moment de la journ�e
* \param fichier : le nom du fichier texte � ouvrir
* \return le succ�s ou echec de la lecture
*/
bool Menu::lireMenu(string & fichier)
{
	ifstream liste(fichier, ios::in);
	string ligneLu;
	bool finit = false;
	while (!ws(liste).eof())
	{
		getline(liste, ligneLu);
		if ((ligneLu == "-MATIN" && type_ == Matin) || (ligneLu == "-MIDI" && type_ == Midi) || (ligneLu == "-SOIR" && type_ == Soir)) 
		{
			while (!ws(liste).eof() && !finit)
			{
				string nomPlat;
				liste >> nomPlat;
				if (nomPlat[0] == '-') 
				{
					finit = 1;
					break;
				}
								
				double prix;
				double cout;
				liste >> prix >> cout;
				ajouterPlat(nomPlat, prix, cout);
			}
		}
	}
	return false;
}
