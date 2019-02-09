/*
* Titre : Table.h - Travail Pratique #2
* Date : 18 Janvier 2019
* Auteur : Allan BEDDOUK
*/

#ifndef TABLE_H
#define TABLE_H

#include "Plat.h"
#include <vector>

const  int MAXCAP = 5;
class Table {
public:
	///constructeurs
	Table();
	Table(int id, int nbPlaces);

	///destructeur
	~Table();

	///getters
	int getId() const;
	int getNbPlaces() const;
	int getnbClientATable() const;
	bool estPleine() const;
	bool estOccupee() const;

	///setters
	void libererTable(); // A MODIFIER
	void placerClient(int nbClients);
	void setId(int id);

	///autres methodes
	void commander(Plat* plat); // A MODIFIER
	double getChiffreAffaire() const;

	///affichage	
	friend ostream& operator<<(ostream& o, Table const& table);

private:
	//A MODIFIER
	vector<Plat*> commande_;
	int id_;
	int nbPlaces_;
	int nbClientsATable_;
};

#endif // !TABLE_H
