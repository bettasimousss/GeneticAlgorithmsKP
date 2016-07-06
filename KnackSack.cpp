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
using namespace std;
int N;
int **MVB;
int *order;
int volumeSac;
priority_queue<node,vector<node>,NodeCompare> NA;
int min_volume;
int Ze; // Borne inférieure de la fonction objective
int bestZ;
int elag;

float alpha;

void knapsack_BT()
{
/*
•	NA : l’ensemble des nœuds actifs, initialement vide.
•	nac : le nœud actif actuel.
•	bestZ : la meilleure valeur de la fonction objective actuellement, initialement nulle.
•	MSA : liste de nombre d’objets de la meilleure solution actuelle, initialement vide.
•	VR : Volume restant à remplir dans le sac, initialement le poids du sac à dos.
*/

    alpha=180;
    time_t t;
    t=clock();
    ofstream trace;
    trace.open("/home/koopa/trace.txt");
    node nac;
    node nf;
    list<int> MSA,L,temp;
    int VR=volumeSac;
    int i=0;
    int b;
    bestZ=0;

    // Branch & Bound
    //pour initialiser le noeud
    nac=LM_Branch();
    bestZ=nac.obj_dad;
    MSA=nac.L;
    nac=node(L,evaluation(-1,volumeSac),0);
    nac.volumeCons=0;
    nac.obj_dad=0;
    //nac.print_node();
    //cout << "\n Noeud initial";
    //nac.print_node();
    //retour_arriere(nac);
    NA=ajouter_noeud(nac);
    //cout << "\n Noeuds actifs number = " << NA.size();
    int nb=0;
    elag=0;

    while (!NA.empty())
    {
        //cout << "Taille de la file" << NA.size() << endl;
        //getchar();
        nb++;
        nac=recup_noeud();
        cout << "\n\n";
        cout <<" \n ************  Noeud courant it= " << nb << " " ;
        trace <<" \n ************  Noeud courant it= " << nb << " eval=" << nac.eval << " obj=" << nac.obj_dad << endl;
        //nac.print_node();
        cout << "\n\n";

        i=nac.L.size();

        cout <<" \n ************  Niveau X" << i << " " ;
        trace <<" \n ************  Niveau X" << i << " " << endl;

        if(floor(nac.eval)>(bestZ+alpha))
        {
            cout << "\n Meilleure evaluation " << nac.eval;
            trace << "\n Meilleure evaluation " << nac.eval << endl;
            if(volumeSac-nac.volumeCons<min_volume)
            {
                // Solution exacte
                bestZ=nac.obj_dad;
                MSA=nac.L;
                cout << "\n Solution exacte " << bestZ;
                trace << "\n Solution exacte " << bestZ << endl;

                // Enelever le noeud + Aller au suivant_inordre
                //NA.pop();
                retour_arriere(nac);
            }
            else
            {
                // Générer fils gauche
                b=(volumeSac-nac.volumeCons)/MVB[0][i];
                temp=nac.L;
                while (b==0)
                {
                  temp.push_back(0);
                  i++;
                  b=(volumeSac-nac.volumeCons)/MVB[0][i];
                }
                //cout << "\n max objets b pour X" << i << " = "<<b << " MVB = " << MVB[0][i] << " " << MVB [1][i];
                //trace << "\n max objets b pour X" << i << " = "<<b << " MVB = " << MVB[0][i] << " " << MVB [1][i] << endl;

                temp.push_back(b);
                nf=creer_noeud(temp,0,nac.volumeCons+b*MVB[0][i]);
                nf.obj_dad=fct_obj(nac.obj_dad,i,b);
                nf.eval=nf.obj_dad+evaluation(i,volumeSac-nf.volumeCons);
                //nf.print_node();
                if(floor(nf.eval)>(bestZ+alpha)) NA=ajouter_noeud(nf);
                else retour_arriere(nf);

            }
        }
        else // Elagage + backtracking
        {
            // Elagage
            elag++;
            //NA.pop();
            // aller au suivant_inordre
            retour_arriere(nac);
        }
    }

                /*******  Résultats ********/
    cout << "\n \n \n Résultat \n ";
    trace << "\n \n \n Résultat \n " << endl;
    int k=0;
    int volumeRestant=volumeSac;
    for (list<int>::iterator  it = MSA.begin(); it != MSA.end(); it++)
    {
        cout << "\n Objet " << order[k] <<" --> " << (*it);
        trace << "\n Objet " << order[k] <<" --> " << (*it) << endl;
        volumeRestant-=MVB[0][k]*(*it);
        k++;
    }

    cout << "\n Objets restants = " << 0;
    trace << "\n Objets restants = " << 0 << endl;
    /*while(k<N)
    {
        cout << "\n Objet " << order[k] <<" --> 0";
        k++;
    }
*/
    cout <<"\n Bénéfice maximal : " << bestZ;
    trace <<"\n Bénéfice maximal : " << bestZ << endl;

    cout << "\n Execution Time = " << clock()-t << " ms";
    trace << "\n Execution Time = " << clock()-t << " ms" << endl;

    cout << "\n Nombre d'élagages = " << elag;
    trace << "\n Nombre d'élagages = " << elag << endl;

    cout << "\n Volume restant = " << volumeRestant;
    trace << "\n Volume restant = " << volumeRestant << endl;

    cout << "\n Meilleur objet = X" << order[0];
    trace << "\n Meilleur mobjet = X" << order[0] << endl;
}

void retour_arriere(node n)
{
   node frere;
   //cout << "Retour arriere" << endl;

  bool continu=true;

  while(continu)
  {
      if(n.L.size()==0)
      {
          //cout << "sortie de boucle " << endl;
          // Back to root
          continu=false;
      }
      else
      {
          //cout << "il y a encore du parcours" << endl;
          if(n.L.back()==0)
          {
              // Pas de frere droit
              //cout << "pas de frere droit " << endl;
              n=getDad(n);
          }
          else
          {
              //cout << "il a un frere droit" << endl;
              frere=getFrereDroit(n);
              if(floor(frere.eval)>(bestZ+alpha))
              {
                  ajouter_noeud(frere); //Noeud intéressant
                  continu=false;
              }
              else
              {
                  n=frere;
              }
          }
      }
  }

  cout << "fin retour arriere " << endl;
}

node getDad(node n)
{
    //cout << endl << "NOEUD DONT ON CHERCHE LE PERE" << endl;
    //n.print_node();
    int i=n.L.size()-1;

    if(i>=0)
    {
        node papa=n;
        int b=papa.L.back();
        papa.L.pop_back();
        papa.obj_dad-=b*MVB[1][i];
        //cout << endl << "FCT OBJECTIVE DU PERE " << papa.obj_dad;
        //getchar();
        papa.volumeCons-=b*MVB[0][i];
        // MAJ EVALUATION
        papa.eval=papa.obj_dad+evaluation(i,volumeSac-papa.volumeCons);
        return papa;
    }
    else
    {
        //cout << "HEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEYYYY CHUI LAAAA";
        return node();
    }
}

node getFrereDroit(node n)
{
    //cout << endl << "NOEUD DONT ON CHERCHE LE FRERE" << endl;
    //n.print_node();

    int b=n.L.back();
    int i=n.L.size()-1;
    double interm=0;
    if(b>0)
    {
        node frere=n;
        frere.L.pop_back();
        frere.L.push_back(b-1);
        frere.obj_dad-=MVB[1][i];
        frere.volumeCons-=MVB[0][i];
        //MAJ EVALUATION

        //interm=(double)(volumeSac-frere.volumeCons)/(double)MVB[0][i];
        //frere.eval=frere.obj_dad+interm*MVB[1][i];
        frere.eval=frere.obj_dad+evaluation(i,volumeSac-frere.volumeCons);
        //cout << endl << "eval du frere et obj" << frere.eval << "  " << frere.obj_dad << endl;
        return frere;
    }
    else
    {
        //cout << "HEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEYYYY CHUI LAAAA";
        return node();
    }
}


void suivant_inordre(node n)
{
    node so,dad;
    list<int> temp=n.L;
    int b=0;
    int i=temp.size();

    if(i>0)
    {
        b=temp.back();
        temp.pop_back();
    }

    if(b>0) // Il possède un frère droit donc même niveau i
    {
        b--;
        temp.push_back(b);
        so=node(temp,0,0);
        so.obj_dad=n.obj_dad-MVB[1][i-1];
        so.volumeCons=n.volumeCons-MVB[0][i-1];
        so.eval=so.obj_dad+evaluation(i-1,volumeSac-so.volumeCons);
        if(floor(so.eval)>bestZ)
            {
                //cout << "\n noeud pouvant etre meilleur ";
                NA=ajouter_noeud(so);
        }
        else
            {
                //cout << "\n Elagage ";
                //so.print_node();
                suivant_inordre(so); elag++;
                // getchar(); getchar();
        }
    }

    else if(i!=0) // Voir dans ses ascendants le suivant_inordre de son père
    {
        dad=node(temp,0,0);
        dad.obj_dad=n.obj_dad-b*MVB[1][i];
        dad.volumeCons=n.volumeCons-b*MVB[0][i];
        dad.eval=dad.obj_dad+evaluation(i-1,volumeSac-dad.volumeCons);
        suivant_inordre(dad);
    }

    // Dans le cas où i=0, donc au niveau de la racine, après avoir parcouru tous ses fils, il n'y a plus rien à faire.
}

node recup_noeud() // Testé -->OK
{
    node next;
    //Retourne le prochain noeud à traiter
    // Si pile non vide, dépiler l'élément en sommet de pile
    if(!NA.empty())
    {
        next= NA.top();
        NA.pop();
    }
    return next;
}

priority_queue<node,vector<node>,NodeCompare> ajouter_noeud(node n) // Testé --> OK
{
    //Ajouter un neoud à la liste
    NA.push(n);
    return NA;
}

double evaluation(int niveau,int VR)  //Testé --> OK
{
    double z=0,interm=0;
    int k=niveau+1;
    int volume=VR;

    interm=(double)VR/(double)MVB[0][k];
    //cout << "\n interm=" << interm;
    z=interm*MVB[1][k];

    //while(VR>0 && k<N)
    //{
    //	interm=(double)VR/(double)MVB[0][k];
    //	volume-=interm*MVB[0][k];
    //	z+=interm*MVB[1][k];
    //	k++;
    //}

    return z;
}

int fct_obj(int obj_dad,int i, int j)  // Testé ---> OK
{
    return obj_dad+MVB[1][i]*j;
}

node creer_noeud(list<int> L,int zpere,int v)  // Testé --> OK
{
    // Instantie un noeud
    node n(L,zpere,v);
    return n;
}

void tri_tableau()
{
    int saveTaille=N;
    int save0,save1,save2;
    bool permutation=false;
    // Tri
//    cout << "\n Va trier" << N << "  " << volumeSac << " " << min_volume;

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


void init_tableau(char* filename)
{

    //Récupère les données à partir du benchmark

    recup_data(filename);

}


/***** Récupération des données à partir du fichier benchmark *****/
void recup_data(char* filepath)
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
            N=atoi(row);
            //cout << N;
            file.getline(row,512,'\n');
            //cout << row;
            volumeSac=atoi(row);
            //cout << volumeSac;
            file.getline(row,512,'\n');
            //cout << row
            min_volume=atoi(row);
            //cout << min_volume;

            MVB=new int*[2];
            MVB[0]=new int[N];
            MVB[1]=new int[N];
            order=new int[N];

            for(int z=0;z<N; z++) order[z]=z;

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

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

node LM_Branch()
{
    int VR=volumeSac;
    list<int> L;
    int obj=0;
    int i=0;
    int b=0;
    node n;

    ofstream f;
    f.open("/home/koopa/trace.txt");

    time_t t=clock();

    while(VR>min_volume)
    {
        b=VR/MVB[0][i];
        L.push_back(b);
        obj+=b*MVB[1][i];
        VR-=b*MVB[0][i];
        i++;
    }

    n=node(L,obj,volumeSac-VR);
    n.obj_dad=obj;

//    f << "\n Solution satisfaisante - Heuristique spécifique";

    f << "\n Bénéfice maximal : " << obj;

    f << "\n Execution Time = " << clock()-t << " ms";

    f << "\n Nombre d'élagages = " << 0;

    f << "\n Volume restant = " << VR;

    f << "\n Meilleur objet = X" << order[0];

    return n;
}

void generate_instance(char* filename,int N, int min_volume, int max_volume, int min_benefice, int max_benefice)
{
    int a=0,b=0;

    ofstream f;
    f.open(filename);
    f << "begin data" << endl;
    f << N << endl;
  f << max_volume*(N+1) + rand()%max_volume*(N-1)<< endl;
  //  f<<51<<endl;
    f << max_volume << endl;

    for (int i=0; i<N; i++)
    {
        a=rand()%(max_volume-min_volume) + min_volume;

        b=rand()%(max_benefice-min_benefice) + min_benefice;
        f <<a << "\t" << b << endl;
    }
    f << "end data";

    f.close();
}



void knapsack_BFS()
{
/*
•	NA : l’ensemble des nœuds actifs, initialement vide.
•	nac : le nœud actif actuel.
•	bestZ : la meilleure valeur de la fonction objective actuellement, initialement nulle.
•	MSA : liste de nombre d’objets de la meilleure solution actuelle, initialement vide.
•	VR : Volume restant à remplir dans le sac, initialement le poids du sac à dos.
*/
    ofstream trace;
    trace.open("/home/koopa/trace.txt");
    node nac;
    node nf;
    int bestZ=0;
    list<int> MSA,L,temp;
    int VR=volumeSac;
    int i=0;
    int b;


    time_t t;

    t=clock();

    // Branch & Bound
    nac=creer_noeud(L,0,0);
    nac.obj_dad=0;

    //cout << "\n Noeud initial";
    //nac.print_node();
    NA=ajouter_noeud(nac);
    //cout << "\n Noeuds actifs number = " << NA.size();
    int nb=0;
    int elag=0;

    while(!NA.empty())
    {
        nb++;
        cout << "\n ******** NA non vide, iteration " << nb;
        nac=recup_noeud();
        //nac.print_node();
        //getchar();
        //cout << "\n Nombre de noeuds restant en pile" << NA.size();

                                        /*** Séparation ***/
        i=nac.L.size();
        //cout << "\n Niveau actuel = i=" << i;
        VR=volumeSac-nac.volumeCons;
        //cout << "\n Volume restant dans le sac " << VR;
        b=VR/MVB[0][i];
        cout << "\n Max elements de Xi possibles; b=" << b;

        for(int j=b;j>=0;j--)
        {
            temp=nac.L;
            //Insertion du fils
            temp.push_back(j);// Insérer à la ième position
            //cout << "Insertion en arriere de " << temp.back();
            nf=creer_noeud(temp,0,nac.volumeCons+j*MVB[0][i]);
            //nf.print_node();
            //getchar();

                        /***  Evaluation ***/
            nf.obj_dad=fct_obj(nac.obj_dad,i,j);
            cout << "\n fct objective =  " << nf.obj_dad;
            nf.eval=nf.obj_dad + evaluation(i,volumeSac-nf.volumeCons);
            cout << "\n evaluation =  " << nf.eval;
            //getchar();

            if(nf.eval>bestZ)
            {
                //cout << "\n meilleure evaluation " << nf.eval << " > " << bestZ;

                // On vérifie si c'est une solution exacte
                if(volumeSac-nf.volumeCons<min_volume) // On ne peut plus rien ajouter --> c'est une solution exacte
                {
                    bestZ=nf.obj_dad;
                    cout << "\n solution exacte et meilleure courante " << bestZ;
                    //getchar();
                    //getchar();
                    MSA=nf.L; /// Solution exacte
                }

                else if(i+1<N) // Ce n'est pas une solution ni une feuille
                {
                    ajouter_noeud(nf); // Mettre en pile
                }
            }
            else
            {
                cout << "\n Elagage "; elag++; //getchar();
            }
        }
        //cout << "\n Nombre de noeuds actif restants " << NA.size();

    }
    cout << "\n Largeur d'abord\n";
    trace << "\n Largeur d'abord\n";

    cout <<"\n Bénéfice maximal : " << bestZ;
    trace <<"\n Bénéfice maximal : " << bestZ << endl;

    cout << "\n Execution Time = " << clock()-t << " ms";
    trace << "\n Execution Time = " << clock()-t << " ms" << endl;

    cout << "\n Nombre d'élagages = " << elag;
    trace << "\n Nombre d'élagages = " << elag << endl;

    cout << "\n Meilleur objet = X" << order[0];
    trace << "\n Meilleur mobjet = X" << order[0] << endl;

}


void knapsack_BE()
{
/*
•	NA : l’ensemble des nœuds actifs, initialement vide.
•	nac : le nœud actif actuel.
•	bestZ : la meilleure valeur de la fonction objective actuellement, initialement nulle.
•	MSA : liste de nombre d’objets de la meilleure solution actuelle, initialement vide.
•	VR : Volume restant à remplir dans le sac, initialement le poids du sac à dos.
*/
    ofstream trace;
    trace.open("/home/koopa/trace.txt");
    node nac;
    node nf;
    int bestZ=0;
    list<int> MSA,L,temp;
    int VR=volumeSac;
    int i=0;
    int b;

    time_t t;

    t=clock();

    // Branch & Bound
    nac=creer_noeud(L,0,0);
    nac.obj_dad=0;

    //cout << "\n Noeud initial";
    //nac.print_node();
    NA=ajouter_noeud(nac);
    //cout << "\n Noeuds actifs number = " << NA.size();
    int nb=0;
    int elag=0;

    while(!NA.empty())
    {
        nb++;
        cout << "\n ******** NA non vide, iteration " << nb;
        nac=recup_noeud();
        //nac.print_node();
        //getchar();
        //cout << "\n Nombre de noeuds restant en pile" << NA.size();

                                        /*** Séparation ***/
        i=nac.L.size();
        //cout << "\n Niveau actuel = i=" << i;
        VR=volumeSac-nac.volumeCons;
        //cout << "\n Volume restant dans le sac " << VR;
        b=VR/MVB[0][i];
        cout << "\n Max elements de Xi possibles; b=" << b;

        for(int j=b;j>=0;j++)
        {
            temp=nac.L;
            //Insertion du fils
            temp.push_back(j);// Insérer à la ième position
            //cout << "Insertion en arriere de " << temp.back();

            nf=creer_noeud(temp,0,nac.volumeCons+j*MVB[0][i]);
            //nf.print_node();
            //getchar();

                        /***  Evaluation ***/
            nf.obj_dad=fct_obj(nac.obj_dad,i,j);
            cout << "\n fct objective =  " << nf.obj_dad;
            nf.eval=nf.obj_dad + evaluation(i,volumeSac-nf.volumeCons);
            cout << "\n evaluation =  " << nf.eval;
            //getchar();

            if(nf.eval>bestZ)
            {
                //cout << "\n meilleure evaluation " << nf.eval << " > " << bestZ;

                // On vérifie si c'est une solution exacte
                if(volumeSac-nf.volumeCons<min_volume) // On ne peut plus rien ajouter --> c'est une solution exacte
                {
                    bestZ=nf.obj_dad;
                    cout << "\n solution exacte et meilleure courante " << bestZ;
                    //getchar();
                    //getchar();
                    MSA=nf.L; /// Solution exacte
                }

                else if(i+1<N) // Ce n'est pas une solution ni une feuille
                {
                    ajouter_noeud(nf); // Mettre en pile
                }
            }
            else
            {
                cout << "\n Elagage "; elag++; //getchar();
            }
        }
        //cout << "\n Nombre de noeuds actif restants " << NA.size();

    }

    cout <<"\n Bénéfice maximal : " << bestZ;
    trace <<"\n Bénéfice maximal : " << bestZ << endl;

    cout << "\n Execution Time = " << clock()-t << " ms";
    trace << "\n Execution Time = " << clock()-t << " ms" << endl;

    cout << "\n Nombre d'élagages = " << elag;
    trace << "\n Nombre d'élagages = " << elag << endl;

    cout << "\n Meilleur objet = X" << order[0];
    trace << "\n Meilleur mobjet = X" << order[0] << endl;

}

void resolution(int method)
{
    switch(method)
    {
    case 0:
        {
            knapsack_BT();
            break;
        }
    case 1:
        {
            LM_Branch();
            break;
        }
    case 2:
        {
            knapsack_BFS();
            break;
        }
    case 3:
        {
        knapsack_BE();
            break;
        }
    }
}


