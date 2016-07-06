#include <iostream>
#include<cstdlib>
#include<ctime>
#include <functional>
#include <algorithm>
#include <stack>
#include <stddef.h>
#include <list>
#include <fstream>
#include <math.h>
#include "KnackSack.h"
#include <string>
#include <vector>
#include <sstream>
#include <time.h>
#include "generation_initiale.h"
priority_queue<solution,vector<solution>,IndividuCompare> population_act;


void initialeAleatoire(int nombrePopulation,int diversification)
{
    recup_data("/home/koopa/save.txt"); //MVB a été initialisé
    solution solution_actif; //on va l'utiliser dans les boucles
    int idObjet=0,nbrObjettemp=0,nbrObjet=0,poids=0,benefice=0;
   int uniforme=0,poids2=0;
    for(int i=0; i< nombrePopulation;i++)
    {
        nbrObjet=0;
        solution_actif = initialiser_solution(N);
        while(solution_actif.volumeCons<volumeSac){
idObjet= rand()%N;
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
//        solution_actif.volumeCons=0;
//        solution_actif.eval=0;

//        for (int jj=0;jj<N;jj++)
//        {
//            solution_actif.volumeCons+=solution_actif.chromosome[jj]*MVB[0][jj];
//            solution_actif.eval+=solution_actif.chromosome[jj]*MVB[1][jj];


//        }
        population_act.push(solution_actif); //hnaya
    }
//    for (int ii=0;ii<nombrePopulation;ii++){
//                    cout << "\nchromosome : "<< ii<<"\n";
//    solution_actif=population_act.top();
//    population_act.pop();
//                    for(int j=0;j<N;j++)
//                    {
//                        cout << solution_actif.chromosome[j]<<"\t";
//                    }
//                            cout<<solution_actif.eval;
//    }

    ofstream trace;
    trace.open("trace.txt");
    trace << "begin date\n";
        trace << nombrePopulation<<"\n";
    trace << N<<endl;
    for (int ii=0;ii<nombrePopulation;ii++){
//                    trace << "\nchromosome : "<< ii<<"\n";
    solution_actif=population_act.top();
    population_act.pop(); //at(ii)
                    for(int j=0;j<N;j++)
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

int* CalculerPoidsDepasse(int * solution)
{
    int * Poids = new int[N];
    for(int i=0; i<N; i++)
    {Poids[i] = 0;
        if(solution[i] == 1){ Poids[i]+=MVB[0][i];}

   return Poids;
}}


void initialeGreedyAleatoire(int nombrePopulation)
{
    recup_data("/home/koopa/save.txt"); //MVB a été initialisé
    int** MVB2;
    MVB2=new int*[2];
    MVB2[0]=new int[N];
    MVB2[1]=new int[N];
    for (int kk=0; kk<2;kk++)
    {
        for (int ll=0;ll<N;ll++)
        {
MVB2[kk][ll]=MVB[kk][ll];
        }
    }
   tri_tableau();

    solution solution_actif,solution_actif2; //on va l'utiliser dans les boucles
    int idObjet=0,nbrObjettemp=0,nbrObjet=0,poids=0,benefice=0;
    node nac;
    node nf;
    int ZAleatoire=0;
    list<int> MSA,L,temp;
    nac=creer_noeud(L,0,0);
    nac.obj_dad=0;
   int uniforme=0,poids2=0;

   int k=0;
    for(int i=0; i< nombrePopulation;i++)
    {
        k=0;
        solution_actif = initialiser_solution(N);
        while(solution_actif.volumeCons<volumeSac ){
            nbrObjet=0;
idObjet=order[k];
int b=0;
if (k != 0){
uniforme = rand()%k;}
poids = MVB2[0][idObjet];
benefice = MVB2[1][idObjet];
nbrObjettemp = rand()%(volumeSac/(poids));
nbrObjet+=nbrObjettemp;
solution_actif.chromosome[idObjet]+= nbrObjettemp;
solution_actif.volumeCons+=nbrObjettemp*poids;
solution_actif.eval+=nbrObjettemp*benefice;
k= (k+1)%N;
     }
        solution_actif2 = initialiser_solution(N);

        solution_actif.chromosome[idObjet]-= nbrObjettemp;
        solution_actif.volumeCons-=nbrObjettemp*poids;
        solution_actif.eval-=nbrObjettemp*benefice;


        population_act.push(solution_actif);//hna
    }
//    for (int ii=0;ii<nombrePopulation;ii++){
//                    cout << "\nchromosome : "<< ii<<"\n";
//    solution_actif=population_act.top();
//    population_act.pop();
//                    for(int j=0;j<N;j++)
//                    {
//                        cout << solution_actif.chromosome[j]<<"\t";
//                    }
//                            cout<<solution_actif.eval;
//    }
    ofstream trace;
    trace.open("/home/koopa/trace.txt");
    trace << "begin date\n";
        trace << nombrePopulation<<"\n";
    trace << N<<endl;
    for (int ii=0;ii<nombrePopulation;ii++){
//                    trace << "\nchromosome : "<< ii<<"\n";
    solution_actif=population_act.top();
    population_act.pop(); //at(ii)
                    for(int j=0;j<N;j++)
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
    recup_data("/home/koopa/save.txt"); //MVB a été initialisé
    int** MVB2;
    MVB2=new int*[2];
    MVB2[0]=new int[N];
    MVB2[1]=new int[N];
    for (int kk=0; kk<2;kk++)
    {
        for (int ll=0;ll<N;ll++)
        {
MVB2[kk][ll]=MVB[kk][ll];
        }
    }
    solution solution_actif; //on va l'utiliser dans les boucles
    int idObjet=0,nbrObjettemp=0,nbrObjet=0,poids=0,benefice=0;
   int uniforme=0,poids2=0;
   double ratio1 = (double)p/100;
   for(int i=0; i< nombrePopulation*ratio1;i++)
   {
       solution_actif = initialiser_solution(N);
       while(solution_actif.volumeCons<volumeSac){
           nbrObjet=0;
idObjet= rand()%N;
poids = MVB[0][idObjet];
benefice = MVB[1][idObjet];

nbrObjettemp = rand()%(volumeSac/((N/10)*poids));
nbrObjet+=nbrObjettemp;


solution_actif.chromosome[idObjet]+= nbrObjettemp;
solution_actif.volumeCons+=nbrObjettemp*poids;
solution_actif.eval+=nbrObjettemp*benefice;

       }

       solution_actif.chromosome[idObjet]-= nbrObjettemp;
       solution_actif.volumeCons-=nbrObjettemp*poids;
       solution_actif.eval-=nbrObjettemp*benefice;
       population_act.push(solution_actif); // hna
   }
       tri_tableau();
       int k=0;
       nbrObjet=0,nbrObjettemp=0;
        for(int i=(nombrePopulation*ratio1)+1; i< nombrePopulation;i++)
        {
            k=0;
            solution_actif = initialiser_solution(N);
            nbrObjet=0;

            while(solution_actif.volumeCons<volumeSac){
                nbrObjet=0;
    idObjet=order[k];
    poids = MVB2[0][idObjet];
    benefice = MVB2[1][idObjet];
    nbrObjettemp = rand()%(volumeSac/(poids));
    nbrObjet+=nbrObjettemp;
    solution_actif.chromosome[idObjet]= nbrObjet;
    solution_actif.volumeCons+=nbrObjet*poids;
    solution_actif.eval+=nbrObjet*benefice;
    k=(k+1)%N;
            }

            solution_actif.chromosome[idObjet]= 0;
            solution_actif.volumeCons-=nbrObjet*poids;
            solution_actif.eval-=nbrObjet*benefice;
            population_act.push(solution_actif); //wehna

        }
//for (int ii=0;ii<nombrePopulation;ii++){
//                cout << "\nchromosome : "<< ii<<"\n";
//solution_actif=population_act.top();
//population_act.pop();
//                for(int j=0;j<N;j++)
//                {
//                    cout << solution_actif.chromosome[j]<<"\t";
//                }
//                        cout<<solution_actif.eval;
//}
        ofstream trace;
        trace.open("/home/koopa/trace.txt");
        trace << "begin date\n";
            trace << nombrePopulation<<"\n";
        trace << N<<endl;
        for (int ii=0;ii<nombrePopulation;ii++){
    //                    trace << "\nchromosome : "<< ii<<"\n";
        solution_actif=population_act.top();
        population_act.pop(); //at(ii)
                        for(int j=0;j<N;j++)
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
    solution* s = new solution;
s->chromosome = new int[taille];
    for (int i=0;i<taille;i++)
    {
        s->chromosome[i]=0;
    }
    s->volumeCons=0;
    s->eval=0.0;
    return *s;
}
