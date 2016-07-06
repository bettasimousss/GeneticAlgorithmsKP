#include <iostream>
#include <time.h>
#include <queue>
#include "data_structures.h"

using namespace std;


// donnee du probleme
extern int nbobj_traitement;
extern int **MVB_traitement;
extern int *order_traitement;
extern int volumeSac_traitement;
extern int min_volume_traitement;


// parametre Tabu search

extern vector<mouvement> tabu_list;
extern int maxsize_tabulist;
extern int nbiter;


// muter un solution 
solution mutation_exchange(solution s,int i, int j);

// générer le voisinage
movSol best_neighbor(movSol e, int maxIt);
movSol first_improve_neighbor(movSol e, int maxIt);
movSol random_neighbor(movSol e, int maxIt);

// Gestion de la liste tabou 
solution tabuSearch(solution s, char choix, int nbiterationv);
solution tabuSearchBest(solution s, int nbiterationv,int nbiter=10);
solution tabuSearchFirst(solution s, int nbiterationv,int nbiter=10);
solution tabuSearchRandom(solution s,int nbiterationv,int nbiter=10);





//********* Comparaison ************//

bool compareSolution(solution s1,solution s2);
bool compareMouvement(mouvement m1,mouvement m2);
bool isTabu (mouvement m);


/*** Lecture des données du problème **/

void tri_tableau_traitement();
void init_tableau_traitement(char* filename);
void recup_data_traitement(char filepath[512]);

/**** Génération de nombres aléatoires ***/
int random_number_traitement();
int bounded_random_traitement(int min, int max);
float random_01_traitement();

/*** Génération de la solution initiale **/
solution LM_Branch_traitement(solution n);

//** intialisation ^^ ***//
solution init_solution(solution s);
mouvement init_mov(mouvement mov);
movSol init_movsol(movSol m);

 //************ Affichage ***//
void print_solution(solution s);
