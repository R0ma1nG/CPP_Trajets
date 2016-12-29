/*************************************************************************
 TrajetCompose  -  classe objet décrivant un trajet composé
 -------------------
 début                : 23 nov. 2016
 copyright            : (C) 2016 par qjoder
 *************************************************************************/

//---------- Réalisation de la classe <TrajetCompose> (fichier TrajetCompose.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
//------------------------------------------------------ Include personnel
#include "TrajetCompose.h"
//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void TrajetCompose::Afficher()const
// Parcourt la liste de trajets et appelle la methode afficher de chacun d'entre eux
{
	cout << "Trajet en plusieurs etapes : " << endl;
	for(int i = 0 ; i<trajets.GetNbAct() ; i++)
	{
		trajets.GetTrajets()[i]->Afficher();
	}
}

Trajet * TrajetCompose::Copie()const
// Copie en profondeur de tous les trajets composant le trajet composé dans nouvelEl
{
	TrajetCompose * nouvelEl  = new TrajetCompose();

	int cardMax = trajets.GetNbAct();
	for(int i = 0 ; i<cardMax ; i++)
	{
		nouvelEl->AjouterTrajet(trajets.GetTrajets()[i]->Copie());
	}
	return nouvelEl;
}

void TrajetCompose::AjouterTrajet(Trajet * unTrajet)
{
	trajets.Ajouter(unTrajet);
}

string TrajetCompose::Encoder()const
{
	string s="#C\r\n";
	int i;
	for(i=0;i<trajets.GetNbAct();i++)
	{
		s.append(trajets.GetTrajets()[i]->Encoder());
	}
	s.append(";\r\n");
	return s;
}
//-------------------------------------------- Constructeurs - destructeur
TrajetCompose::TrajetCompose ( const ListeTrajets & liste )
{
	#ifdef MAP
		cout << "Appel au constructeur de copie de <TrajetCompose>" << endl;
	#endif
	trajets = ListeTrajets(liste);
} //----- Fin de TrajetCompose (constructeur de copie)


TrajetCompose::TrajetCompose()
:trajets()
{
	#ifdef MAP
		cout << "Appel au constructeur de <TrajetCompose>" << endl;
	#endif
} //----- Fin de TrajetCompose


TrajetCompose::~TrajetCompose ( )
{
	#ifdef MAP
		cout << "Appel au destructeur de <TrajetCompose>" << endl;
	#endif

} //----- Fin de ~TrajetCompose


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées


