/*************************************************************************
                           Trajet  -  description
                             -------------------
    début                : 16/11
*************************************************************************/

//---------- Interface de la classe <Trajet> (fichier Trajet.h) ----------------
#if ! defined ( Trajet_H )
#define Trajet_H

//--------------------------------------------------- Interfaces utilisées
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Trajet>
// Classe virtuelle pure, definition des methodes necessaires au fonctionnement
// des classes derivees.
//------------------------------------------------------------------------

class Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
	
	virtual void Afficher()const=0;
	
	virtual char * GetDepart()const=0;
	
	virtual char * GetArrivee()const=0;
	
	virtual Trajet * Copie()const=0;
	
	virtual string Encoder()const=0;
	
	virtual bool GetTypeTrajet()const=0;

//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeurs
	virtual ~Trajet(){}
//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

};

//-------------------------------- Autres définitions dépendantes de <Trajet>

#endif // TRAJET_H

