// Déclaration des structures de données
#include <iostream>
#include<cstdlib>
#include<ctime>
#include <functional>
#include <algorithm>
#include <stack>
#include <stddef.h>
#include <list>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include "node.cpp"
#include <QString>
#include "data_structures.h"
#define MAX_NUMBER_OBJECTS 3

using namespace std;

struct NodeCompare
{
    bool operator()(const node &t1, const node &t2) const
    {
        return t1.eval < t2.eval;
    }

};

/*** Variables globales ***/

extern int N;
extern int **MVB;
extern int *order;
extern int volumeSac;
extern 	priority_queue<node,vector<node>,NodeCompare> NA;
extern int min_volume; //Volume du plus petit objet
extern int Ze; // Borne inférieure de la fonction objective
extern int bestZ;
extern int elag;

void knapsack_BT();


node recup_noeud(); //Récupération du prochain noeud selon stratégie de parcours
priority_queue<node,vector<node>,NodeCompare> ajouter_noeud(node n); //Ajouter le noeud à la liste des Noeuds actifs
double evaluation(int niveau,int VR);
int fct_obj(int,int,int);
node creer_noeud(list<int> L,int zpere,int v);

// Fonctions annexes
void tri_tableau();
void init_tableau(char* filename);
void suivant_inordre(node n);

void recup_data(char filepath[512]);
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim) ;

void generate_instance(char* filename, int N, int min_volume, int max_volume, int min_benefice, int max_benefice);

node LM_Branch();
void knapsack_BFS();
void knapsack_BE();


void resolution(int method);
// 0 : heuristique spécifique
// 1 : B&B avec backtracking
// 2 : B&B avec largeur d'abord
// 3 : B&B, largeur d'abord avec priorité
void retour_arriere(node n);
node getDad(node n);
node getFrereDroit(node n);

