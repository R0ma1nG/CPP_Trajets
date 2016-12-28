/*************************************************************************
                           TrajetSimple  -  description
                             -------------------
    début                : 23 nov. 2016
*************************************************************************/

//---------- Interface de la classe <TrajetSimple> (fichier TrajetSimple.h) ------
#if ! defined ( TRAJETSIMPLE_H_ )
#define TRAJETSIMPLE_H_

//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"
#include <sstream>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <TrajetSimple>
// Objet héritant de Trajet, permettant le stockage et la manipulation
// d'un trajet sans etapes intermediaires partant d'un endroit à un autre
// en utilisant un moyen de transport.
//------------------------------------------------------------------------

class TrajetSimple : public Trajet
{
//----------------------------------------------------------------- PUBLIC

    public:
//----------------------------------------------------- Méthodes publiques

	virtual void Afficher()const;
	// Affiche dans l'ordre la ville de départ, la ville d'arrivee et le moyen de transport pour ce trajet

	virtual char * GetDepart()const
    // Renvoie la ville de depart du trajet
	{
		return depart;
	}


	virtual char * GetArrivee()const
	// Renvoie la ville d'arrivee du trajet
	{
		return arrivee;
	}


	virtual char *GetMdT()const
	//Renvoie le moyen de transport utilisé pendant le trajet
	{
		return moyenTransport;
	}

	virtual string Encoder()const;
	/*virtual string Encoder()const{
		//string s = "#S $D"+(*depart)+"$A"+(*arrivee)+"$T"+(*moyenTransport)+"\0";
		ostringstream s;
		s << "ABC" << "DEF";
		return s.str();
	}*/

	Trajet * Copie()const;
	// Renvoie un pointeur sur une copie en profondeur de l'objet actuel
	
	virtual bool getTypeTrajet()const{
		return true;
	}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
	TrajetSimple(const TrajetSimple & trajetSimple);
	//Créé un trajet simple qui est la copie de 'trajetSimple'

	TrajetSimple(const char * villeDepart, const char * villeArrivee, const char * moyTrans);
    // Créé un trajet simple partant de villeDepart et allant à villeArrivee avec un moyTrans
    //Initialise les attributs depart, arrivee et moyenTransport

    virtual ~TrajetSimple();
    // Libère la mémoire allouée aux pointeurs depart, arrivee, moyenTransport

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés
    char * depart;
    // Ville de départ de ce trajet
    char * arrivee;
    // Ville d'arrivée de ce trajet
    char * moyenTransport;
    // Moyen de transport pour ce trajet
private:
//------------------------------------------------------- Attributs privés

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <TrajetSimple>

#endif // TRAJETSIMPLE_H_

