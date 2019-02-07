/*
* Titre : Table.cpp - Travail Pratique #1
* Date : 31/01/2019
* Auteurs : Philippe Maisonneuve - 1959052
*			Hugo Perronnet - 1885263
*/
#include "Table.h"
#include <fstream>

//Constructeur par défaut
Table::Table() : capacite_(MAXCAP), id_(-1), nbPlaces_(1), occupee_(false), nbPlats_(0)
{
	commande_ = new Plat*[MAXCAP];
}

//Constructeur
Table::Table(int id, int nbPlaces) : capacite_(MAXCAP), id_(id), nbPlaces_(nbPlaces), occupee_(false), nbPlats_(0)
{
	commande_ = new Plat*[MAXCAP];
}

//Destructeur
Table::~Table() {
	for (int i = 0; i < nbPlats_; i++) {
		commande_[i] = nullptr;
	}
	delete[] commande_;
}

/*
* \return id_ de la table
*/
int Table::getId() const
{
	return id_;
}

/*
* \return nombre de places sur un table
*/
int Table::getNbPlaces() const
{
	return nbPlaces_;
}

/*
* \return si la table est occupée ou non
*/
bool Table::estOccupee() const
{
	return occupee_;
}

/*
* La table n'est plus accupée et la commande associée est vidée
*/
void Table::libererTable()
{
	occupee_ = false;

	for  (int i = 0; i < nbPlaces_; i++)
	{
		commande_[i] = nullptr;
	}
}

/*
* La table devient occupée
*/
void Table::placerClient()
{
	occupee_ = true;
}

/*
* Définit l'id de la table
*/
void Table::setId(int id)
{
	id_ = id;
}

/*
* Ajouter un plat à la commande des clients
* \param plat : Le plat à ajouter à la commande
*/
void Table::commander(Plat * plat)
{
	commande_[nbPlats_] = plat;
	nbPlats_++;
}

/*
* Renvoie le chiffre d'affaire de la table
* \return le chiffre d'affaire
*/
double Table::getChiffreAffaire()
{
	double prix = 0.0;

	for (int i = 0; i < nbPlats_; i++)
	{
		prix += commande_[i]->getPrix();
	}
	return prix;
}

/*
* Affiche l'id de la table. Indique si elle est libre ou occupée. Si elle est occupée, affiche les commandes passées par les clients
*/
void Table::afficher() const
{
	cout << "La table numero " << id_ << " est ";
	if (occupee_) {
		cout << "occupe. Voici les commandes passees par les clients :" << endl;
		for (int i = 0; i < nbPlats_; i++)
		{
			commande_[i]->afficher();
		}
	}
	else
		cout << "libre." << endl;
}
