/*
* Titre : Plat.cpp - Travail Pratique #2
* Date : 18 Janvier 2019
* Auteur : Allan BEDDOUK
*/

#include "Plat.h"

//constructeurs
Plat::Plat() {
	nom_ = "Inconnu";
	prix_ = 0;
	cout_ = 0;
}

Plat::Plat(string nom, double prix, double leCout) {
	nom_ = nom;
	prix_ = prix;
	cout_ = leCout;
}
//getters

string Plat::getNom() const {
	return nom_;
}

double Plat::getPrix() const {
	return prix_;
}

double Plat::getCout() const {
	return cout_;
}
//setters
void Plat::setNom(string nom) {
	nom_ = nom;
}

void Plat::setPrix(double prix) {
	prix_ = prix;
}


//methodes en plus

ostream & operator<<(ostream& o, const Plat& cePlat) {
	return o << "\t" << cePlat.getNom() << " - " << cePlat.getPrix() << " $ (" << cePlat.getCout() << "$ pour le restaurant)";
}

bool operator<(Plat const& unPlat, Plat const& unAutrePlat)
{
	if (unPlat.getPrix() < unAutrePlat.getPrix()) {
		return true;
	}
	else {
		return false;
	}
}

