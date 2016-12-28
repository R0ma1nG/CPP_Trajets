/*************************************************************************
                           ListeTrajets  -  description
                             -------------------
    début                : 27 nov. 2016
    copyright            : (C) 2016 par vbonin
*************************************************************************/

//---------- Réalisation de la classe <ListeTrajets> (fichier ListeTrajets.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "ListeTrajets.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void ListeTrajets::Ajouter(Trajet *trajetAAjouter)
// Si le nombre maximum d'element est atteint, le tableau est agrandi
// Ensuite on ajoute le pointeur vers Trajet au tableau
{
	if(nbMax == nbAct)
	{
		Agrandir();
	}
	trajets[nbAct] = trajetAAjouter;
	nbAct++;
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
ListeTrajets::ListeTrajets ( const ListeTrajets & unListeTrajets )
{
#ifdef MAP
	cout << "Appel au constructeur de copie de <ListeTrajets>" << endl;
#endif
	nbAct = 0;
	nbMax = unListeTrajets.nbMax;
	trajets = new Trajet*[nbMax];
	for(int i =0 ; i<nbMax ; i++)
	{
		Ajouter(unListeTrajets.GetTrajets()[i]->Copie());
	}
} //----- Fin de ListeTrajets (constructeur de copie)


ListeTrajets::ListeTrajets ( )
{
#ifdef MAP
	cout << "Appel au constructeur de <ListeTrajets>" << endl;
#endif
	nbAct = 0;
	nbMax = MAX;
	trajets = new Trajet*[MAX];
} //----- Fin de ListeTrajets


ListeTrajets::~ListeTrajets ( )
{
#ifdef MAP
	cout << "Appel au destructeur de <ListeTrajets>" << endl;
#endif
	for(int i =0 ; i<nbAct ; i++)
	{
		delete trajets[i];
	}
	delete[] trajets;
} //----- Fin de ~ListeTrajets


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
void ListeTrajets::Agrandir()
// Cree un nouveau pointeur vers un tableau de pointeurs de taille maximale +10
// Effectue une copie en profondeur de l'ancien dans le nouveau
// Supprime l'ancien
// Affecte le nouveau
{
	Trajet **nouveau = new Trajet*[nbMax+10];
	for(int i = 0 ; i < nbAct ; i++)
	{
		nouveau[i] = trajets[i];
	}
	nbMax += 10;
	delete []trajets;
	trajets = nouveau;
} // Fin de Agrandir
