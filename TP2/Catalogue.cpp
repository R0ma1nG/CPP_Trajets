/*************************************************************************
                           Catalogue  -  description
                             -------------------
    début                : 23 nov. 2016
    copyright            : (C) 2016 par qjoder
*************************************************************************/

//---------- Réalisation de la classe <Catalogue> (fichier Catalogue.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>
#include <fstream>
#include "TrajetSimple.h"
#include "TrajetCompose.h"

//------------------------------------------------------ Include personnel
#include "Catalogue.h"
//------------------------------------------------------------- Constantes
#define MAP true
//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types privés

//----------------------------------------------------------------- PUBLIC

//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- Méthodes publiques
void Catalogue::Afficher()const
// Parcours de notre collection de trajets, et appel de la fonction <Afficher> pour chacun d'eux
{
	int nbAct=trajetsCatalogue.GetNbAct();
	if(nbAct == 0)
	{
		cout << "Il n'existe aucun trajet dans le catalogue" << endl;
	}
	else
	{
		for(int i = 0 ; i < nbAct ; i++)
		{
			cout<<"Trajet n°"<<(i+1)<<" : "<<endl;
			trajetsCatalogue.GetTrajets()[i]->Afficher();
		}
	}
}

bool Catalogue::Ajouter(Trajet * unTrajet)
// Appel de la fonction Ajouter de la classe 'ListeTrajets'
{
	trajetsCatalogue.Ajouter(unTrajet);
	return true;
}

void Catalogue::RechercheSimple(char* depart, char* arrivee) const
// Parcours du catalogue de Trajet. Si les villes de départ et d'arrivée du Trajet (simple ou composé) correspondent aux villes de départ et d'arrivée
// recherchées, alors on affiche ce trajet
{
	int compteur =0;
	Trajet ** trajets = trajetsCatalogue.GetTrajets();
	int nbAct = trajetsCatalogue.GetNbAct();

	for(int i = 0 ; i<nbAct ; i++)
	{
		if(strcmp(trajets[i]->GetDepart(), depart)==0 && strcmp(trajets[i]->GetArrivee(), arrivee)==0)
		{
			trajets[i]->Afficher();
			compteur++;
		}

	}
	if ( compteur > 0)
	{
		cout << compteur <<" trajet"<<(compteur > 1 ? "s ":" ")<<"correspond"<<(compteur > 1 ? "ent ":" ")<<"à votre recherche" << endl;
	}
	else {
		cout <<"Aucun trajet partant de " << depart <<" et arrivant à " << arrivee <<" n'existe :(" << endl;
	}
} // Fin de RechercheSimple

void Catalogue::RechercheComplexe(char * depart, char * arrivee) const
//Parcours du catalogue, plusieurs tests permettent de sélectionner les trajets qui peuvent êter intéressants
// Complexité de l'agorithme : 0(n)
{
	if(trajetsCatalogue.GetNbAct() != 0){
		char * departAct = depart;  // on cherche les trajets partant de departAct. Initialisée à depart
		Trajet ** trajets = trajetsCatalogue.GetTrajets();  // Catalogue des trajets existants
		ListeTrajets parcours;  // Liste des trajets modélisant le parcours actuel
		char * villesParcourue[trajetsCatalogue.GetNbAct()*2]; // Tableau contenant les noms des villes précédemment parcourues.
		//Tableau de taille 2* le nombre de trajets existants (car (nombre de villes différentes) <= (2* nombre de trajets existants))
		villesParcourue[0] = departAct; // On initialise le tableau avec notre ville de départ
		int nbVillesParcourues=0;   // Nombre de villes visitées dans le parcours actuel
		int i = 0;  // indice du trajet actuellement testé
		int indiceIteration[trajetsCatalogue.GetNbAct()*2]; // Tableau stockant les indices où on en était restés lors des étapes précédentes
		do
		{
			if(strcmp(trajets[i]->GetDepart(), departAct)==0) // Si la ville de départ du trajet testé correspond à la ville de départ souhaitée :
			{
				if(strcmp(trajets[i]->GetArrivee(), arrivee)==0)// Si la ville d'arrivée du trajet testé	correspond à la ville d'arrivée souhaitée :
				{
					cout << "J'ai trouve un trajet !!" << endl;
					for(int j = 0 ; j<nbVillesParcourues;j++) // On parcourt notre tableau 'villesParcourue' en affichant chacun des trajets le composant
					{
						parcours.GetTrajets()[j]->Afficher();
					}
					trajets[i]->Afficher(); // On affiche le trajet testé actuellement pour compléter l'affichage
					i++; // On teste l'élément suivant
				}
				else
				{
					if(villeVisitee(trajets[i]->GetArrivee(), villesParcourue)) // Si la ville d'arrivée du trajet testé a déjà été visitée :
					{
						i++; // On passe à l'élément suivant
						cout << "Ville déjà visitée" << endl;
					}
					else // Sinon : la ville de départ correspond mais la ville d'arrivée n'est pas celle cherchée et n'a jamais été visitée :
					{   // On ajoute le trajet testé au parcours, on stocke la valeur de i, on augmente le nombre de villes parcourues
				    //et on ajoute l'arrivée du trajet testé aux villes parcourues, on met à jour 'departAct' et on recommence le parcours du catalogue avec i=0
						parcours.GetTrajets()[nbVillesParcourues] = trajets[i];
						indiceIteration[nbVillesParcourues] = i;
						nbVillesParcourues++;
						villesParcourue[nbVillesParcourues] = trajets[i]->GetArrivee();
						strcpy(departAct, trajets[i]->GetArrivee());
						i=0;
					}
				}
			}
			else // Sinon : la ville de départ ne correspond pas à celle recherchée : on passe au trajet suivant
			{
				i++;
			}

			if(nbVillesParcourues != 0 && i>=trajetsCatalogue.GetNbAct()){ // si on arrive à la fin du catalogue, on regarde si on ne peut pas reprendre à une étape précédente
				villesParcourue[nbVillesParcourues] = 0; // Si on peut, on enlève la dernière ville parcourue, on diminue en conséquence le nombre de villes Parcourues
				nbVillesParcourues--;
				i=indiceIteration[nbVillesParcourues]; // On recommence à l'indice i où on s'était arretés
				strcpy(departAct, parcours.GetTrajets()[nbVillesParcourues]->GetDepart());  // On reprend la valeur de 'departAct' qu'on cherchait
				i++; // et on passe à l'élément suivant
			}
		}while(i<trajetsCatalogue.GetNbAct()); // On sort seulement après avoir testé toutes les possibilités intéressantes
	}
	else
	{
		cout <<"Aucun trajet partant de " << depart <<" et arrivant à " << arrivee <<" n'existe :(" << endl;
	}

} // Fin de RechercheComplexe


bool Catalogue::villeVisitee(const char * ville, char **tableau) const
// Parcours du tableau des villes parcourues. Si au moins une d'entre elle est identique à la ville testee, renvoie true
{
	for (unsigned int i = 0 ; i<strlen(*tableau) ;i++) {
		if(strcmp(tableau[i], ville) == 0)
		{
			return true;
		}
	}
	return false;
}

void Catalogue::Tri(string fichier)
{
	Sauvegarder(fichier, trajetsCatalogue);
}

void Catalogue::Tri(string fichier, bool typeTrajet)
// true : trajet simple
// false : trajet compose
{
	ListeTrajets listeTmp;
	for(int i = 0 ; i < trajetsCatalogue.GetNbAct() ; i++)
	{
		//if(typeTrajet == trajetsCatalogue.GetTrajets()[i]->getTypeTrajet())
		if(typeTrajet && dynamic_cast<TrajetSimple *>(trajetsCatalogue.GetTrajets()[i]) != nullptr)
		{
			#ifdef MAP
				cout << "Trajet Simple" <<endl;
			#endif
			listeTmp.Ajouter(trajetsCatalogue.GetTrajets()[i]->Copie());
		}
		else if(!typeTrajet && dynamic_cast<TrajetCompose *>(trajetsCatalogue.GetTrajets()[i]) != nullptr)
		{
			#ifdef MAP
				cout << "Trajet Compose" << endl;
			#endif
			listeTmp.Ajouter(trajetsCatalogue.GetTrajets()[i]->Copie());
		}
	}
	Sauvegarder(fichier, listeTmp);
}

void Catalogue::Tri(string fichier,string ville,bool typeVille){
	Trajet** tableau=this->trajetsCatalogue.GetTrajets();
	int nbAct=this->trajetsCatalogue.GetNbAct();
	ListeTrajets resultat;
	if(typeVille){
		//La ville est le depart
		for(int i = 0 ; i < nbAct ; i++)
		{
			if(ville.compare(tableau[i]->GetDepart())==0){
				resultat.Ajouter(tableau[i]);
			}
		}
	}
	else{
		// La ville est l'arrivee
		for(int i = 0 ; i < nbAct ; i++)
		{
			if(ville.compare(tableau[i]->GetArrivee())==0){
				resultat.Ajouter(tableau[i]);
			}
		}
	}
	this->Sauvegarder(fichier,resultat);
}

void Catalogue::Tri(string fichier, string depart, string arrivee)
{
	Trajet** tableau=this->trajetsCatalogue.GetTrajets();
	int nbAct=this->trajetsCatalogue.GetNbAct();
	ListeTrajets resultat;
	for(int i = 0 ; i < nbAct ; i++)
	{
		if((depart.compare(tableau[i]->GetDepart())==0) && (arrivee.compare(tableau[i]->GetArrivee())==0))
		{
			resultat.Ajouter(tableau[i]);
		}
	}
	this->Sauvegarder(fichier,resultat);
	
}

void Catalogue::Tri(string fichier, int borneinf, int borneMax)
{
	Trajet** tableau=this->trajetsCatalogue.GetTrajets();
	int nbAct=this->trajetsCatalogue.GetNbAct();
	ListeTrajets resultat;
	for(int i = borneinf ; i <= borneMax ; i++)
	{
		resultat.Ajouter(tableau[i]);
	}
	this->Sauvegarder(fichier,resultat);
}

void Catalogue::Charger(Catalogue &catalogue, string fichier)
{
	ListeTrajets listeContenuFichier;
	ifstream is;
	is.open(fichier);
	if(is)
	{
		string typeTrajet;
		while(is >> typeTrajet)
		{
			if(typeTrajet.compare("#S")==0)
			{
				is.seekg(-2, ios::cur); // On se repositionne au debut de la ligne, on respecte ainsi le contrat de la méthode LireTrajetSimple
				TrajetSimple ts(LireTrajetSimple(is));
				catalogue.Ajouter(ts.Copie());
				#ifdef MAP
				cout << "---- Fin de lecture et ajout d'un TrajetSimple ----" << endl;
				#endif
			}
			else if(typeTrajet.compare("#C")==0)
			{
				cout << "Trajet Compose" << endl;
				is.seekg(-2, ios::cur);
				TrajetCompose tc(LireTrajetCompose(is));
				catalogue.Ajouter(tc.Copie());
				#ifdef MAP
				cout << "---- Fin de lecture et ajout d'un TrajetCompose ----" << endl;
				#endif
			}
			else
			{
				cerr << "Erreur de symbole" << endl;
 			}
		}
		is.close();
	}
	else
	{
		cerr << "Erreur d'ouverture du fichier " << fichier << endl;
	}
}

//------------------------------------------------- Surcharge d'operateurs

//-------------------------------------------- Constructeurs - destructeur
Catalogue::Catalogue ( )
:trajetsCatalogue()
{
	#ifdef MAP
		cout << "Appel au constructeur de <Catalogue>" << endl;
	#endif
} //----- Fin de Catalogue (constructeur 1)

Catalogue::Catalogue(const Catalogue & unCatalogue )
{
	#ifdef MAP
		cout << "Appel au constructeur de copie de <Catalogue>" << endl;
	#endif

} // Fin de Catalogue (constructeur de copie)

Catalogue::~Catalogue ( )
{
	#ifdef MAP
		cout << "Appel au destructeur de <Catalogue>" << endl;
	#endif
} //----- Fin de ~Catalogue

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Methodes protegees
void Catalogue::Sauvegarder(string fichier, ListeTrajets &liste)
{
	// Verifier si le fichier existe
	ifstream is (fichier.c_str()); // on ouvre le fichier en lecture
	if (!is.fail())
	{
		int choix;
		cout << "Un fichier avec ce nom existe deja�. Que souhaitez vous faire ?" << endl << "1 : Ecraser" << endl << "2 : Ajouter" << endl << "3 : Choisir un nouveau nom" << endl << "Autre : Retour au menu principal" << endl;
		cin >> choix;
		if (choix == 1)
		{
			EcrireFichier(fichier, liste);
			cout << "Le fichier a ete ecrase" << endl;
		}
		else if (choix == 2)
		{
			/*Charger(fichier); // Attention a l'ordre !!!
			 Sauvegarder(fichier);*/
			// Pour mettre a jour le fichier, il faut utiliser ios::app dans la definition du flux :
			// On va se placer a la fin du fichier afin de le modifier
			cout << "Travaux en cours" << endl;
			cout << "Le fichier a ete mis a jour" << endl;
		}
		else if (choix == 3)
		{
			string newName;
			cout << "Veuillez choisir un nouveau nom " << endl;
			cin >> newName;
			Sauvegarder(newName, liste);
		}
	}
	else
	{
		cout << "Fichier inexistant" << endl;
		EcrireFichier(fichier, liste);
		cout << "Le fichier a ete cree" << endl;
	}
	cout << "Fin sauvegarde" << endl;
}


void Catalogue::EcrireFichier(string nomFichier, ListeTrajets &liste) // DETRUIRE LA LISTE DE TRAJETS CREES
{
	ofstream os;
	os.open(nomFichier.c_str());
	
	if(os)
	{
		cout << "En cours d'ecriture" << endl;
		
		int nbAct=liste.GetNbAct();
		for(int i = 0 ; i < nbAct ; i++)
		{
			string nextLine = trajetsCatalogue.GetTrajets()[i]->Encoder();
			os << nextLine;
		}
		os.close();
	}
	else
	{
		cerr << "Erreur d'ouverture" << endl;
	}
}


TrajetSimple Catalogue::LireTrajetSimple(ifstream &is)
{
	is.seekg(5, ios::cur); // Placement du curseur au debut de la ville de depart
	// --------------------Lecture de depart
	string depart;
	char tmp;
	while(is.get(tmp))
	{
		if(tmp == '$')
		{
			break;
		}
		depart += tmp;
	}
	is.seekg(1, ios::cur); // On viens de lire le $, on passe le type de ville (A)
	// --------------------Lecture de arrivee
	string arrivee;
	while(is.get(tmp))
	{
		if(tmp == '$')
		{
			break;
		}
		arrivee += tmp;
	}
	is.seekg(1, ios::cur); // On viens de lire le $, on passe le type (T)
	// --------------------Lecture de transport
	string transport;
	while(is.get(tmp))
	{
		if(tmp == '\r')
		{
			break;
		}
		transport += tmp;
	}
	is.seekg(1, ios::cur); // On se place pres a lire la ligne suivante
	TrajetSimple ts(depart.c_str(), arrivee.c_str(), transport.c_str());
	return ts;
}

TrajetCompose Catalogue::LireTrajetCompose(ifstream & is)
{
	is.seekg(4, ios::cur); // On se positionne au début de la ligne suivant le #C\r\n
	TrajetCompose tc;
	string typeTrajet;
	while (is >> typeTrajet && typeTrajet.compare(";")!=0)
	{
		cout << typeTrajet << endl;
		if(typeTrajet.compare("#S")==0)
		{
			is.seekg(-2, ios::cur); // On se repositionne au debut de la ligne, on respecte ainsi le contrat de la méthode LireTrajetSimple
			TrajetSimple ts(LireTrajetSimple(is));
			tc.AjouterTrajet(ts.Copie());
		}
		else if(typeTrajet.compare("#C")==0)
		{
			cout << "Trajet Compose" << endl;
			is.seekg(-2, ios::cur);
			TrajetCompose tcAjout(LireTrajetCompose(is));
			tc.AjouterTrajet(tcAjout.Copie());
		}
		else
		{
			cerr << "Erreur de symbole" << endl;
		}
	}
	return tc;
}
//------------------------------------------------------- Méthodes privées

