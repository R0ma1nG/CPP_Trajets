/*************************************************************************
                           ListeTrajets  -  description
                             -------------------
    début                : 23/11/2016
*************************************************************************/

//---------- Interface de la classe <ListeTrajets> (fichier ListeTrajets.h) ----------------
#if ! defined ( ListeTrajets_H )
#define ListeTrajets_H

//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"
//------------------------------------------------------------- Constantes
const int MAX = 20; // Nombre de trajet maximum a l'initialisation de la liste
//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <ListeTrajets>
// Classe principale de la structure de donnees
// Tableau dynamique de Trajets*
// Permet la gestion et l'acces au tableau et a ses elements
//------------------------------------------------------------------------

class ListeTrajets
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
	void Ajouter(Trajet *trajetAAjouter);
	// @param : Pointeur sur un Trajet, l'element à ajouter
	// Ajoute un trajet supplementaire dans le tableau de pointeurs
	// Augmente la taille du tableau si necessaire
	// Contrat : Le pointeur doit etre initialise.
	
	int GetNbAct() const
	{
		return nbAct;
	}
	// Renvoie le nombre de trajets presents dans la liste
	
	Trajet ** GetTrajets() const
	{
		return trajets;
	}
	// Renvoie un pointeur vers le tableau contenant les pointeurs vers les trajets
//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    ListeTrajets ( const ListeTrajets & unListeTrajets );
    // (Constructeur de copie) :
	//  Cree une copie en profondeur des elements dynamiques de l'objet unListeTrajets


    ListeTrajets();
    // (Constructeur) :
	// Cree une liste avec un tableau de pointeurs de Trajet vide

    virtual ~ListeTrajets ( );

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
	void Agrandir();
	// Augmente de 10 le nombre de trajets maximums de la liste
	// La liste gere sa taille maximale de maniere autonome
//----------------------------------------------------- Attributs protégés
	int nbAct; // Nombre de trajets presents dans la liste
	int nbMax; // Nombre de trajets maximum de la liste
	Trajet **trajets; // Tableau de pointeurs sur des Trajets contenant les trajets de cette liste
};

//-------------------------------- Autres définitions dépendantes de <ListeTrajets>

#endif // ListeTrajets_H

