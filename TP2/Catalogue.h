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

	void RechercheSimple(char * depart, char * arrivee) const;
	// Fonction obsolete
	// Affiche tous les trajets simples ou composes allant d'une ville de depart a une ville d'arrivee sans composition de trajets ente eux

	void RechercheComplexe(const char * depart, const char * arrivee) const;
	// Affiche tous les itinéraires possibles avec le catalogue actuel pour aller de depart a arrivee

	bool villeVisitee(const char * ville, char **tableau) const;
	// Indique si durant notre itinéraire, on est deja passe par la ville ou non
	// Retourne TRUE si depart est present dans le tableau
	// Retourne FALSE sinon
	
	void Sauvegarder(string fichier);
	// Ecrit dans 'fichier' tous les trajets du catalogue
	
	void Sauvegarder(string fichier, bool typeTrajet);
	// Ecrit dans 'fichier' les trajets suivants :
	// typeTrajet = true : uniquement les trajets simples
	// typeTrajet = false: uniquement les trajets composes
	
	void Sauvegarder(string fichier, string ville, bool typeVille);
	// Ecrit dans 'fichier' les trajets suivants :
	// Au depart de 'ville' si typeVille = true
	// Arrivant a 'ville' si typeVille = false
	
	void Sauvegarder(string fichier, string depart, string arrivee);
	// Ecrit dans 'fichier' les trajets au depart de 'depart' et arrivant a 'arrivee'
	
	void Sauvegarder(string fichier, int borneinf, int borneMax);
	// Ecrit dans 'fichier' les trajets du catalogue compris entre le borneInf-ieme et le borneSup-ieme
	
	void Charger(string fichier);
	// Ajoute au catalogue les trajets contenus dans le 'fichier'
	// Contrat : le fichier est bien formé : il respecte les règles fixées par les methodes de sauvegarde
	
	void Charger(string fichier, bool type);
	// Ajoute les trajets contenus dans le fichier  dans le catalogue :
	// type = true --> Trajets Simple
	// type = false--> Trajets Compose
	// Contrat : le fichier est bien formé : il respecte les règles fixées par les methodes de sauvegarde
	
	void Charger(string fichier, string ville, bool typeVille);
	// Ajoute les trajets contenus dans le fichier dans le catalogue :
	// typeVille = true  --> ville est le point de depart
	// typeVille = false --> ville est le point d'arrivee
	// Contrat : le fichier est bien formé : il respecte les règles fixées par les methodes de sauvegarde
	
	void Charger(string fichier, string depart, string arrivee);
	// Ajoute les trajets contenus dans le fichier au depart de 'depart' et arrivant a 'arrivee' dans le catalogue.
	// Contrat : le fichier est bien formé : il respecte les règles fixées par les methodes de sauvegarde
	
	void Charger(string fichier, int borneInf, int borneSup);
	// Ajoute les trajets contenus dans le fichier a partir du 'borneInf'ieme jusqu'au 'borneSup'ieme dans le catalogue.
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
	bool VerifierExistenceFichier(string &fichier);
	// Ajoute l'extension .txt au nom de fichier si elle n'est pas presente
	// Verifie si le fichier ayant comme nom le parametre existe
	// - Si il existe, l'utilisateur peut l'effacer ou le mettre a jour
	// - Si il n'existe pas tout est ok
	
	void EcrireTrajet(ofstream &os, Trajet &trajet);
	// Ecrit dans le fichier (la ou est positionne le curseur du ofstream) le trajet 'trajet' formaté
	// Contrat : le flux de sortie est défini et ouvert sur le fichier que l'on doit modifier
	
	TrajetSimple LireTrajetSimple(ifstream &is);
	//Contrat : le curseur du ifstream est positionné au debut de la ligne contenant le trajet simple
	// Le fluc d'entree est correctement initialisé et ouvert
	
	TrajetCompose LireTrajetCompose(ifstream &is);
	//Contrat : le curseur du ifstream est positionné au début de la ligne contenant le trajet compose
	// Le fluc d'entree est correctement initialisé et ouvert
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

