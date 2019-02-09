/*
* Titre : Table.cpp - Travail Pratique #2
* Date : 18 Janvier 2019
* Auteur : Allan BEDDOUK
*/

#include "Table.h"

//constructeurs
Table::Table() {
	//vector<Plat*> commande_;
	id_ = -1;
	nbPlaces_ = 1;
	nbClientsATable_ = 0;
}

Table::Table(int id, int nbPlaces) {
	//vector<Plat*> commande_;
	id_ = id;
	nbPlaces_ = nbPlaces;
	nbClientsATable_ = 0;
}

//destructeur
Table::~Table() {
	//A MODIFIER
	//Probablement supprimer chaque plat de la commande
	for (unsigned i = 0; i < commande_.size(); i++)
		commande_[i] = nullptr;
	commande_.clear();
}

//getters
int Table::getId() const {
	return id_;
}

int Table::getNbPlaces() const {
	return nbPlaces_;
}

int Table::getnbClientATable() const
{
	return nbClientsATable_;
}

bool Table::estPleine() const {
	return nbPlaces_==0;
}

bool Table::estOccupee() const
{
	return nbClientsATable_!=0;
}

//setters
void Table::setId(int id) {
	id_ = id;
}

void Table::libererTable() {
	nbPlaces_ += nbClientsATable_;
	nbClientsATable_ = 0;
	//A MODIFIER
	commande_.clear();
}

void Table::placerClient(int nbClients) {
	nbClientsATable_ = nbClients;
	nbPlaces_ -= nbClients;
}

//autres methodes
void Table::commander(Plat* plat) {
	// A MODIFIER
	commande_.push_back(plat);
}

double Table::getChiffreAffaire() const {
	double chiffre = 0;
	for (unsigned i = 0; i < commande_.size(); i++) {
		chiffre += (commande_[i]->getPrix() - commande_[i]->getCout());
	}
	return chiffre;
}

//affichage
ostream & operator<<(ostream& o, Table const& table)
{
	o << "La table numero " << table.id_;
	if (table.estOccupee()) {

		o << " est occupee.";
		if (table.commande_.size() != 0) {
			o << " Elle a commande : " << endl;
			for (int i = 0; i < table.commande_.size(); i++) {
				o << *table.commande_[i] << endl;
			}
		}
		else {
			o << " Mais les clients n'ont rien commande pour l'instant." << endl;
		}
	}
	else {
		o << " est libre.";
	}


	return o;
}
