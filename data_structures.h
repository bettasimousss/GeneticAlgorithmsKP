#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;

const int MAX_SIZE=2000;
/** Paramètres **/

struct cluster_parameters{
    int s; // Nombre de noeuds alloués
    int interv_migr; // Nombre d'itérations = intervalle de migration
    float taux_migr; // Taux de migration
};

struct AG_parameters{
   int N; // Taille de la population
   char initial; // stratègie d'initialisation
   int ratio=50; //le p pour le mixte, entre 0 et 100
   float p; // Taux de population intermédiaire
   float Pc; // Probabilité de croisement
   float Pm; // Probabilité de mutation
   char select_str; // Stratégie de sélection
   char rempl_str; // Stratégie de remplacement
   char mut_meth;  // Méthode de mutation
   char crois_meth; // Méthode de croisement
   //int k; // Nombre d'adversaires par tournois
   char critere_arret; // Critère d'arrêt de l'algorithme
   int nb_it; // Nombre d'itérations maximales
   float epsilon; // Ecart maximal toléré
   float taux_evol; // Taux d'évolution
   float seuil_Reparation; // Seuil sur le nombre d'individus invalides après reproduction (croisement-> mutation)
};

/** Solution **/
struct solution{
    int chromosome[MAX_SIZE];
    float eval;
    int volumeCons;
};

/** Population **/
struct IndividuCompare
{
    bool operator()(const solution &t1, const solution &t2) const
    {
        return t1.eval > t2.eval;
    }
};

struct mouvement{
    int i; // premier mouvement à interdire dans la liste tabou
    int inb; // nombre d'objet dans la position i
    int j; // 2eme mouvement à interdire dans la liste tabou
    int jnb; // nombre d'objet dans la position j
};
struct movSol{
    solution s;
    mouvement mov;
};
