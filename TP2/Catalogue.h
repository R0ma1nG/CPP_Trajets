/*************************************************************************
                           Catalogue  -  description
                             -------------------
    début                : 23 nov. 2016
*************************************************************************/

//---------- Interface de la classe <Catalogue> (fichier Catalogue.h) ------
#if ! defined ( CATALOGUE_H_ )
#define CATALOGUE_H_

//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"
#include "ListeTrajets.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Catalogue>
// Gere une collection de trajets : ajout, recherche, affichage
//------------------------------------------------------------------------

class Catalogue
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
	void Afficher()const;
	// Affiche tous les trajets présents dans le catalogue : depart, arrivee, moyen de transport

	void Rechercher(const char * depart, const char * arrivee)const;
	// Recherche et	affiche tous les trajets partant de 'depart' et arrivant à 'arrivee'

	bool Ajouter(Trajet * unTrajet);
	// Ajoute un nouveau trajet au catalogue en respectant un tri par ordre alphabétique
	// Renvoie True si l'ajout a été effectué
	// Renvoie False si une erreur a été détectée

	void RechercheSimple(char* depart, char* arrivee) const;
	// Fonction obsolete
	// Affiche tous les trajets simples ou composes allant d'une ville de depart a une ville d'arrivee sans composition de trajets ente eux

	void RechercheComplexe(char * depart, char * arrivee) const;
	// Affiche tous les itinéraires possibles avec le catalogue actuel pour aller de depart a arrivee

	bool villeVisitee(const char * ville, char **tableau) const;
	// Indique si durant notre itinéraire, on est deja passe par la ville ou non
	// Retourne TRUE si depart est present dans le tableau
	// Retourne FALSE sinon
	
	void Tri(string fichier);
	
	void Tri(string fichier, bool typeTrajet);

	void Tri(string fichier, string ville, bool typeVille);
	
	void Tri(string fichier, string depart, string arrivee);
	
	void Tri(string fichier, int borneinf, int borneMax);
	
	
	void Charger(Catalogue &catalogue, string fichier);
	// Ajoute au 'catalogue' les trajets contenus dans le 'fichier'
	// Contrat : le fichier est bien formé : il respecte les règles fixées par les methodes de sauvegarde
	
	void Charger(Catalogue &catalogue, string fichier, bool typeTrajet);
	// Contrat : le fichier est bien formé : il respecte les règles fixées par les methodes de sauvegarde
	
	void Charger(Catalogue &catalogue, string fichier, string ville, bool typeVille);
	// Contrat : le fichier est bien formé : il respecte les règles fixées par les methodes de sauvegarde
	
	void Charger(Catalogue &catalogue, string fichier, string depart, string arrivee);
	// Contrat : le fichier est bien formé : il respecte les règles fixées par les methodes de sauvegarde
	
	void Charger(Catalogue &catalogue, string fichier, int borneInf, int borneSup);
	// Contrat : le fichier est bien formé : il respecte les règles fixées par les methodes de sauvegarde
	
//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur
    Catalogue ( const Catalogue & unCatalogue );
    // Construit une copie de unCatalogue, qui est un catalogue avec ou sans trajet

    Catalogue ( );
    // Construit un catalogue sans aucun trajet

    virtual ~Catalogue ( );
	// Libère la mémoire allouée pour les pointeurs

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
	void EcrireFichier(string nom, ListeTrajets &liste);
	void Sauvegarder(string fichier, ListeTrajets &liste);
	
	TrajetSimple LireTrajetSimple(ifstream &is);
	//Contrat : le curseur du ifstream est positionné au debut de la ligne contenant le trajet simple
	
	TrajetCompose LireTrajetCompose(ifstream &is);
	//Contrat : le curseur du ifstream est positionné au début de la ligne contenant le trajet compose
private:
//------------------------------------------------------- Méthodes privées

protected:
//----------------------------------------------------- Attributs protégés
	ListeTrajets trajetsCatalogue;

private:
//------------------------------------------------------- Attributs privés

//---------------------------------------------------------- Classes amies

//-------------------------------------------------------- Classes privées

//----------------------------------------------------------- Types privés

};

//----------------------------------------- Types dépendants de <Catalogue>

#endif // CATALOGUE_H_

