#include <iostream>
#include <time.h>
#include <functional>
#include <stddef.h>
#include <fstream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <sstream>
#include <string>
#include <list>
#include "strategies.h"
#include <cstring>

using namespace std;

/*** Variables globales ***/
ofstream csv;
vector<solution> population_act;
vector<solution> population_int;
vector<int>  listIndividuToReper;
string row;

float fitness_total;
AG_parameters param;
cluster_parameters cparam;
int nbobj;
//int **MVB;
//int *order;
//int volumeSac;
//int min_volume;ffff

/**** Génération de nombres aléatoires ***/
int random_number()
{
    return rand();
}

int bounded_random(int min, int max)
{
    return rand()%(max-min) + min;
}

float random_01()
{
    return (float) (rand()%10000) / 10000;
}

/*** Ajout d'un individu à la population ***/
void addIndividu(solution i)
{
    population_act.push_back(i);
    fitness_total+=i.eval;
}



///********* Utilities ****/
//std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
//    std::stringstream ss(s);
//    std::string item;
//    while (std::getline(ss, item, delim)) {
//        elems.push_back(item);
//    }
//    return elems;
//}

//std::vector<std::string> split(const std::string &s, char delim) {
//    std::vector<std::string> elems;
//    split(s, delim, elems);
//    return elems;
//}

int rechercheDicho(float tab[], int nbVal, float val){

  /* déclaration des variables locales à la fonction */
  bool trouve;  //vaut faux tant que la valeur "val" n'aura pas été trouvée
  int id;  //indice de début
  int ifin;  //indice de fin
  int im;  //indice de "milieu"

  /* initialisation de ces variables avant la boucle de recherche */
  trouve = false;  //la valeur n'a pas encore été trouvée
  id = 0;  //intervalle de recherche compris entre 0...
  ifin = nbVal;  //...et nbVal

  /* boucle de recherche */
  while(!trouve && (id<=ifin)){

    im = (id + ifin)/2;  //on détermine l'indice de milieu

    trouve = (tab[im] == val);  //on regarde si la valeur recherchée est à cet indice

    if(tab[im] > val) ifin = im-1;  //si la valeur qui est à la case "im" est supérieure à la valeur recherchée, l'indice de fin "ifin" << devient >> l'indice de milieu, ainsi l'intervalle de recherche est restreint lors du prochain tour de boucle
    else id = im+1;  //sinon l'indice de début << devient >> l'indice de milieu et l'intervalle est de la même façon restreint
  }

  /* test conditionnant la valeur que la fonction va renvoyer */
  if(trouve) return(id-1);  //si on a trouvé la bonne valeur, on retourne l'indice
  else return(id);  //sinon on retourne -1
}


void recup_Pinit(char* filename)
{
    ifstream f;
    f.open(filename);
    char row[512]="";
    bool found_begin=false,eof=false,endofdata=false;
    solution s;
    string phrase;
    vector <string> tokens;
    int** chromos;
    int i=0;

    if(f.is_open())
    {
        /** Se positionner au début du jeu d'essai ***/
        while(!found_begin && !eof)
        {
            f.getline(row,512,'\n');
            if(strcmp(row,"begin data")==0) {
                found_begin=true;
            }
            if(f.eof()) eof=true;
        }
        if(found_begin)
        {
            /** Récupérer le nombre d'individus **/
            f.getline(row,512,'\n');
            param.N=atoi(row);

            chromos=new int*[param.N];

            /** Récupérer le nombre de types d'objets = taille d'un chromosome **/
            f.getline(row,512,'\n');
            nbobj=atoi(row);

            //s.chromosome=new int[nbobj];
        while(!endofdata && !eof)
        {
            chromos[i]=new int[nbobj];
            f.getline(row,512,'\n');
            if(strcmp(row,"end data")==0) endofdata=true;
            else
            {
                //Retrieve data
                phrase=((string)row);
                cout << phrase << endl;
                tokens=split(phrase,'\t');
                for(int j=0; j<nbobj; j++)
                {
                    cout << tokens[j] << endl;
                    chromos[i][j]=atoi(tokens[j].c_str());
                    s.chromosome[j]=chromos[i][j];

                }
                //s.chromosome=chromos[i];
                s.volumeCons=atoi(tokens[nbobj].c_str());
                s.eval=(float)atof(tokens[nbobj+1].c_str());
                addIndividu(s);
                i++;
            }

            if (f.eof()) eof=true;
        }
        }
        else cout<< "Debut de population introuvable" << endl;

    }
    else cout << "Fichier non ouvert" << endl;
}




/*** Stratégies de sélection ***/
vector<solution> str_sel_roue()
{
    //cout << "N = " << param.N << " portion " << param.p*param.N << endl;
    vector<solution> selection;
    int j=-1,i=1;
    float *Q;
    Q=new float[param.N];
    Q[0]=0;
    float v=0; // une variable qui suit la loi uniforme[0,1]
    vector<solution>::iterator it;
    //cout << "Q[0] = " << Q[0] << endl;
    for( it=population_act.begin();it!=population_act.end();it++)
    {
        Q[i]=(*it).eval/fitness_total + Q[i-1];
        //cout << "Q[" <<i<<"] = " << Q[i] << endl;
        i++;
    }

    //cout << "DONE WITH Q " << endl;

    for(int k=0;k<floor(param.N*param.p);k++)
    {
        v=random_01();
        //cout << "la val de v"<< v << endl;
        // Rechercher dichotomiquement la position j de v dans Q
        //cout << param.N << endl;
        j=rechercheDicho(Q,param.N,v);
        //cout << "Insertion de l'individu " << j-1 << endl;

        if(j!=-1){
            //cout <<" affiiiiiiiiiiiiiiiichit"<<endl;
            //print_individu(population_act.at(j-1));
            selection.push_back(population_act.at(j-1));
        }
        //Insertion du jème individu dans la nouvelle population
    }

    //cout << "\n\n POPULATION SELECTIONNEE PAR ROUE " << selection.size() << "\n\n";
    //free(Q);
    return selection;
}

/***  Sélection aléatoire ***/
vector<solution> str_sel_random()
{
    int v=0;
    vector<solution> selection;
    for(int i=0; i<floor(param.N*param.p);i++)
    {
        v=bounded_random(0,population_act.size()-1);
        //cout << "v= " << v << endl;
        selection.push_back(population_act.at(v));
    }

    return selection;
}

/**   Sélection élitiste **/
vector<solution> str_sel_ellitiste()
{
    std::sort(population_act.begin(),population_act.end(),IndividuCompare());
    vector<solution> selection;
    for(int i=0; i<floor(param.N*param.p) && i<population_act.size();i++)
    {
        selection.push_back(population_act.at(i));
    }

    return selection;
}

/*** Selection ***/
vector<solution> selection()
{
    switch(param.select_str)
    {
        case 'r': return str_sel_roue();
        case 'a': return str_sel_random();
        case 'e': return str_sel_ellitiste();
        default: exit(-1);
    }
}

/*** Opérateurs génétiques  ***/
vector<solution> croisement_1pt(solution p,solution m)
{
    int j=0;
    int pos=bounded_random(0, nbobj);
    //cout << "indice 1 pt : " << pos << endl;
    vector<solution> fils;

    solution fils1;
    //fils1.chromosome=new int[nbobj];
    fils1.eval=p.eval;
    fils1.volumeCons=p.volumeCons;

    solution fils2;
    //fils2.chromosome=new int[nbobj];
    fils2.eval=m.eval;
    fils2.volumeCons=m.volumeCons;

    for(j=0;j<pos;j++){
        fils1.chromosome[j]=p.chromosome[j];
        fils2.chromosome[j]=m.chromosome[j];
    }

    for(j=pos;j<nbobj;j++){
        fils1.chromosome[j]=m.chromosome[j];
        fils2.chromosome[j]=p.chromosome[j];

        fils1.eval=fils1.eval-p.chromosome[j]*MVB[1][j]+m.chromosome[j]*MVB[1][j];
        fils2.eval=fils2.eval-m.chromosome[j]*MVB[1][j]+p.chromosome[j]*MVB[1][j];

        fils1.volumeCons=fils1.volumeCons-p.chromosome[j]*MVB[0][j]+m.chromosome[j]*MVB[0][j];
        fils2.volumeCons=fils2.volumeCons-m.chromosome[j]*MVB[0][j]+p.chromosome[j]*MVB[0][j];
    }
    fils.push_back(fils1);
    fils.push_back(fils2);
    return fils;
}

vector<solution> croisement_2pt(solution p,solution m)
{
    int j=0;
    int pos1=bounded_random(0, nbobj);
    int pos2=bounded_random(0, nbobj);

    if(pos1>pos2)
    {
        j=pos2;
        pos2=pos1;
        pos1=j;
    }
    //cout << "indice 2 pt : " << pos1 << " " << pos2 << endl;
    vector<solution> fils;

    solution fils1;
    //fils1.chromosome=new int[nbobj];
    fils1.eval=p.eval;
    fils1.volumeCons=p.volumeCons;

    solution fils2;
    //fils2.chromosome=new int[nbobj];
    fils2.eval=m.eval;
    fils2.volumeCons=m.volumeCons;

    for(j=0;j<pos1;j++){
        fils1.chromosome[j]=p.chromosome[j];
        fils2.chromosome[j]=m.chromosome[j];
    }
    for(j=pos1;j<pos2;j++){
        fils1.chromosome[j]=m.chromosome[j];
        fils2.chromosome[j]=p.chromosome[j];

        fils1.eval=fils1.eval-p.chromosome[j]*MVB[1][j]+m.chromosome[j]*MVB[1][j];
        fils2.eval=fils2.eval-m.chromosome[j]*MVB[1][j]+p.chromosome[j]*MVB[1][j];

        fils1.volumeCons=fils1.volumeCons-p.chromosome[j]*MVB[0][j]+m.chromosome[j]*MVB[0][j];
        fils2.volumeCons=fils2.volumeCons-m.chromosome[j]*MVB[0][j]+p.chromosome[j]*MVB[0][j];
    }
    for(j=pos2;j<nbobj;j++){
        fils1.chromosome[j]=p.chromosome[j];
        fils2.chromosome[j]=m.chromosome[j];
    }
    fils.push_back(fils1);
    fils.push_back(fils2);
    return fils;
}

solution mutation_add(solution s)
{
    int pos=bounded_random(0,nbobj);
    //cout << "addition " << pos << endl;
    s.chromosome[pos]++;
    s.eval+=MVB[1][pos];
    s.volumeCons+=MVB[0][pos];

    return s;
}

solution mutation_del(solution s)
{
    int pos=bounded_random(0,nbobj);
    //cout << "soustraction " << pos << endl;
    if(s.chromosome[pos]>0)
    {
        s.chromosome[pos]--;
        s.eval-=MVB[1][pos];
        s.volumeCons-=MVB[0][pos];
    }
    return s;
}

solution mutation_exchange(solution s)
{
    int pos=bounded_random(0,nbobj);
    int pos2=bounded_random(0,nbobj);
    //cout << "add " << pos << endl;
    //cout << "sous " << pos2 << endl;
    s.chromosome[pos]++;
    s.eval+=MVB[1][pos];
    s.volumeCons+=MVB[0][pos];

    if(s.chromosome[pos2]>0){
        s.chromosome[pos2]--;
        s.eval-=MVB[1][pos2];
        s.volumeCons-=MVB[0][pos2];
    }
    return s;
}

solution reparation(solution s)
{
    int i=nbobj-1;
    while(s.volumeCons>volumeSac)
    {
        if (s.chromosome[i]==0)i--;
        else
            {
                s.chromosome[i]--;
                s.volumeCons-=MVB[0][i];
                s.eval-=MVB[1][i];
        }
    }
    return s;
}

vector<solution> select_crois(solution p, solution m)
{
    switch(param.crois_meth)
    {
    case '1': return croisement_1pt(p,m);
    case '2': return croisement_2pt(p,m);
    default: exit(-1);
    }
}

solution select_mut(solution s)
{
    switch(param.mut_meth)
    {
        case 'a':return mutation_add(s );
        case 'd':return mutation_del(s);
        case 'e':return mutation_exchange(s);
        default: exit(-1);
    }
}

/*** Reproduction ***/
void croiser(int nb_couples)
{
    population_act.clear();
    //cout << "clearit jed yemmaha fiha douka " << population_act.size() << endl;
    int indicePere;
    int indiceMere;
    vector <solution> fils;
    float v;
    for (int i=0; i <nb_couples;i++)
    {

        //j'ai changé ici avec -1
        int mini=0;
        if ( floor(param.p*param.N) < population_int.size())
        {
            mini = floor(param.p*param.N);
        }
        else {
            mini = population_int.size();
        }
        indicePere=bounded_random(0,mini);
        indiceMere=bounded_random(0,mini);
        v=random_01();
        //cout<<"dkhelt lel merra " << i << " generit les parents" << indicePere << " " << indiceMere << " random= " << v << endl;
        if (v< param.Pc)
        {
            fils=select_crois(population_int.at(indicePere),population_int.at(indiceMere));
            population_act.push_back(fils.at(0));
            population_act.push_back(fils.at(1));

        }
        else
        {
            population_act.push_back(population_int.at(indicePere));
            population_act.push_back(population_int.at(indiceMere));
        }
    }
}

void muter()
{
    for (int i=0;i<population_act.size();i++)
    {
        float v=random_01();
        if (v<param.Pm)
        {
            population_act.at(i)=select_mut(population_act.at(i));
            //cout << "L'objet " << i << " sera muted" << endl;
        }
        if (population_act.at(i).volumeCons >volumeSac)
                listIndividuToReper.push_back(i);
    }
}

void remplacer()
{
    int randomReplace;
    if(listIndividuToReper.size()<=param.seuil_Reparation*population_act.size())
    {
        //cout << "rah nekhdem bel 2 % "<< endl;
        // Remplacement à partir de la population intermédiaire
        for(int i=0; i<listIndividuToReper.size();i++)
        {
            randomReplace=bounded_random(0,population_int.size());
            population_act.at(listIndividuToReper.at(i))=population_int.at(randomReplace);
        }
    }
    else
    {
        //cout << "manekhdemch biha <_< "<< endl;
        // Réparation
        for(int i=0; i<listIndividuToReper.size();i++)
        {
            population_act.at(listIndividuToReper.at(i))=reparation(population_act.at(listIndividuToReper.at(i)));
        }
    }

    // Remplissage
    switch(param.rempl_str)
    {
    case 'm':
        {
            //cout << " \n\n\n\nLOL" << param.N - population_act.size() << endl;
            std::sort(population_int.begin(),population_int.end(),IndividuCompare());
            int nbARemplir=param.N-population_act.size();
            for(int i=0; i<nbARemplir;i++)
            {
                population_act.push_back(population_int.at(i));
                //cout << "rah nzid whda " << endl;
            }
            break;
        }

    case 'e':
        {
            std::sort(population_act.begin(),population_act.end(),IndividuCompare());
            while(population_act.size()>param.N)
            {
                population_act.pop_back();
            }
            break;
        }

    case 'g':
        {
            std::sort(population_int.begin(),population_int.end(),IndividuCompare());
            for(int i=0; i<param.N-population_act.size();i++)
            {
                population_act.push_back(population_int.at(i));
            }
            break;
        }

    default: break;
    }

}

/*** Affichage de l'individu --> debugging ***/
void print_individu(solution s)
{
    cout << "Chromosome " << endl;
    for(int i=0; i<nbobj ; i++)
    {
        cout << " " << s.chromosome[i];
        //cout << "Obj " << i << "Quantite " << s.chromosome[i] << endl;
    }

    cout << endl;
    cout << "  Volume consomme = " << s.volumeCons << " Fitness = " << s.eval  << endl;
}


/*** Récupération des données du problème ***/

void tri_tableau_strategie()
{
    int saveTaille=nbobj;
    int save0,save1,save2;
    bool permutation=false;
    // Tri

    do
    {
        permutation=false;
        for(int i=0;i<saveTaille-1;i++){

            if((double)MVB[1][i]/(double)MVB[0][i] < (double)MVB[1][i+1]/(double)MVB[0][i+1])
            {
                permutation=true;
                save0=MVB[0][i+1];
                MVB[0][i+1]=MVB[0][i];
                MVB[0][i]=save0;

                save1=MVB[1][i+1];
                MVB[1][i+1]=MVB[1][i];
                MVB[1][i]=save1;

                save2=order[i+1];
                order[i+1]=order[i];
                order[i]=save2;

                //cout << "si si je trie";
            }
        }
        saveTaille--;

    } while (permutation);


}


void init_tableau_strategie(char* filename)
{
    //Récupère les données à partir du benchmark
    recup_data_strategie(filename);
}


/***** Récupération des données à partir du fichier benchmark *****/
void recup_data_strategie(char* filepath)
{
    char row[512]="";
    vector <string> tokens;
    string phrase;
    bool found_begin=false,eof=false,endofdata=false;
    // Ouverture du fichier
    ifstream file;
    file.open(filepath);
    int i=0;
    int tmp=0;

    if(file.is_open())
    {
        //cout << "DEBUG !! OPEN";
        // Parcours jusqu'à trouver la ligne begin data
        while(!found_begin && !eof)
        {
            file.getline(row,512,'\n');
            //cout << "\n " << row;
            if(strcmp(row,"begin data")==0) {
                found_begin=true;
                //cout<<"BEGIN!";
            }
            if(file.eof()) eof=true;
        }

        // Récupération des lignes de données et copie dans la matrice
        if (found_begin){
            // Récupérer taille du problème et volume du sac
            file.getline(row,512,'\n');
            //cout << row;
            nbobj=atoi(row);
            //cout << nbobj;
            file.getline(row,512,'\n');
            //cout << row;
            volumeSac=atoi(row);
            //cout << volumeSac;
            file.getline(row,512,'\n');
            //cout << row
            min_volume=atoi(row);
            //cout << min_volume;

            MVB=new int*[2];
            MVB[0]=new int[nbobj];
            MVB[1]=new int[nbobj];
            order=new int[nbobj];

            for(int z=0;z<nbobj; z++) order[z]=z;

        while(!endofdata && !eof)
        {
            file.getline(row,512,'\n');
            //cout<< "\nLigne" << row;
            //process the row
            if(strcmp(row,"end data")==0) endofdata=true;
            else
            {
                //Retrieve data
                phrase=((string)row);
                tokens=split(phrase,'\t');
                //cout << "\n" << atoi(tokens[0].c_str()) << "  " << atoi(tokens[1].c_str());
                tmp=atoi(tokens[0].c_str());
                if(tmp<min_volume) min_volume=tmp;
                MVB[0][i]=tmp;
                MVB[1][i]=atoi(tokens[1].c_str());
                if(MVB[1][i]==0)
                {
                    //cout << "\n ici";
                    MVB[1][i]=atoi(tokens[2].c_str());
                }
                i++;
            }

            if (file.eof()) eof=true;
        }
        }

        else
        {
            cout << "Format de fichier incorrect !";
        }
        // Fermeture du fichier
        file.close();

    }

    else cout << "Fichier non ouvert";

}


void AG(AG_parameters paramAG, char* pop_init_file,QWidget* parent)
{
    std::vector<int> tableau,tableau2;
    int it=0;
    float taux_evol=0;
    float bestEval=0;

    float ref=volumeSac*MVB[1][0]/MVB[0][0];

    //population_act.clear();
    // Génération de la population initiale
    //recup_Pinit(pop_init_file);

    //cout << endl << endl << "\t POPULATION initiale de taille" << population_act.size() << endl;
    //print_population(population_act);
    //getchar();

    // Exécution de l'algorithme génétique


    //bookmark ouvrir csv
    //std::ios_base::app
    csv.open("/home/koopa/result.csv",std::ios_base::app);

   // csv<<"N;pop_inter;Prob_croisement;Prob_mutation; Strategie selection;strategie remplacement;methode mutation;methode croisement;";
  //    csv<<    "critere arret; nbr iterations;epsilon;taux evolution; seuil reparation;Fitness;Volume;Temps Execution\n";



    csv<<param.N<<";";

    switch (param.initial){
    case 'a':
        csv<<"aléatoire"<<";";
             break;
    case 'g' :
        csv <<"Greedy Aléatoire"<<";";
        break;
    case 'm':
        csv<<"Mixte("<<param.ratio<<",";
        csv<<100-param.ratio<<");";

    }
        csv<<param.p<<";"<<param.Pc<<";"<<param.Pm<<";";
    switch (param.select_str)
    {
    case 'e' :
    csv<<"elitiste"<<";";break;
    case 'r' :
    csv<<"roue"<<";";break;
    case 'a' :
    csv<<"aléatoire"<<";";break;

    }


    //mettez ici le nom de la méthode significative au lieu du symbole, sinvoupliz
    switch (param.rempl_str)
    {
    case 'm' :
    csv<<"50/50"<<";";break;
    case 'e' :
    csv<<"elitiste"<<";";break;
    case 'g' :
    csv<<"générationnelle"<<";";break;

    }
    switch (param.mut_meth)
    {

    //hna tanik dirou les noms de methodes significatives
    case 'a' :
    csv<<"add"<<";";break;
    case 'd' :
    csv<<"delete"<<";";break;
    case 'e' :
    csv<<"exchange"<<";";break;

    }
    switch (param.crois_meth)
    {

    //hna tanik dirou les noms de methodes significatives
    case '1' :
    csv<<"1pt"<<";";break;
    case '2':
    csv<<"2pts"<<";";break;


    }
    switch (param.critere_arret)
    {
    case 'i' :
    csv<<"nbr iterations"<<";";break;
    case 'e' :
    csv<<"taux d'évolution"<<";";break;
    case 's' :
    csv<<"seuil"<<";";break;

    }
    csv<<param.nb_it<<";"<<param.epsilon<<";"<<param.taux_evol<<";"<<param.seuil_Reparation<<";";
Result_AG *fen = new Result_AG(parent);


clock_t begin1 = clock();

    switch(param.initial)
    {
    case 'a' :
        initialeAleatoire(param.N);break;

    case 'g' :
        initialeGreedyAleatoire(param.N);
        break;
    case 'm' :
        initialeMixte(param.N,param.ratio,100-param.ratio);
    }
    clock_t end1 = clock();
    double elapsed_secs1 = double(end1 - begin1) / CLOCKS_PER_SEC;
    ofstream Duree;
    Duree.open("/home/koopa/duree.txt");
    Duree<<elapsed_secs1<<endl;





    while(!check_arret(it,taux_evol,abs(bestEval-ref)))
    {
        // Selection
        population_int=selection();
        //cout << endl << endl << "\t POPULATION SELECTIONNEE A L'ITERATION " << it << endl;
        //print_population(population_int);
        // Reproduction
        //1. Croisement
        switch(param.rempl_str)
        {
        case 'e':
            {
                croiser(param.N);
                break;
            }
        case 'm':
            {
                croiser(floor((float) param.N/4));
                break;
            }
        default:
            {
                croiser(floor((float) param.N/2));
                break;
            }
        }
        //2. Mutation
        muter();
        //3. Remplacement
        remplacer();
        population_int.clear();

        // il faut mettre a jour le taux d'evolution ^^
        // the level of feelings is too damn high #ba3oucha
        bestEval=population_act.at(0).eval;
        if (it == param.nb_it)
        {
csv<<bestEval<<";"<<population_act.at(0).volumeCons<<";";
csv.close();
        }
        cout << " Meilleure solution de la generation " << it << " eval=" << bestEval << " Volume= " << population_act.at(0).volumeCons<< endl << endl;
tableau.push_back(bestEval);
tableau2.push_back(population_act.at(0).volumeCons);
        it++;
    }

std::sort(tableau.begin(),tableau.end());
std::sort(tableau2.begin(),tableau2.end());

    fen->setNbrLigne(it-1);
    int zz=0,w=0;
    //fen->setTableauGen(0,0,1);
    fen->majtab(50);

    while(zz<nbobj)
    {
        if (population_act.at(0).chromosome[zz] != 0)
        {
            fen->setTableauGen(w,0,zz);
            fen->setTableauGen(w,1,population_act.at(0).chromosome[zz]);
            w++;
        }
        zz++;
    }
    //fen->majtab(w+10);

fen->InitTab();
int i=tableau.size()-1,j=it-1;
    while (i > 0)
    {
    fen->setTableau(1,it-j-1,tableau.at(i));
    i--;
//    cout << "element["<<0<<"]["<<j<<"]="<<fen->getTableau(0,j)<<endl;

    fen->setTableau(0,it-j-1,tableau2.at(i));
//    cout << "element["<<1<<"]["<<j<<"]="<<fen->getTableau(1,j)<<endl;
j--;

    }
    clock_t end2 = clock();
    double elapsed_secs2= double(end2 - begin1) / CLOCKS_PER_SEC;
    Duree<<elapsed_secs2<<endl;
    Duree.close();
    fen->DureeT();
    fen->show();
}

bool check_arret(int it, float taux_evol, float diff)
{
    bool arret=false;

    switch(param.critere_arret)
    {
    case 'i':
        {
            // Nombre d'itérations
            if(it>param.nb_it) arret=true;
            break;
        }
    case 'e':
        {
            // Taux d'évolution
            if(taux_evol<param.taux_evol) arret=true;
            break;
        }

    case 's':
        {
            // Seuil de différence vis-à-vis de la meilleure évaluation possible
            if(diff>param.epsilon) arret=true;
            break;
        }
    default: break;
    }

    return arret;
}


/***** Génération de la population initiale ****/

void initialeAleatoire(int nombrePopulation,int diversification)
{
    //recup_data("D:\\Exo_TD.txt"); //MVB a été initialisé
    solution solution_actif; //on va l'utiliser dans les boucles
    int idObjet=0,nbrObjettemp=0,nbrObjet=0,poids=0,benefice=0;
    int uniforme=0,poids2=0;

    for(int i=0; i< nombrePopulation;i++)
    {
        nbrObjet=0;
        solution_actif = initialiser_solution(nbobj);
        while(solution_actif.volumeCons<volumeSac){
        idObjet= rand()%nbobj;
        poids = MVB[0][idObjet];
        benefice = MVB[1][idObjet];
        nbrObjettemp = rand()%(volumeSac/(poids));
        nbrObjet+=nbrObjettemp;
        if (diversification != 0)
        {
            uniforme = rand()%100;
            if (uniforme < diversification)
            {
                nbrObjettemp/=(diversification/10);
            }
        }
        solution_actif.chromosome[idObjet]+= nbrObjettemp;
        solution_actif.volumeCons+=nbrObjettemp*poids;
        solution_actif.eval+=nbrObjettemp*benefice;
        }
        solution_actif.chromosome[idObjet]-= nbrObjettemp;
        solution_actif.volumeCons-=nbrObjettemp*poids;
        solution_actif.eval-=nbrObjettemp*benefice;

        population_act.push_back(solution_actif);
    }
        ofstream trace;
        trace.open("/home/koopa/population.txt");
        trace << "begin data\n";
        trace << nombrePopulation<<"\n";
        trace << nbobj <<endl;
        for (int ii=0;ii<nombrePopulation;ii++){
        //trace << "\nchromosome : "<< ii<<"\n";
        solution_actif=population_act.at(ii);
         for(int j=0;j<nbobj;j++)
             {
                trace << solution_actif.chromosome[j]<<"\t";
              }
              trace<<solution_actif.volumeCons<<"\t";
              trace<<solution_actif.eval;
              trace<<"\n";
        }
        trace<<"end data";
        trace.close();

}

int* CalculerPoidsDepasse(int * solution){
    int * Poids = new int[nbobj];
    for(int i=0; i<nbobj; i++)
    {
        Poids[i] = 0;
        if(solution[i] == 1) Poids[i]+=MVB[0][i];
    }
   return Poids;
}


void initialeGreedyAleatoire(int nombrePopulation)
{
    solution solution_actif,solution_actif2; //on va l'utiliser dans les boucles
    int idObjet=0,nbrObjettemp=0,nbrObjet=0,poids=0,benefice=0;
    int ZAleatoire=0;
    int uniforme=0,poids2=0;
    int k=0;
    for(int i=0; i< nombrePopulation;i++)
    {
        k=0;
        solution_actif = initialiser_solution(nbobj);
        while(solution_actif.volumeCons<volumeSac ){
            nbrObjet=0;
        idObjet=order[k];
        int b=0;
        if (k != 0){
        uniforme = rand()%k;}
        poids = MVB[0][idObjet];
        benefice = MVB[1][idObjet];
        nbrObjettemp = rand()%(volumeSac/(poids));
        nbrObjet+=nbrObjettemp;
        solution_actif.chromosome[idObjet]+= nbrObjettemp;
        solution_actif.volumeCons+=nbrObjettemp*poids;
        solution_actif.eval+=nbrObjettemp*benefice;
        k= (k+1)%nbobj;
     }
        //solution_actif2 = initialiser_solution(nbobj);

        solution_actif.chromosome[idObjet]-= nbrObjettemp;
        solution_actif.volumeCons-=nbrObjettemp*poids;
        solution_actif.eval-=nbrObjettemp*benefice;


        population_act.push_back(solution_actif);
    }

    ofstream trace;
    trace.open("/home/koopa/population.txt");
    trace << "begin data\n";
        trace << nombrePopulation<<"\n";
    trace << nbobj <<endl;
    for (int ii=0;ii<nombrePopulation;ii++){
    //trace << "\nchromosome : "<< ii<<"\n";
    solution_actif=population_act.at(ii);
    //population_act.pop();
                    for(int j=0;j<nbobj;j++)
                    {
                        trace << solution_actif.chromosome[j]<<"\t";
                    }
                    trace<<solution_actif.volumeCons<<"\t";
                            trace<<solution_actif.eval;
                            trace<<"\n";

    }
    trace<<"end data";
    trace.close();
}


//mvb2, n*poids
void initialeMixte(int nombrePopulation, int p,int q)
{
   solution solution_actif; //on va l'utiliser dans les boucles
   int idObjet=0,nbrObjettemp=0,nbrObjet=0,poids=0,benefice=0;
   int uniforme=0,poids2=0;
   double ratio1 = (double)p/100;
   for(int i=0; i< nombrePopulation*ratio1+1;i++)
   {
       solution_actif = initialiser_solution(nbobj);
       while(solution_actif.volumeCons<volumeSac){
           nbrObjet=0;
            idObjet= rand()%nbobj;
            poids = MVB[0][idObjet];
            benefice = MVB[1][idObjet];
            cout << "\n ******  " << nbobj <<  "********" << idObjet << " " << MVB[0][idObjet] << " "<< endl;
            nbrObjettemp = rand()%(volumeSac/poids);
            nbrObjet+=nbrObjettemp;
            solution_actif.chromosome[idObjet]+= nbrObjettemp;
            solution_actif.volumeCons+=nbrObjettemp*poids;
            solution_actif.eval+=nbrObjettemp*benefice;
       }

       solution_actif.chromosome[idObjet]-= nbrObjettemp;
       solution_actif.volumeCons-=nbrObjettemp*poids;
       solution_actif.eval-=nbrObjettemp*benefice;
       population_act.push_back(solution_actif);}
       tri_tableau_strategie();
       int k=0;
       nbrObjet=0,nbrObjettemp=0;
        for(int i=(nombrePopulation*ratio1)+1; i< nombrePopulation;i++)
        {
            k=0;
            solution_actif = initialiser_solution(nbobj);
            nbrObjet=0;

            while(solution_actif.volumeCons<=volumeSac){
                nbrObjet=0;
                idObjet=order[k];
                poids = MVB[0][idObjet];
                benefice = MVB[1][idObjet];
                nbrObjettemp = rand()%(volumeSac/(poids));
                nbrObjet+=nbrObjettemp;
                solution_actif.chromosome[idObjet]= nbrObjet;
                solution_actif.volumeCons+=nbrObjet*poids;
                solution_actif.eval+=nbrObjet*benefice;
                k=(k+1)%nbobj;
            }

            solution_actif.chromosome[idObjet]= 0;
            solution_actif.volumeCons-=nbrObjet*poids;
            solution_actif.eval-=nbrObjet*benefice;
            population_act.push_back(solution_actif);

        }

        ofstream trace;
        trace.open("/home/koopa/population.txt");
        trace << "begin data\n";
        trace << nombrePopulation<<"\n";
        trace << nbobj <<endl;
        for (int ii=0;ii<nombrePopulation;ii++){
        //trace << "\nchromosome : "<< ii<<"\n";
        //population_act.pop();
        for(int j=0;j<nbobj;j++)
         {
           trace << solution_actif.chromosome[j]<<"\t";
          }
         trace<<solution_actif.volumeCons<<"\t";
         trace<<solution_actif.eval;
         trace<<"\n";
        }
        trace<<"end data";
        trace.close();
}


solution initialiser_solution(int taille)
{
    //solution* s = new solution;
    solution s;
    //s.chromosome = new int[taille];
    for (int i=0;i<taille;i++)
    {
        s.chromosome[i]=0;
    }
    s.volumeCons=0;
    s.eval=0.0;
    return s;
}


/*** Récupération des paramètres de l'AG ***/
void recup_AGparam(char* paramFile,int saut)
{
    ifstream f;
    f.open(paramFile);
    char row[512]="";
    bool found_begin=false,eof=false,endofdata=false;
    string phrase;
    vector <string> tokens;
    int i=0;

    if(f.is_open())
    {
        /** Se positionner au début des parametres , ce n'est pas ton code hihihihihiiii***/
        /* ceci n'est pas un commentaire*/

        //reti
        while(!found_begin && !eof)
        {
            f.getline(row,512,'\n');



            if (saut == 1){
            if(strcmp(row,"begin data\r")==0 ) {
                found_begin=true;
            }}
            else {
                if(strcmp(row,"begin data")==0 ) {
                    found_begin=true;
                }
            }



            if(f.eof()) eof=true;
        }
        if(found_begin)
        {
            /** Récupérer le nombre d'individus **/
            f.getline(row,512,'\n');
            param.N=atoi(row);

            //recupérer la méthode d'intialisation
            f.getline(row,512,'\n');
            param.initial=row[0];
            //récupérer le p et q si mixte
if (row[1] >= '0' && row[1]<='9' ){
            param.ratio = (int)atoi(row+1);}
            // recuperer le taux de la population intermediaire
            f.getline(row,512,'\n');
            param.p=(float)atof(row);


            //recuperer pc, probabilité de croisement
            f.getline(row,512,'\n');
            param.Pc=(float)atof(row);

            //recuperer pm, probabilité de mutation
            f.getline(row,512,'\n');
            param.Pm=(float)atof(row);

            //recupérer la stratégie de selection
            f.getline(row,512,'\n');
            param.select_str=row[0];

            //recupérer la stratégie de remplacement
            f.getline(row,512,'\n');
            param.rempl_str=row[0];

            //recupérer la methode de mutation
            f.getline(row,512,'\n');
            param.mut_meth=row[0];

            //recupérer la stratégie de croisement
            f.getline(row,512,'\n');
            param.crois_meth=row[0];

            //recupérer le critere d'arret
            f.getline(row,512,'\n');
            param.critere_arret=row[0];

            //recupérer le nombre d'itération
            f.getline(row,512,'\n');
            param.nb_it=atoi(row);

            //recuperer epsilon
            f.getline(row,512,'\n');
            param.epsilon=(float)atof(row);


            //recuperer taux_evolution
            f.getline(row,512,'\n');
            param.taux_evol=(float)atof(row);


            //recuperer seuil de réparation
            f.getline(row,512,'\n');
            param.seuil_Reparation=(float)atof(row);
            //la fin du fichier ou bien le monde
            f.getline(row,512,'\n');
            if (saut == 1){
            if(strcmp(row,"end data\r")==0 ) {
                found_begin=true;
            }}
            else {
                if(strcmp(row,"end data")==0 ) {
                    found_begin=true;
                }
            }            if (f.eof()) eof=true;

        }
        else cout<< "Debut des parametres introuvables" << endl;

    }
    else cout << "Fichier non ouvert" << endl;
}


/**** PRINT ****/
void print_population(vector<solution> pop)
{
    cout << endl << endl << "\t\t **** POPULATION ACTUELLE " << endl << endl;
    for(int i=0; i<pop.size(); i++)
        print_individu(pop.at(i));
}
