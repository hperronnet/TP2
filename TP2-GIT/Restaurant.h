/*
* Titre : Restaurant.h - Travail Pratique #2
* Date : 18 Janvier 2019
* Auteur : Allan BEDDOUK
*/

#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "Table.h"
#include "Menu.h"
#include <vector>
const int INTTABLES = 6;
class Restaurant {
public:
	//constructeurs
	Restaurant();
	Restaurant(const string& fichier, const string& nom, TypeMenu moment);
	Restaurant(const Restaurant& restaurantCopie);

	//destructeur
	~Restaurant();

	//setters
	void setMoment(TypeMenu moment);
	void setNom(string *nom);

	//getters
	string getNom() const;
	TypeMenu getMoment() const;

	//Autres methodes
	void lireTable(const string& fichier);
	Restaurant& operator+=(Table& table); // A MODIFIER
	void libererTable(int id);
	friend ostream& operator<<(ostream& o, Restaurant const& ceRestaurant);
	void commanderPlat(const string& nom, int idTable);
	void placerClients(int nbClients);
	//Nouvelles methodes
	Restaurant& operator=(const Restaurant& restaurantCopie);
	friend bool operator<(Restaurant restaurant, Restaurant restaurantCompare);



private:
	string* nom_;

	double chiffreAffaire_;
	TypeMenu momentJournee_;

	//differents menus en fonction du moment de la journee
	Menu* menuMatin_;
	Menu* menuMidi_;
	Menu* menuSoir_;

	// A MODIFIER

	//liste des tables
	vector<Table*> tables_;
};
#endif // !RESTAURANT_H