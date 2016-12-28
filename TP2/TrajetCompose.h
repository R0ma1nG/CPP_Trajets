/*************************************************************************
 TrajetCompose  -  classe objet décrivant un trajet composé
 -------------------
 début                : 16 nov. 2016
 copyright            : (C) 2016 par qjoder
 *************************************************************************/

//---------- Interface de la classe <TrajetCompose> (fichier TrajetCompose.h) ----------------
#if ! defined ( TrajetCompose_H )
#define TrajetCompose_H

//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"
#include "ListeTrajets.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <TrajetCompose>
// Objet héritant de trajet, permettant le stockage et la manipulation
// d'un trajet avec des etapes intermediaires, chaque etape etant elle meme
// un trajet avec ou sans etapes.
//------------------------------------------------------------------------

class TrajetCompose : public Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

	virtual void Afficher()const;
	// Affiche dans l'ordre la ville de départ, la ville d'arrivée et le moyen de transport pour chaque trajet etape de l'itineraire compose
	// à raison de une étape par ligne

	virtual char * GetDepart()const
    // Retourne la ville de depart du trajet compose : l'attribut depart du premier Trajet
	{
		return trajets.GetTrajets()[0]->GetDepart();
	}


	virtual char * GetArrivee()const
	// Retourne la ville d'arrivee du trajet compose : l'attribut arrivee du dernier Trajet
	{
		return trajets.GetTrajets()[trajets.GetNbAct()-1]->GetArrivee();
	}


	virtual Trajet * Copie()const;
	// Retourne un pointeur sur une copie en profondeur de l'objet actuel

	virtual void AjouterTrajet(Trajet * unTrajet);
	// Ajoute au trajet composé le trajet passé en paramètre en tant qu'étape. Cette méthode n'est appelée que si la condition de continuité est
	// préalabement vérifiée (la ville de départ du trajet passé en paramètre doit être identique à la ville d'arrivée du trajet précédent).
	
	virtual string Encoder()const;
	
	virtual bool getTypeTrajet()const{
		return false;
	}

//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur
	TrajetCompose(const ListeTrajets & liste);
	//Construit un Trajet Composé en copiant un objet ListeTrajets.


    TrajetCompose();
	// Créé un trajet composé vide, ne contenant aucune etapes

    virtual ~TrajetCompose();
	// Libère la mémoire allouée pour les pointeurs

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
	ListeTrajets trajets; // Tableau contenant des pointeurs sur des Trajets (simples ou composés)
};

//-------------------------------- Autres définitions dépendantes de <TrajetCompose>

#endif // TrajetCompose_H

