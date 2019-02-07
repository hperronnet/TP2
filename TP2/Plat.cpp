/*
* Titre : Plat.cpp - Travail Pratique #1
* Date : 31/01/2019
* Auteurs : Philippe Maisonneuve - 1959052
*			Hugo Perronnet - 1885263
*/

#include "Plat.h"

using namespace std;

//Constructeur par défaut
Plat::Plat() : nom_("inconnu"), prix_(0.0), cout_(0.0)
{
}

//Constructeur
Plat::Plat(string nom, double prix, double cout) : nom_(nom), prix_(prix), cout_(cout)
{
}

/*
* Recupere le nom du plat
*/
string Plat::getNom() const
{
	return nom_;
}

/*
* recupere le prix du plat
*/
double Plat::getPrix() const
{
	return prix_;
}

/*
* recupere le cout du plat pour le restaurant
*/
double Plat::getCout() const
{
	return cout_;
}

/*
* Définit le nom du plat
* \param nom : le nom du plat
*/
void Plat::setNom(string nom)
{
	nom_ = nom;
}

/*
* Définit le prix du plat
* \param prix : le prix du plat
*/
void Plat::setPrix(double prix)
{
	prix_ = prix;
}

/*
* Affiche le nom, le prix et le cout du plat
*/
void Plat::afficher() const
{
	cout << nom_ << " - " << prix_ << " $ (" << cout_ << "$ pour le restaurant)" << endl;
}
