/*************************************************************************
 Main  -  classe main du TP2 Heritage
 -------------------
 debut                : 16 nov. 2016
 copyright            : (C) 2016 par rgouttefangeas
 *************************************************************************/

//---------- R√©alisation de la classe <Main> (fichier Main.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include syst√®me
#include <iostream>
#include <cstring>
using namespace std;
//------------------------------------------------------ Include personnel
#include "Trajet.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"
#include "Catalogue.h"

//------------------------------------------------------------- Constantes
const int TAILLE = 100;
//---------------------------------------------------- Variables de classe

//----------------------------------------------------------- Types priv√©s


//----------------------------------------------------------------- PUBLIC



int main(int argv, char** argc)
{
	//test();

	Catalogue catalogue;


	while(true)
	{
		cout << "=============================================================" <<endl;
		cout << "1 : Ajouter un trajet simple"<< endl;
		cout << "2 : Ajouter un trajet compose"<< endl;
		cout << "3 : Afficher tous les trajets"<< endl;
		cout << "4 : Recherche complexe d'un itinéraire"<< endl;
		cout << "5 : Sauvegarder" << endl;
		cout << "6 : Charger"<<endl;
		cout << "7 : Quitter" << endl;
		cout << "=============================================================" <<endl;
		int choix=0;

		if (! (cin >> choix))
		{
			cerr << "Erreur de saisie" << endl;
			cin.clear();
			cin.ignore(1);
			continue;
		}


		string depart;
		string arrivee;
		string transport;
		if(choix == 1)
		{
			cout << "Inserez le trajet : "<< endl <<"<Ville de Depart> : "<<flush;
			cin >> ws;
			getline(cin, depart);
			cout << "<Ville d'Arrivee> : "<< flush;
			cin >> ws;
			getline(cin, arrivee);
			cout << "<Moyen de Transport> : "<< flush;
			cin >> ws;
			getline(cin, transport);
			TrajetSimple *trajet = new TrajetSimple(depart.c_str(), arrivee.c_str(), transport.c_str());
			catalogue.Ajouter(trajet);
			cout << "Trajet ajoute!" << endl;
		}
		else if(choix==2)
		{
			int etapes = 0;
			cout << "Entrez le nombre d'etapes" << endl;
			cin >> etapes;
			cout << "Pour entrer vos trajets : " <<endl<< "   Un trajet par ligne" << endl << "   depart arrivee transport" << endl;
			cout << "A vous de jouer" <<endl;
			char lastArrivee[TAILLE];
			TrajetCompose *newTrajetC = new TrajetCompose();
			for(int i = 0 ; i<etapes ;i++)
			{
				cout << "Etape n° "<<i<<" : "<< endl <<"<Ville de Depart> : "<<flush;
				cin >> ws;
				getline(cin, depart);
				cout << "<Ville d'Arrivee> : "<<flush;
				cin >> ws;
				getline(cin, arrivee);
				cout << "<Moyen de Transport> : "<<flush;
				cin >> ws;
				getline(cin, transport);

				if(strcmp(depart.c_str(), arrivee.c_str())==0)
				{
					cout << "Depart et arrivee sont les memes, essayez encore" << endl;
					i--;
					continue;
				}
				if(i!=0 && strcmp(lastArrivee, depart.c_str())!=0)
				{
					cout << "La ville de depart ne correspond pas a la ville d'arrivee de l'etape precedente" << endl;
					i--;
					continue;
				}
				TrajetSimple *ts = new TrajetSimple(depart.c_str(), arrivee.c_str(), transport.c_str());
				newTrajetC->AjouterTrajet(ts);
				strcpy(lastArrivee, arrivee.c_str());
			}
			catalogue.Ajouter(newTrajetC);
			cout << "Votre trajet compose a ete ajoute" << endl;
		}
		else if(choix == 3)
		{
			cout << "------------------------------------------------" << endl;
			catalogue.Afficher();
			cout << "------------------------------------------------" << endl;
		}
		else if(choix == 4)
		{
			string dep;
			string arr;
			cout << "Recherche de trajet : " << endl << "Saisissez votre recherche : "<<endl<<"<Ville de Depart> : "<< flush;
			cin >> ws;
			getline(cin, dep);
			cout <<"<Ville d'Arrivee> :"<< flush;
			cin >> ws;
			getline(cin, arr);
			catalogue.RechercheComplexe(dep.c_str(), arr.c_str());
		}
		else if (choix == 5)
		{
			int choixSauv;
			string nomFichier;
			cout << "------------------------------------------------------" << endl;
			cout << "Quels trajets voulez vous sauvegarder ?" << endl << "1 : Tous les trajets" << endl <<"2 : Trajets directs uniquement" << endl <<"3 : Trajets avec etape uniquement" << endl << "4 : Trajets partant de ..." << endl << "5 : Trajets a destination de ..."  << endl <<"6 : Trajets partant de ... et a destination de ..." << endl << "7 : Trajets numero ... a ..." << endl;
			cout << "------------------------------------------------------" << endl;
			cin >> choixSauv;
			cout << "Veuillez choisir un nom de fichier" << endl;
			cin >> nomFichier;
			
			switch(choixSauv)
			{
				case 1 :
					// Tous les trajets
					catalogue.Sauvegarder(nomFichier);
					break;
					
				case 2 :
					// Trajets simples
					catalogue.Sauvegarder(nomFichier, true);
					break;
					
				case 3 :
					// Trajets composes
					catalogue.Sauvegarder(nomFichier, false);
					break;
					
				case 4 :
				{
					// Trajet avec selection depart
					string nomDepart;
					cout << "Veuillez entrer votre ville de depart" << endl;
					cin >> ws;
					getline(cin, nomDepart);
					catalogue.Sauvegarder(nomFichier, nomDepart, true);
					break;
				}
										
				case 5 :
				{
					// Trajets avec selection arrivee
					string nomArrivee;
					cout << "Veuillez entrer votre ville d'arrivee" << endl;
					cin>>ws;
					getline(cin, nomArrivee);
					catalogue.Sauvegarder(nomFichier, nomArrivee, false);
					break;
				}
					
				case 6 :
				{
					// Trajets avec selection depart et arrivee
					string arrivee;
					string depart;
					cout << "Veuillez entrer votre ville de depart" << endl;
					cin>>ws;
					getline(cin, depart);
					cout << "Veuillez entrer votre ville d'arrivee" << endl;
					cin>>ws;
					getline(cin, arrivee);
					catalogue.Sauvegarder(nomFichier, depart, arrivee);
					break;
				}
					
				case 7 :
				{
					// Trajets numero
					int borneInf;
					int borneMax;
					cout << "Veuillez entrer la borne minimale de la selection" << endl;
					cin >> borneInf;
					cout << "Veuillez entrer la borne maximale de la selection" << endl;
					cin >> borneMax;
					catalogue.Sauvegarder(nomFichier, borneInf, borneMax);
					break;
				}
				default :
					cout << "Votre choix n'est pas valide. Retour au menu" << endl;
			}
		}
		
		else if(choix == 6)
		{
			int choixCharg;
			string nomFichier;
			cout << "------------------------------------------------------" << endl;
			cout << "Quels trajets voulez vous charger ?" << endl << "1 : Tous les trajets" << endl <<"2 : Trajets directs uniquement" << endl <<"3 : Trajets avec etape uniquement" << endl << "4 : Trajets partant de ..." << endl << "5 : Trajets a destination de ..."  << endl <<"6 : Trajets partant de ... et a destination de ..." << endl << "7 : Trajets numero ... a ..." << endl;
			cout << "------------------------------------------------------" << endl;
			cin >> choixCharg;
			cout << "Veuillez choisir le nom du fichier a charger" << endl;
			cin >> nomFichier;
			// VERIFICATION DE L'EXTENSION DU FICHIER
			if(nomFichier.size() >=4)
			{
				string extensionFichier = nomFichier.substr(nomFichier.size()-4, nomFichier.size());
				if(extensionFichier.compare(".txt")!=0)
				{
					nomFichier.append(".txt");
				}
			}
			else
			{
				nomFichier.append(".txt");
			}
			
			switch(choixCharg)
			{
				case 1 :
					// Tous les trajets
					catalogue.Charger(nomFichier);
					break;
					
				case 2 :
					// Trajets simples
					catalogue.Charger(nomFichier, true);
					break;
					
				case 3 :
					// Trajets composes
					catalogue.Charger(nomFichier, false);
					break;
					
				case 4 :
				{
					// Trajet avec selection dÈpart
					string nomDepart;
					cout << "Veuillez entrer votre ville de depart" << endl;
					cin >> ws;
					getline(cin, nomDepart);
					catalogue.Charger(nomFichier, nomDepart, true);
					break;
				}
					
				case 5 :
				{
					// Trajets avec selection arrivee
					string nomArrivee;
					cout << "Veuillez entrer votre ville d'arrivee" << endl;
					cin >> ws;
					getline(cin, nomArrivee);
					catalogue.Charger(nomFichier, nomArrivee, false);
					break;
				}
					
				case 6 :
				{
					// Trajets avec selection depart et arrivee
					string nomArrivee;
					string nomDepart;
					cout << "Veuillez entrer votre ville de depart" << endl;
					cin >> ws;
					getline(cin, nomDepart);
					cout << "Veuillez entrer votre ville d'arrivee" << endl;
					cin >> ws;
					getline(cin, nomArrivee);
					catalogue.Charger(nomFichier, nomDepart, nomArrivee);
					break;
				}
					
				case 7 :
				{
					// Trajets numero
					int borneInf;
					int borneMax;
					cout << "Veuillez entrer la borne minimale de la selection" << endl;
					cin >> borneInf;
					cout << "Veuillez entrer la borne maximale de la selection" << endl;
					cin >> borneMax;
					if (borneInf <= borneMax) // Il y a d'autres test ‡ vÈrifier
					{
						catalogue.Charger(nomFichier, borneInf, borneMax);
					}
					else {
						cout << "La borne minimale doit eter plus petite ou egale a la borne maximale " << endl;
					}
					break;
				}
					
				default :
					cout << "Votre choix n'est pas valide. Retour au menu" << endl;
			}
		}

		else if (choix == 7)
		{
			cout << "A bientot" << endl;
			break;
		}
		else
		{
			cout << "Votre choix n'est pas valide"<< endl;
		}
	}

	return 0;
}
//-------------------------------------------------------- Fonctions amies

//----------------------------------------------------- M√©thodes publiques

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- M√©thodes prot√©g√©es

//------------------------------------------------------- M√©thodes priv√©es

