#include <iostream>
#include <time.h>
#include <queue>
#include "data_structures.h"
#include "result_ag.h"
#include <qwidget.h>


using namespace std;

/*** Variables globales ***/
extern vector<solution> population_act;
extern vector<solution> population_int;
extern vector<int>  listIndividuToReper;
extern float fitness_total;
extern AG_parameters param;
extern cluster_parameters cparam;

/** Paramètres du problème **/
extern int nbobj;
extern int **MVB;
extern int *order;
extern int volumeSac;
extern int min_volume;


/*** Génération de nombres aléatoires ***/
int random_number();
int bounded_random(int min, int max);
float random_01();

/**** Manipulation de la population ****/
void addIndividu(solution i);
int rechercheDicho(float tab[], int nbVal, float val);

/*** Stratégies de sélection ***/
vector<solution> str_sel_roue(); //Utilise les variables globales : population actuelle et p
vector<solution> str_sel_random(); // Utilise les variables globales : population actuelle et p
vector<solution> str_sel_ellitiste(); // Utilise les variables globales : population actuelle et p
vector<solution> selection(); // Multiplexer selon le choix de la stratégie

/*** Opérateurs génétiques  ***/
vector<solution> croisement_1pt(solution p,solution m);
vector<solution> croisement_2pt(solution p,solution m);
solution mutation_del(solution s);
solution mutation_add(solution s);
solution mutation_exchange(solution s);
solution reparation(solution s);

vector<solution> select_crois(solution p, solution m);
solution select_mut(solution s);

/*** Reproduction ***/

void croiser(int nb_couples);
void muter();
void remplacer();

/*** Récupération de la population  initiale à partir d'un fichier ***/
void recup_Pinit(char* filename);

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);

/*** Affichage de l'individu --> debugging ***/
void print_individu(solution s);


/*** Lecture des données du problème **/

void tri_tableau_strategie();
void init_tableau_strategie(char* filename);
void recup_data_strategie(char filepath[512]);

/*** Algorithme génétique ***/
void recup_AGparam(char* paramFile,int saut=0);
void AG(AG_parameters paramAG, char* pop_init_file,QWidget* parent);
bool check_arret(int it, float taux_evol, float diff);

/*** Génération de la population intiale ***/
solution initialiser_solution(int taille);
void initialeMixte(int nombrePopulation, int p=50,int q=50);
void initialeGreedyAleatoire(int nombrePopulation);
int* CalculerPoidsDepasse(int * solution);
void initialeAleatoire(int nombrePopulation,int diversification=0);

/** print population **/
void print_population(vector<solution> pop);
