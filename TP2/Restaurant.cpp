/*
* Titre : Restaurant.cpp - Travail Pratique #1
* Date : 31/01/2019
* Auteurs : Philippe Maisonneuve - 1959052
*			Hugo Perronnet - 1885263
*/


#include "Restaurant.h"

//constructeur par défaut
Restaurant::Restaurant() : chiffreAffaire_(0), momentJournee_(Matin), nbTables_(0), nom_(new string("inconnu"))
{
	tables_ = new Table*[INTTABLES];
}

//constructeur
Restaurant::Restaurant(string & fichier, string & nom, TypeMenu moment) : momentJournee_(moment), chiffreAffaire_(0), nbTables_(0), nom_(new string(nom))
{
	tables_ = new Table*[INTTABLES];
	lireTable(fichier);
	menuMatin_ = new Menu(fichier, Matin);
	menuMidi_ = new Menu(fichier, Midi);
	menuSoir_ = new Menu(fichier, Soir);

}

//Destructeur
Restaurant::~Restaurant() {
	for (int i = 0; i < nbTables_; i++) {
		tables_[i] = nullptr;
	}
	delete[] tables_;
	delete menuMatin_;
	delete menuMidi_;
	delete menuSoir_;

}



/*
* définit le moment de la journée
* \param moment : le moment de la journée
*/
void Restaurant::setMoment(TypeMenu moment)
{
	momentJournee_ = moment;
}

/*
* Récupère le nom du restaurant
* \return le nom du restaurant
*/
string Restaurant::getNom() const
{
	return string(*nom_);
}

/*
* Récupère le moment de la journée
* \return le moment de la journée
*/
TypeMenu Restaurant::getMoment() const
{
	return TypeMenu(momentJournee_);
}

/*
* Ouvre le fichier .txt pour récupérer les tables du restaurant
* \param fichier : le nom du fichier à ouvrir 
*/
void Restaurant::lireTable(string & fichier)
{
	ifstream liste(fichier, ios::in);
	string ligneLu;
	while (!ws(liste).eof())
	{
		getline(liste, ligneLu);
		if ((ligneLu == "-TABLES"))
		{
			while (!ws(liste).eof())
			{
				int IDTables, nbPlace;
				liste >> IDTables >> nbPlace;
				ajouterTable(IDTables, nbPlace);
			}
		}
	}
}

/*
* Ajouter une table à la liste de tables
* \param id : le nomero de table
*		 nbPlaces : le nombre de places sur la table
*/
void Restaurant::ajouterTable(int id, int nbPlaces)
{
	tables_[nbTables_] = new Table(id, nbPlaces);
	nbTables_++;
}

/*
* Libere une table (n'est plus occupée, mise à jour du chiffre d'affaire)
* \param id : le nomero de table
*/
void Restaurant::libererTable(int id)
{
	for (int i = 0; i < nbTables_; i++)
	{
		if (tables_[i]->getId() == id)
		{
			chiffreAffaire_ += tables_[i]->getChiffreAffaire();
			tables_[i]->libererTable();
		}
	}
}

/*
* Ajoute le plat à la liste de commande si celui-ci est dans le menu du moment de la journée
* \param nom : nom du plat
*		 idTable : ID de la table
*/
void Restaurant::commanderPlat(string & nom, int idTable)
{
	for (int i = 0; i < nbTables_; i++)
	{
		if (tables_[i]->getId() == idTable)
		{
			Plat * plat = new Plat;
			switch (momentJournee_)
			{

			case Matin: 
				plat = menuMatin_->trouverPlat(nom);
				break;
			case Midi:
				plat = menuMidi_->trouverPlat(nom);
				break;
			case Soir: 
				plat = menuSoir_->trouverPlat(nom);
				break;
			default:
				break; plat = nullptr;
			}

			if (plat != nullptr)
				tables_[i]->commander(plat);
			plat = nullptr;
			delete plat;
		}
	}



}

/*
* Place les clients sur une talbe (la table devient occupée)
* \param nbClients : le nombre de clients
*/
void Restaurant::placerClients(int nbClients)
{
	bool tableTrouvee = false;
	Table* meilleurTable = new Table(-1, 500);
	for (int i = 0; i < nbTables_; i++) {
		if ((tables_[i]->estOccupee() == 0) && (nbClients <= tables_[i]->getNbPlaces())) {
			tableTrouvee = true;

			if (tables_[i]->getNbPlaces() < meilleurTable->getNbPlaces()) {
				meilleurTable = tables_[i];
			}
		}
	}

	if (!tableTrouvee) {
		cout << "Aucune table n'a ete trouvee pour les clients au nombre de " << nbClients << endl;
	}
	else {
		cout << "Clients aux nombre de" << nbClients <<" place !" << endl;
		meilleurTable->placerClient();
	}
}

/*
* Affiche tout le menu
*/
void Restaurant::afficher() const
{
	cout << "Le nom du restaurant est " << *nom_ << endl << endl << "Voici son menu : " <<endl;
	cout << "MATIN : " << endl;
	menuMatin_->afficher();
	cout << "MIDI : " << endl;
	menuMidi_->afficher();
	cout << "SOIR : " << endl;
	menuSoir_->afficher();
		

	

	cout << "Voici les tables du restaurant" << endl;

	for (int i = 0; i < nbTables_; i++)
	{
		tables_[i]->afficher();
	}

	cout << "Le chiffre d'affaire du restaurant est " << chiffreAffaire_ << endl << endl;
}