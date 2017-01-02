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

void Catalogue::Sauvegarder(string fichier)
{
	//Sauvegarder(fichier, trajetsCatalogue);
	bool erase = VerifierExistenceFichier(fichier);
	ofstream os;
	os.open(fichier.c_str(), (erase?ios::out : ios::out|ios::app));
	if(os)
	{
		for(int i = 0 ; i < trajetsCatalogue.GetNbAct() ; i++)
		{
			#ifdef MAP
				cout << "Ajout d'un trajet a la sauvegarde"<< endl;
			#endif
			EcrireTrajet(os, *trajetsCatalogue.GetTrajets()[i]);
		}
		os.close();
	}
	else
	{
		cerr << "Erreur sur le flux de sortie" << endl;
	}
}

void Catalogue::Sauvegarder(string fichier, bool typeTrajet)
// true : trajet simple
// false : trajet compose
{
	bool erase = VerifierExistenceFichier(fichier);
	ofstream os;
	os.open(fichier.c_str(), (erase?ios::out : ios::out|ios::app));
	if(os)
	{
		for(int i = 0 ; i < trajetsCatalogue.GetNbAct() ; i++)
		{
			if(typeTrajet == trajetsCatalogue.GetTrajets()[i]->GetTypeTrajet())
			{
				#ifdef MAP
					cout << "Ajout d'un trajet a la sauvegarde"<< endl;
				#endif
				EcrireTrajet(os, *trajetsCatalogue.GetTrajets()[i]);
			}
		}
		os.close();
	}
	else
	{
		cerr << "Erreur sur le flux de sortie" << endl;
	}
}

void Catalogue::Sauvegarder(string fichier, string ville, bool typeVille)
// true : depart
// false : arrivee
{
	bool erase = VerifierExistenceFichier(fichier);
	ofstream os;
	os.open(fichier.c_str(), (erase?ios::out : ios::out|ios::app));
	if(os)
	{
		for(int i = 0 ; i < trajetsCatalogue.GetNbAct() ; i++)
		{
			if((typeVille && ville.compare(trajetsCatalogue.GetTrajets()[i]->GetDepart())==0)||
			   (!typeVille && ville.compare(trajetsCatalogue.GetTrajets()[i]->GetArrivee())==0))
			{
				#ifdef MAP
					cout << "Ajout d'un trajet a la sauvegarde"<< endl;
				#endif
				EcrireTrajet(os, *trajetsCatalogue.GetTrajets()[i]);
			}
		}
		os.close();
	}
	else
	{
		cerr << "Erreur sur le flux de sortie" << endl;
	}
}

void Catalogue::Sauvegarder(string fichier, string depart, string arrivee)
{
	bool erase = VerifierExistenceFichier(fichier);
	ofstream os;
	os.open(fichier.c_str(), (erase?ios::out : ios::out|ios::app));
	if(os)
	{
		for(int i = 0 ; i < trajetsCatalogue.GetNbAct() ; i++)
		{
			if(depart.compare(trajetsCatalogue.GetTrajets()[i]->GetDepart())==0 && arrivee.compare(trajetsCatalogue.GetTrajets()[i]->GetArrivee())==0)
			{
#ifdef MAP
				cout << "Ajout d'un trajet a la sauvegarde"<< endl;
#endif
				EcrireTrajet(os, *trajetsCatalogue.GetTrajets()[i]);
			}
		}
		os.close();
	}
	else
	{
		cerr << "Erreur sur le flux de sortie" << endl;
	}
}

void Catalogue::Sauvegarder(string fichier, int borneInf, int borneMax)
{
	// Verifications sur les bornes
	(borneInf < 0 ? borneInf = 0 : true);
	(borneMax > trajetsCatalogue.GetNbAct() ? borneMax = trajetsCatalogue.GetNbAct() : true);
	if(borneInf > borneMax)
	{
		cerr << "Erreur : les bornes min et max sont incorrectes" << endl;
		cerr << "Retour au menu..." << endl;
		return;
	}
	// Verification sur le nom du fichier
	bool erase = VerifierExistenceFichier(fichier);
	// Debut de la sauvegarde
	ofstream os;
	os.open(fichier.c_str(), (erase?ios::out : ios::out|ios::app));
	if(os)
	{
		for(int i = borneInf ; i < borneMax ; i++)
		{
#ifdef MAP
			cout << "Ajout d'un trajet a la sauvegarde"<< endl;
#endif
			EcrireTrajet(os, *trajetsCatalogue.GetTrajets()[i]);
		}
		os.close();
	}
	else
	{
		cerr << "Erreur sur le flux de sortie" << endl;
	}
}

void Catalogue::Charger(string fichier)
{
	ifstream is;
	is.open(fichier.c_str(), ios::in);
	if(is)
	{
		string typeTrajet;
		while(is >> typeTrajet)
		{
			if(typeTrajet.compare("#S")==0)
			{
				is.seekg(-2, ios::cur); // On se repositionne au debut de la ligne, on respecte ainsi le contrat de la méthode LireTrajetSimple
				TrajetSimple ts(LireTrajetSimple(is));
				Ajouter(ts.Copie());
				#ifdef MAP
					cout << "---- Fin de lecture et ajout d'un TrajetSimple ----" << endl;
				#endif
			}
			else if(typeTrajet.compare("#C")==0)
			{
				is.seekg(-2, ios::cur);
				TrajetCompose tc(LireTrajetCompose(is));
				Ajouter(tc.Copie());
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

void Catalogue::Charger(string fichier, bool type)
{
	ifstream is;
	is.open(fichier.c_str(), ios::in);
	if(is)
	{
		string typeTrajet;
		while(is >> typeTrajet)
		{
			if(typeTrajet.compare("#S")==0)
			{
				is.seekg(-2, ios::cur); // On se repositionne au debut de la ligne, on respecte ainsi le contrat de la methode LireTrajetSimple
				TrajetSimple ts(LireTrajetSimple(is));
				if(type == true)
				{
					Ajouter(ts.Copie());
					#ifdef MAP
						cout << "---- Fin de lecture et ajout d'un TrajetSimple ----" << endl;
					#endif
				}
			}
			else if(typeTrajet.compare("#C")==0)
			{
				is.seekg(-2, ios::cur); // On se repositionne au debut de la ligne
				TrajetCompose tc(LireTrajetCompose(is));
				if (type == false)
				{
					Ajouter(tc.Copie());
					#ifdef MAP
						cout << "---- Fin de lecture et ajout d'un TrajetCompose ----" << endl;
					#endif
				}
			}
			else
			{
				cerr << "Erreur de symbole" << endl;
			}
		}
		is.close(); // fermeture du flux d'entree
	}
	else
	{
		cerr << "Erreur d'ouverture du fichier " << fichier << endl;
	}
}

void Catalogue::Charger(string fichier, string ville, bool typeVille)
{
	ifstream is;
	is.open(fichier.c_str(), ios::in);
	if(is)
	{
		string typeTrajet;
		while(is >> typeTrajet)
		{
			if(typeTrajet.compare("#S")==0)
			{
				is.seekg(-2, ios::cur); // On se repositionne au debut de la ligne, on respecte ainsi le contrat de la methode LireTrajetSimple
				TrajetSimple ts(LireTrajetSimple(is));
				if((typeVille == true && ((string)(ts.GetDepart())).compare(ville)==0) || (typeVille == false && ((string)ts.GetArrivee()).compare(ville)==0))
				{
					Ajouter(ts.Copie());
#ifdef MAP
					cout << "---- Fin de lecture et ajout d'un TrajetSimple ----" << endl;
#endif
				}
			}
			else if(typeTrajet.compare("#C")==0)
			{
				is.seekg(-2, ios::cur);
				TrajetCompose tc(LireTrajetCompose(is));
				if((typeVille == true && ((string)tc.GetDepart()).compare(ville)==0) || (typeVille == false && ((string)tc.GetArrivee()).compare(ville)==0))
				{
					Ajouter(tc.Copie());
#ifdef MAP
					cout << "---- Fin de lecture et ajout d'un TrajetCompose ----" << endl;
#endif
				}
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

void Catalogue::Charger(string fichier, string depart, string arrivee)
{
	ifstream is;
	is.open(fichier.c_str(), ios::in);
	if(is)
	{
		string typeTrajet;
		while(is >> typeTrajet)
		{
			if(typeTrajet.compare("#S")==0)
			{
				is.seekg(-2, ios::cur); // On se repositionne au debut de la ligne, on respecte ainsi le contrat de la methode LireTrajetSimple
				TrajetSimple ts(LireTrajetSimple(is));
				if(((string)ts.GetDepart()).compare(depart)== 0 && ((string)ts.GetArrivee()).compare(arrivee)==0)
				{
					Ajouter(ts.Copie());
#ifdef MAP
					cout << "---- Fin de lecture et ajout d'un TrajetSimple ----" << endl;
#endif
				}
			}
			else if(typeTrajet.compare("#C")==0)
			{
				is.seekg(-2, ios::cur);
				TrajetCompose tc(LireTrajetCompose(is));
				if(((string)tc.GetDepart()).compare(depart)== 0 && ((string)tc.GetArrivee()).compare(arrivee)==0)
				{
					Ajouter(tc.Copie());
#ifdef MAP
					cout << "---- Fin de lecture et ajout d'un TrajetCompose ----" << endl;
#endif
				}
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

void Catalogue::Charger(string fichier, int borneInf, int borneSup)
{
	ifstream is;
	is.open(fichier.c_str(), ios::in);
	int compteur =0;
	if(is)
	{
		string typeTrajet;
		while(is >> typeTrajet)
		{
			if(typeTrajet.compare("#S")==0)
			{
				is.seekg(-2, ios::cur); // On se repositionne au debut de la ligne, on respecte ainsi le contrat de la méthode LireTrajetSimple
				TrajetSimple ts(LireTrajetSimple(is));
				if (compteur >= borneInf && compteur <= borneSup)
				{
					Ajouter(ts.Copie());
					#ifdef MAP
					cout << "---- Fin de lecture et ajout d'un TrajetSimple ----" << endl;
					#endif
				}
				compteur ++;
			}
			else if(typeTrajet.compare("#C")==0)
			{
				is.seekg(-2, ios::cur);
				TrajetCompose tc(LireTrajetCompose(is));
				if (compteur >= borneInf && compteur <= borneSup)
				{
					Ajouter(tc.Copie());
					#ifdef MAP
					cout << "---- Fin de lecture et ajout d'un TrajetCompose ----" << endl;
					#endif
				}
				compteur ++;
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
bool Catalogue::VerifierExistenceFichier(string &fichier)
// Ajoute l'extension .txt si le nom de fichier n'a pas d'extension
// Puis verifie si le fichier existe et propose un renommage ou l'ecrasement si il existe.
// Tant que le nom de fichier n'est pas correct, la méthode est recursive et ne permet pas de continuer la sauvegarde.
{
	// VERIFICATION DE L'EXTENSION DU FICHIER
	string extensionFichier = fichier.substr(fichier.size()-4, fichier.size());
	if(extensionFichier.compare(".txt")!=0)
	{
		fichier.append(".txt");
	}
	
	// Verifier si le fichier existe
	ifstream is (fichier.c_str()); // on ouvre le fichier en lecture
	if (!is.fail())
	{
		int choix;
		cout << "Un fichier avec ce nom existe deja. Que souhaitez vous faire ?" << endl << "1 : Ecraser" << endl << "2 : Ajouter" << endl << "3 : Choisir un nouveau nom" << endl << "Autre : Retour au menu principal" << endl;
		cin >> choix;
		if (choix == 1)
		{
			return true;
		}
		else if (choix == 2)
		{
			/*Charger(fichier); // Attention a l'ordre !!!
			 Sauvegarder(fichier);*/
			// Pour mettre a jour le fichier, il faut utiliser ios::app dans la definition du flux :
			// On va se placer a la fin du fichier afin de le modifier
			return false;
		}
		else if (choix == 3)
		{
			string newName;
			cout << "Veuillez choisir un nouveau nom " << endl;
			cin >> newName;
			VerifierExistenceFichier(newName);
		}
	}
	return true;
} // Fin de VerifierExistenceFichier(string &fichier)

void Catalogue::EcrireTrajet(ofstream &os, Trajet &trajet)
// Inscrit dans le flux ofstream un trajet (passé en parametre) formaté.
{
	if(os)
	{
#ifdef MAP
		cout << "En cours d'ecriture" << endl;
#endif
		string nextLine = trajet.Encoder();
		os << nextLine;
	}
	else
	{
		cerr << "Erreur sur le flux de sortie" << endl;
	}
} // Fin de EcrireTrajet(ofstream &os, Trajet &trajet)


TrajetSimple Catalogue::LireTrajetSimple(ifstream &is)
// Utilise le flux ifstream afin de lire puis de créer un objet TrajetSimple, puis le retourne
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
} // Fin de LireTrajetSimple(ifstream &is)

TrajetCompose Catalogue::LireTrajetCompose(ifstream & is)
// Utilise le flux ifstream afin de lire puis de créer un objet TrajetCompose, puis le retourne
{
	is.seekg(4, ios::cur); // On se positionne au début de la ligne suivant le #C\r\n
	TrajetCompose tc;
	string typeTrajet;
	while (is >> typeTrajet && typeTrajet.compare(";")!=0) // ; marque la fin du trajet compose
	{
		if(typeTrajet.compare("#S")==0)
		{
			is.seekg(-2, ios::cur); // On se repositionne au debut de la ligne, on respecte ainsi le contrat de la méthode LireTrajetSimple
			TrajetSimple ts(LireTrajetSimple(is));
			tc.AjouterTrajet(ts.Copie());
		}
		else if(typeTrajet.compare("#C")==0)
		{
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
} // Fin de LireTrajetCompose(ifstream & is)
//------------------------------------------------------- Méthodes privées

