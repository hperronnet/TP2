/*
* Titre : Restaurant.cpp - Travail Pratique #2
* Date : 18 Janvier 2019
* Auteur : Allan BEDDOUK
*/

#include "Restaurant.h"
#include <vector>

//constructeurs
Restaurant::Restaurant() {
	nom_ = new string("Inconnu");

	chiffreAffaire_ = 0;

	momentJournee_ = Matin;

	menuMatin_ = new Menu("menu.txt", Matin);
	menuMidi_ = new Menu("menu.txt", Midi);
	menuSoir_ = new Menu("menu.txt", Soir);

	//vector <Table*> tables_;


}

Restaurant::Restaurant(const string& fichier, const string& nom, TypeMenu moment) {
	nom_ = new string(nom);

	chiffreAffaire_ = 0;

	momentJournee_ = moment;

	menuMatin_ = new Menu(fichier, Matin);
	menuMidi_ = new Menu(fichier, Midi);
	menuSoir_ = new Menu(fichier, Soir);
	//vector <Table*> tables_;

	lireTable(fichier);
}

Restaurant::Restaurant(const Restaurant & restaurantCopie) : chiffreAffaire_(restaurantCopie.chiffreAffaire_), 
momentJournee_(restaurantCopie.momentJournee_)
{
	nom_ = new string(*restaurantCopie.nom_);

	menuMatin_ = new Menu(*restaurantCopie.menuMatin_);
	menuMidi_ = new Menu(*restaurantCopie.menuMidi_);
	menuSoir_ = new Menu(*restaurantCopie.menuSoir_);

	for (unsigned i = 0; i < restaurantCopie.tables_.size(); i++)
	{
		tables_.push_back(new Table(*restaurantCopie.tables_[i]));
	}

}
//destructeur
Restaurant::~Restaurant() {
	delete nom_;
	delete menuMatin_;
	delete menuMidi_;
	delete menuSoir_;

	//A MODIFIER
	for (unsigned i = 0; i < tables_.size(); i++)
		delete tables_[i];
	tables_.clear();
}

//setter
void Restaurant::setMoment(TypeMenu moment) {
	momentJournee_ = moment;
}

void Restaurant::setNom(string *nom)
{
	nom_ = nom;
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
	for (unsigned i = 0; i < tables_.size(); i++) {
		if (id == tables_[i]->getId()) {
			chiffreAffaire_ += tables_[i]->getChiffreAffaire();
			tables_[i]->libererTable();
		}
	}
}

void Restaurant::commanderPlat(const string& nom, int idTable) {
	Plat* plat = nullptr;
	int index = 0;
	for (unsigned i = 0; i <tables_.size(); i++) {
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

Restaurant& Restaurant::operator+=(Table& table)
{
	tables_.push_back(new Table(table));
	return *this;
}


void Restaurant::lireTable(const string& fichier) {
	ifstream file(fichier, ios::in);

	if (file) {
		string ligne;

		string idString;
		int id;

		string nbPersonnesString;
		int nbPersonnes;

		int curseur = 0;
		while (!file.eof()) {
			getline(file, ligne);
			if (ligne == "-TABLES") {
				while (!file.eof()) {
					getline(file, ligne);
					for (unsigned i = 0; i < ligne.size(); i++) {
						if (ligne[i] == ' ') {
							curseur = i;
							break;
						}
						idString += ligne[i];
					}

					id = stoi(idString);

					nbPersonnesString = ligne.substr(curseur + 1);
					nbPersonnes = stoi(nbPersonnesString);

					Table newTable(id, nbPersonnes);
					*this += newTable;
					nbPersonnesString = "";
					idString = "";
				}
			}
		}
		file.close();
	}
}

void Restaurant::placerClients(int nbClients) {
	int indexTable = -1;
	int minimum = 100;


	for (unsigned i = 0; i < tables_.size(); i++) {
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

Restaurant & Restaurant::operator=(const Restaurant& restaurantCopie)
{
	if (this != &restaurantCopie) {


		nom_ = new string(*restaurantCopie.nom_);
		chiffreAffaire_ = restaurantCopie.chiffreAffaire_;
		momentJournee_ = restaurantCopie.momentJournee_;

		delete menuMatin_;
		delete menuMidi_;
		delete menuSoir_;
		menuMatin_ = new Menu(*restaurantCopie.menuMatin_);
		menuMidi_ = new Menu(*restaurantCopie.menuMidi_);
		menuSoir_ = new Menu(*restaurantCopie.menuSoir_);
			
		tables_.clear();

		for (unsigned i = 0; i < restaurantCopie.tables_.size(); i++)
		{
			tables_.push_back(new Table(*restaurantCopie.tables_[i]));
		}
		return *this;
	}

}

ostream & operator<<(ostream & o, Restaurant const& ceRestaurant)
{
	o << "Le restaurant " << *ceRestaurant.nom_;
	if (ceRestaurant.chiffreAffaire_ != 0)
		o << " a fait un chiffre d'affaire de : " << ceRestaurant.chiffreAffaire_ << "$" << endl;
	else
		o << " n'a pas fait de benefice ou le chiffre n'est pas encore calcule." << endl;
	o << "-Voici les tables : " << endl;
	for (unsigned i = 0; i < ceRestaurant.tables_.size(); i++) {
		o << "\t" << *ceRestaurant.tables_[i] << endl;
	}
	o << endl;


	o << "-Voici son menu : " << endl
		<< "Matin : " << endl << *ceRestaurant.menuMatin_
		<< "Midi : " << endl << *ceRestaurant.menuMidi_
		<< "Soir : " << endl << *ceRestaurant.menuSoir_;
	
	return o;
}

bool operator<(Restaurant restaurant, Restaurant restaurantCompare)
{
	if (restaurant.chiffreAffaire_ < restaurantCompare.chiffreAffaire_)
		return true;
	else
		return false;
}
