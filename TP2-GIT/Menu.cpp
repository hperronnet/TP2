/*
* Titre : Restaurant.cpp - Travail Pratique #2
* Date : 18 Janvier 2019
* Auteur : Allan BEDDOUK
*/

#include "Restaurant.h"

//constructeurs
Restaurant::Restaurant() {
	nom_ = new string("Inconnu");

	chiffreAffaire_ = 0;

	momentJournee_ = Matin;

	menuMatin_ = new Menu("menu.txt", Matin);
	menuMidi_ = new Menu("menu.txt", Midi);
	menuSoir_ = new Menu("menu.txt", Soir);

	capaciteTables_ = INTTABLES;
	nbTables_ = 0;
	tables_ = new Table*[capaciteTables_];


}

Restaurant::Restaurant(const string& fichier, const string& nom, TypeMenu moment) {
	nom_ = new string(nom);

	chiffreAffaire_ = 0;

	momentJournee_ = moment;

	menuMatin_ = new Menu(fichier, Matin);
	menuMidi_ = new Menu(fichier, Midi);
	menuSoir_ = new Menu(fichier, Soir);


	capaciteTables_ = INTTABLES;
	nbTables_ = 0;
	tables_ = new Table*[capaciteTables_];

	lireTable(fichier);
}
//destructeur
Restaurant::~Restaurant() {
	delete nom_;
	delete menuMatin_;
	delete menuMidi_;
	delete menuSoir_;

	//A MODIFIER
	for (int i = 0; i < nbTables_; i++)
		delete tables_[i];
	delete[] tables_;
}


//setter

void Restaurant::setMoment(TypeMenu moment) {
	momentJournee_ = moment;
}
//getters
string Restaurant::getNom() const {
	return *nom_;
}

TypeMenu Restaurant::getMoment() const {
	return momentJournee_;
}

//autres methodes


void Restaurant::libererTable(int id) {
	for (int i = 0; i < nbTables_; i++) {
		if (id == tables_[i]->getId()) {
			chiffreAffaire_ += tables_[i]->getChiffreAffaire();
			tables_[i]->libererTable();
		}
	}
}
ostream opperator << (ostream o, Restaurant restaurant) const
{
	o << "Le restaurant " << restaurant->nom_;
	if (restaurant.chiffreAffaire_ != 0)
		o << " a fait un chiffre d'affaire de : " << restaurant.chiffreAffaire_ << "$" << endl;
	else
		o << " n'a pas fait de benefice ou le chiffre n'est pas encore calcule." << endl;
	o << "-Voici les tables : " << endl;
	for (int i = 0; i < restaurant.nbTables_; i++) {
		o << "\t" << restaurant.tables_[i] << endl;
	}
	o << endl;


	o << "-Voici son menu : " << endl
		<< "Matin : " << endl << restaurant.menuMatin_
		<< "Midi : " << endl << restaurant.menuMidi_
		<< "Soir : " << endl << restaurant.menuSoir_;
}

void Restaurant::commanderPlat(const string& nom, int idTable) {
	Plat* plat = nullptr;
	int index;
	for (int i = 0; i < nbTables_; i++) {
		if (idTable == tables_[i]->getId()) {
			index = i;
			switch (momentJournee_) {
			case Matin:
				plat = menuMatin_->trouverPlat(nom);
				break;
			case Midi:
				plat = menuMidi_->trouverPlat(nom);
				break;
			case Soir:
				plat = menuSoir_->trouverPlat(nom);
				break;
			}
		}
	}
	if (plat != nullptr && tables_[index]->estOccupee()) {
		tables_[index]->commander(plat);
	}
	else cout << "Erreur : table non occupee ou plat introuvable" << endl;
}

void Restaurant::lireTable(const string& fichier) {
	ifstream file(fichier, ios::in);

	if (file) {
		string ligne;

		string idString;
		int id;

		string nbPersonnesString;
		int nbPersonnes;

		int curseur;
		while (!file.eof()) {
			getline(file, ligne);
			if (ligne == "-TABLES") {
				while (!file.eof()) {
					getline(file, ligne);
					for (int i = 0; i < ligne.size(); i++) {
						if (ligne[i] == ' ') {
							curseur = i;
							break;
						}
						idString += ligne[i];
					}

					id = stoi(idString);

					nbPersonnesString = ligne.substr(curseur + 1);
					nbPersonnes = stoi(nbPersonnesString);

					ajouterTable(id, nbPersonnes);
					nbPersonnesString = "";
					idString = "";
				}
			}
		}
		file.close();
	}
}

void Restaurant::ajouterTable(int id, int nbPlaces) {
	// A MODIFIER
	if (nbTables_ == capaciteTables_) {
		capaciteTables_ *= 2;
		Table** temp = new Table*[capaciteTables_];

		for (int i = 0; i < nbTables_; i++) {
			temp[i] = tables_[i];
		}

		delete[] tables_;
		tables_ = temp;

	}

	tables_[nbTables_] = new Table(id, nbPlaces);
	nbTables_++;
}

void Restaurant::placerClients(int nbClients) {
	int indexTable = -1;
	int minimum = 100;


	for (int i = 0; i < nbTables_; i++) {
		if (tables_[i]->getNbPlaces() >= nbClients && !tables_[i]->estOccupee() && tables_[i]->getNbPlaces() < minimum) {
			indexTable = i;
			minimum = tables_[i]->getNbPlaces();
		}
	}
	if (indexTable == -1) {
		cout << "Erreur : il n'y a plus/pas de table disponible pour le client. " << endl;
	}
	else
		tables_[indexTable]->placerClient(nbClients);
}

bool operator<(Restaurant Restaurant, Restaurant RestaurantCompare)
{
	if (Restaurant.chiffreAffaire_ < RestaurantCompare.chiffreAffaire_)
		return true;
	else
		return false;
}
Restaurant* operator=(Restaurant restaurantCopie)
{
	nom_ = RestaurantCopie.nom;

	chiffreAffaire_ = restaurantCopie.chiffreAffaire_;

	momentJournee_ = restaurantCopie.momentJournee_;

	menuMatin_ = restaurantCopie.menuMatin_;
	menuMidi_ = restaurantCopie.menuMidi_;
	menuSoir_ = restaurantCopie.menuSoir_;

	capaciteTables_ = restaurantCopie.capaciteTables_;
	nbTables_ = restaurantCopie.nbTables_;
	tables_ = restaurantCopie.tables_
		return this;
}

Restaurant(const Restaurant& RestaurantCopie) {
	nom_ = RestaurantCopie.nom;

	chiffreAffaire_ = restaurantCopie.chiffreAffaire_;

	momentJournee_ = restaurantCopie.momentJournee_;

	menuMatin_ = restaurantCopie.menuMatin_;
	menuMidi_ = restaurantCopie.menuMidi_;
	menuSoir_ = restaurantCopie.menuSoir_;

	capaciteTables_ = restaurantCopie.capaciteTables_;
	nbTables_ = restaurantCopie.nbTables_;
	tables_ = restaurantCopie.tables_
}