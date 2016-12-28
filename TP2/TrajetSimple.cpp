/*************************************************************************
 TrajetCompose  -  classe objet décrivant un trajet composé
 -------------------
 début                : 16 nov. 2016
 copyright            : (C) 2016 par vbonin
 *************************************************************************/


//---------- Réalisation de la classe <TrajetSimple> (fichier TrajetSimple.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>
//------------------------------------------------------ Include personnel

#include "TrajetSimple.h"
//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

Trajet * TrajetSimple::Copie() const
{
	TrajetSimple *t = new TrajetSimple(*this); // Appel du constructeur de copie pour copier l'élément actuel en profondeur
	return t;
}

void TrajetSimple::Afficher() const
{
	#ifdef MAP
		cout <<depart<<" / "<<arrivee<<" : "<<moyenTransport<<endl;
	#else
		cout << "Trajet en "<<GetMdT()<<" partant de "<<GetDepart()<<" à destination de "<<GetArrivee() << endl;
	#endif
}

string TrajetSimple::Encoder() const
{
	string s="#S $D";
	s.append(depart);
	s.append("$A");
	s.append(arrivee);
	s.append("$T");
	s.append(this->moyenTransport);
	s.append("\r\n");
	return s;
}

//-------------------------------------------- Constructeurs - destructeur

TrajetSimple::TrajetSimple (const char * villeDepart, const char * villeArrivee, const char * moyTrans)
// Initialisation des attributs et copie en profondeur des paramètres
{
	#ifdef MAP
		cout << "Appel au constructeur de <TrajetSimple>" << endl;
	#endif
	depart = new char[strlen(villeDepart)+1];
	arrivee = new char[strlen(villeArrivee)+1];
	moyenTransport = new char[strlen(moyTrans)+1];
	strcpy(depart,villeDepart);
	strcpy(arrivee,villeArrivee);
	strcpy(moyenTransport,moyTrans);
} //----- Fin de TrajetSimple

TrajetSimple::TrajetSimple(const TrajetSimple & trajetSimple)
{
	#ifdef MAP
		cout << "Appel au constructeur de copie de <TrajetSimple>" << endl;
	#endif
	depart = new char[strlen(trajetSimple.GetDepart())+1];
	arrivee = new char[strlen(trajetSimple.GetArrivee())+1];
	moyenTransport = new char[strlen(trajetSimple.GetMdT())+1];
	strcpy(depart,trajetSimple.GetDepart());
	strcpy(arrivee,trajetSimple.GetArrivee());
	strcpy(moyenTransport,trajetSimple.GetMdT());
} //----- Fin du constructeur de copie


TrajetSimple::~TrajetSimple ( )
{
	#ifdef MAP
		cout << "Appel au destructeur de <TrajetSimple>" << endl;
	#endif
	delete []depart;
	delete []arrivee;
	delete []moyenTransport;
} //----- Fin de ~TrajetSimple

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

