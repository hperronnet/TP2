/*
* Titre : main.cpp - Travail Pratique #1
* Date : 09 Janvier 2019 
* Auteur : David Dratwa
*/

#include "Restaurant.h"
#include <iostream>

using namespace std; 

int main() {

	//creation du restaurant - avec le fichier donne - le nom : PolyFood - moment de la journee : soir. 
	string fichier = "polyFood.txt";
	string nom = "PolyFood";
	Restaurant poly(fichier, nom, Soir);
	//creer plusieurs clients -- des entiers 
	int client1 = 1; 
	int client2 = 5; 
	int client3 = 15; 
	int client4 = 3; 
	int client5 = 2; 

	//placer les clients 
	poly.placerClients(client1);
	poly.placerClients(client2);
	poly.placerClients(client3);
	poly.placerClients(client4);
	poly.placerClients(client5);


	// commander des plats
	string poisson = "Poisson";
	string poulet = "Poulet";
	string pizza = "Pizza";
	string muffin = "Muffin";
	string oeuf = "Oeuf";
	poly.commanderPlat(poisson, 1);
	poly.commanderPlat(poulet, 2);
	poly.commanderPlat(pizza, 2);
	poly.commanderPlat(poulet, 4);
	poly.commanderPlat(muffin, 4);
	poly.commanderPlat(oeuf, 4);
	//Poisson - Table 1 
	//Poulet - Table 2 
	//Pizza - Table 2 
	//Poulet - Table 4
	//Muffin - Table 4 
	//Oeud - Table 4 
	

	//afficher le restaurant
	poly.afficher(); 

	cout << "-------------------------------------------------" << endl; 

	//liberer les tables 
	poly.libererTable(1);
	poly.libererTable(2);
	poly.libererTable(3);
	poly.libererTable(4);
	//afficher le restaurant 
	poly.afficher(); 
	system("pause");
	return 0;

}