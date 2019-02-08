/*
* Titre : Table.cpp - Travail Pratique #2
* Date : 18 Janvier 2019
* Auteur : Allan BEDDOUK
*/

#include "Table.h"

//constructeurs
Table::Table() {
	capacite_ = MAXCAP;
	vector<Plat*> commande_;
	nbPlats_ = 0;
	id_ = -1;
	nbPlaces_ = 1;
	nbClientsATable_ = 0;
}

Table::Table(int id, int nbPlaces) {
	capacite_ = MAXCAP;
	vector<Plat*> commande_;
	nbPlats_ = 0;
	id_ = id;
	nbPlaces_ = nbPlaces;
	nbClientsATable_ = 0;
}

//destructeur
Table::~Table() {
	//A MODIFIER
	//Probablement supprimer chaque plat de la commande
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
	nbPlats_ = 0;
}

void Table::placerClient(int nbClients) {
	nbClientsATable_ = nbClients;
	nbPlaces_ -= nbClients;
}

//autres methodes
void Table::commander(Plat* plat) {
	// A MODIFIER
	if (nbPlats_ == capacite_) {
		capacite_ *= 2;
		Plat** temp = new Plat*[capacite_];
		for (int i = 0; i < nbPlats_; i++) {
			temp[i] = commande_[i];
		}

		commande_.clear();
		for (int i = 0; i < nbPlats_; i++) {
			commande_.push_back(temp[i]);
		}
		
	}

	commande_[nbPlats_] = plat;
	nbPlats_++;
}

double Table::getChiffreAffaire() const {
	double chiffre = 0;
	for (int i = 0; i < nbPlats_; i++) {
		chiffre += (commande_[i]->getPrix() - commande_[i]->getCout());
	}
	return chiffre;
}

//affichage

ostream & operator<<(ostream& o, Table const& table)
{
	o << "La table numero" << table.id_;
	if (table.estPleine()) {

		o << "est occupée.";
	}
	else {
		o << "est libre.";
	}

	if (table.nbPlats_ != 0) {
		o << "Elle a commande : " << endl;
		for (int i = 0; i < table.nbPlats_; i++) {
			o << table.commande_[i] << endl;
		}
	}
	else {
		o << "Mais les clients n'ont rien commandé pour l'instant.";
	}
	return o;
}
