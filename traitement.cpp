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
#include <stdio.h>
#include <string.h>
#include <list>
#include <cstring>
#include "traitement.h"
using namespace std;

 // donnee du probleme
 int nbobj_traitement;
 int **MVB_traitement;
 int *ordre_traitement;
 int volumeSac_traitement;
 int min_volume_traitement;

 // donnee de tabu search
 vector<mouvement> tabu_list;
 int maxsize_tabulist;
 //int nbiter=1000;



 //** intialisation ^^ ***//
 solution init_solution(solution s){
     for (int i=0;i<nbobj_traitement;i++){
         s.chromosome[i]=0;
     }
     s.eval=0;
     s.volumeCons=0;
     return s;
 }
 mouvement init_mov(mouvement mov){
     mouvement m;
     mov.i=-1;
     mov.inb=-1;
     mov.j=-1;
     mov.jnb=-1;
     return mov;
 }
 movSol init_movsol(movSol m){
     m.s=init_solution(m.s);
     m.mov=init_mov(m.mov);
     return m;
 }

 // * Affichage***//
 void print_solution(solution s){
     cout<<endl<<endl;
     for (int i=0;i<nbobj_traitement;i++){
        // if (s.chromosome[i]!=0)
        //cout << " indice: "<<i<<" -> "<< s.chromosome[i];
         cout << "  "<< s.chromosome[i];
    }
     cout.setf(ios::fixed);
    //cout << setprecision(0)<<s.eval;
    cout <<fixed<<"   eval  " <<s.eval<<"  volcon  "<< s.volumeCons;
    ofstream tabu,tabu2;
    tabu.open("/home/koopa/tabu.txt");
    tabu2.open("/home/koopa/tabu2.txt");

    tabu<<fixed<<s.eval<<endl<<s.volumeCons<<endl;
    int zz=0,w=0;
//    //fen->setTableauGen(0,0,1);
//    Result_Tabou *fen = new Result_Tabou();
//    fen->majtab(50);

    while(zz<nbobj_traitement)
    {
        if (s.chromosome[zz] != 0)
        {
            tabu<<zz<<endl;
            tabu<<s.chromosome[zz]<<endl;
//            fen->setTableauGen(w,0,zz);
//            fen->setTableauGen(w,1,population_act.at(0).chromosome[zz]);
w++;
        }
        zz++;
    }
    tabu2<<w-1<<endl;
tabu2.close();
    tabu.close();



 }

 // fonction qui génére un voisin ( changement élémentaire)
 solution mutation_exchange(solution s,int i, int j)
{
    //cout << "add " << pos << endl;
    //cout << "sous " << pos2 << endl;
    solution res;
    init_solution(res);
    res	=s;
    res.chromosome[i]++;
    res.eval+=MVB_traitement[1][i];
    res.volumeCons+=MVB_traitement[0][i];

    if(res.chromosome[j]>0){
        res.chromosome[j]--;
        res.eval-=MVB_traitement[1][j];
        res.volumeCons-=MVB_traitement[0][j];
    }
    //print_solution(res);
    return res;
}

// ******génération du voisinage*****//
movSol best_neighbor(movSol e, int maxIt)// si aucune amélioaration e est retourner
{
    int pos1=0,pos2=0; // les mouvements a effectués sur l'objet d'indice pos1 et pos2
    int i=0; // pour le calcul du nombre d'itération

    solution  neighbor; // la solution mutée <==> voisin potentiel

    movSol neighbor_element; // le meilleure voisin de s + le mouvement effectué

    mouvement mov; // afin de pouvoir vérifier si le mouvement a effectuer est tabou ou non

    //** initialisation **//
    neighbor=init_solution(neighbor);
    neighbor_element=init_movsol(neighbor_element);
    //mov= init_mov(mov);
    mov.i=-1;
    mov.inb=-1;
    mov.j=-1;
    mov.jnb=-1;
    //mov=init_mov(mov);

    neighbor_element=e;

    while ((i< maxIt) && (pos1<nbobj_traitement-1)){
        pos2=pos1+1;
        while ((i< maxIt) && (pos2<nbobj_traitement)){ // on génere deux voisins dans une boucle +pos1 - pos2 ensuite -pos1 +pos2 ( le nombre d'objets)

            neighbor=mutation_exchange(e.s,pos1,pos2); // générer le 1 er voisin
            //cout << "pos1: "<<pos1<< " pos2: "<<pos2<<" neighbor : "; print_solution(neighbor); cout<<endl;
            mov.i=pos1;
            mov.inb=e.s.chromosome[pos1];
            mov.j=pos2;
            mov.jnb=e.s.chromosome[pos2];

            i++;

            if (!isTabu(mov) && neighbor.eval > neighbor_element.s.eval && neighbor.volumeCons<=volumeSac_traitement) // s'il n'est pas tabou et s'il améliore la solution courante en respectant la contrainte du poids
            {
                neighbor_element.mov=mov;
                neighbor_element.s=neighbor;
            }

            neighbor=mutation_exchange(e.s,pos2,pos1); // générer le 2 eme voisin
            //cout << "pos2: "<<pos2<< " pos1: "<<pos1<<" neighbor : "; print_solution(neighbor); cout<<endl;
            mov.i=pos2;
            mov.inb=e.s.chromosome[pos2];
            mov.j=pos1;
            mov.jnb=e.s.chromosome[pos1];

                i++;

            if ( !isTabu(mov) &&  neighbor.eval > neighbor_element.s.eval && neighbor.volumeCons<=volumeSac_traitement) // s'il n'est pas tabou et s'il améliore la solution courante en respectant la contrainte du poids
            {
                neighbor_element.mov=mov;
                neighbor_element.s=neighbor;
            }
            pos2++;
        }
        pos1++;
    }

    return neighbor_element;

} // si aucune amélioaration e est retourner
movSol first_improve_neighbor(movSol e, int maxIt)// si aucune amélioaration e est retourner
{
    int pos1=0,pos2=0;
    int i=0;
    bool found=false;

    solution neighbor;
    movSol element;
    mouvement mov;


    // *** initialisation *** //
    neighbor=init_solution(neighbor);
    element=init_movsol(element);
    mov.i=-1;
    mov.inb=-1;
    mov.j=-1;
    mov.jnb=-1;

    element=e;



    while ((!found) && (i< maxIt) && (pos1<nbobj_traitement-1)){
        pos2=pos1+1;
        while ((!found) && (i< maxIt) && (pos2<nbobj_traitement)){ // on génere deux voisins dans une boucle
            neighbor=mutation_exchange(e.s,pos1,pos2);
            //cout << "pos1: "<<pos1<< " pos2: "<<pos2<<" neighbor : "; print_solution(neighbor); cout<<endl;
            mov.i=pos1;
            mov.inb=e.s.chromosome[pos1];
            mov.j=pos2;
            mov.jnb=e.s.chromosome[pos2];

            i++;
            //cout<<endl<< " ___________________"; print_solution(neighbor);cout<<endl;;
            if ( !isTabu(mov) && neighbor.eval > e.s.eval && neighbor.volumeCons<=volumeSac_traitement )
            {
                found =true;
                element.mov=mov;
                element.s=neighbor;
            }
            else
            {
                neighbor=mutation_exchange(e.s,pos2,pos1);
                //cout << "pos2: "<<pos2<< " pos1: "<<pos1<<" neighbor : "; print_solution(neighbor); cout<<endl;
                mov.i=pos2;
                mov.inb=e.s.chromosome[pos2];
                mov.j=pos1;
                mov.jnb=e.s.chromosome[pos1];

                i++;
                if (!isTabu(mov) && neighbor.eval >e.s.eval && neighbor.volumeCons<=volumeSac_traitement )
                {
                    found =true;
                    element.mov=mov;
                    element.s=neighbor;
                }
                else {
                    pos2++;
                }
            }
        }
        pos1++;
    }

    return element;
}
movSol random_neighbor(movSol e,int maxIt) // peut boucler pour un long moment :/
{
    int pos1,pos2;
    int i=0;
    movSol element;

    element.s=init_solution(element.s);
    do{
        pos1=bounded_random_traitement(0, nbobj_traitement);
        pos2=bounded_random_traitement(0, nbobj_traitement);
        while (pos1 == pos2){ // garantir que pos1 soit diff de pos2
            pos2=bounded_random_traitement(0, nbobj_traitement);
        }

        //cout << " *first pos = "<<pos1 << " second pos= " << pos2 <<endl;
        element.mov.i=pos1;
        element.mov.inb=e.s.chromosome[pos1];
        element.mov.j=pos2;
        element.mov.jnb=e.s.chromosome[pos2];
        element.s=mutation_exchange(e.s,pos1,pos2);
        i++;
    }
    while( (element.s.volumeCons > volumeSac_traitement || isTabu(element.mov))  &&  i < maxIt); // on ne retourne que des voisins qui ne sont pas tabou et qui ont un volume <= au volume du sac
    // la verification " si l'elemnt est tabu" peut boucler infiniment ...
    //print_solution(element.s);
    return element;
}

/***** Comparaison*****/
bool compareMouvement(mouvement m1,mouvement m2){
    if ((m1.i == m2.i && m1.inb== m2.inb && m1.j==m2.j && m1.jnb ==m2.jnb)) return true;
        //||(m1.i == m2.j && m1.inb== m2.jnb && m1.j==m2.i && m1.jnb ==m2.inb)) return true;
    return false;
}
bool compareSolution(solution s1,solution s2){
    int i=0;
    while (i <nbobj_traitement){
        if (s1.chromosome[i] != s2.chromosome[i]) return false;
        i++;
    }
    return true;
}
bool isTabu (mouvement m){
    for(int i=0;i< tabu_list.size();i++){
        if (compareMouvement(tabu_list.at(i),m)) return true;
    }
    return false;
}

// tabu Search
solution tabuSearchBest(solution s, int nbiterationv,int nbiter){
    cout<<"nbr iter "<< nbiter;

    solution sol_init, best_sol;
    movSol e;
    movSol neighbor_e;
    int i=0;
    bool stop=false;

    /**** initialisation***/
    e=init_movsol(e);
    sol_init=s;
    best_sol=s;
    e.s=sol_init;
    neighbor_e=e;

    cout <<endl<<endl<< " Debut tabu"<<endl <<endl;
    cout << "solution initiale: " ; print_solution(s);cout <<endl<<endl<<endl;;



    cout << "you have chosen to generate best neighbors "<<endl;
    while (i<nbiter && !stop){
        neighbor_e=best_neighbor(e,nbiterationv);
        i++;
        //cout << "neighbor: "<<i <<"="; print_solution(neighbor_e.s);cout <<endl;

        if (!compareSolution(neighbor_e.s,sol_init)){	// si le voisin est different de la solution initialement introduit
            best_sol=neighbor_e.s;
            if (isTabu(neighbor_e.mov)){ // s'ssurer que c'est un mouvement tabou ou non, can't happen, unless the neighbir_e == e ^_^, we check anyway
                cout<<endl;
                //cout << "l'element" ;print_solution(neighbor_e.s);cout <<" est un mouvement tabou"<<endl;
            }
            else{ // si le voisin n'est pas tabou, on l'ajoute a liste tabou en la mettant à jour
                tabu_list.push_back(neighbor_e.mov); // ajouter a liste tabou
                if (tabu_list.size() >maxsize_tabulist) // si la taille deborde
                    tabu_list.erase(tabu_list.begin()); //supprimer le plus ancien  element ( le premier dans la file

            }

        }
        else{ // le voisin généré est égale à la solution initiale <_<
            stop=true;
            cout << "on vient de généer la solution initilae"<<endl;
        }
        cout << "\t contenu Tabu a la "<<i<< " iteration:"<<endl;
        cout << "****" << "i" << " --" << "nbi"<< " --"<< "j" << " --" << "nbj" <<endl;
        for(int j=0;j<tabu_list.size();j++)
            cout << "--->" << tabu_list.at(j).i << " --" << tabu_list.at(j).inb << " --"<< tabu_list.at(j).j << " --" << tabu_list.at(j).jnb <<endl;
        cout <<endl <<endl;
        e=neighbor_e;
    }
    cout << " Fin  tabu avec best solution == "; print_solution(best_sol); cout<<endl <<endl;
    return best_sol;
}
solution tabuSearchFirst(solution s, int nbiterationv,int nbiter){

    cout<<"nbr iter "<< nbiter<<endl;
    solution sol_init, best_sol;
    movSol e;
    movSol neighbor_e;
    int i=0;
    bool stop=false;

    /**** initialisation***/
    e=init_movsol(e);
    sol_init=s;
    best_sol=s;
    e.s=sol_init;
    neighbor_e=e;

    cout <<endl<<endl<< " Debut tabu"<<endl <<endl;
    cout << "solution initiale: " ; print_solution(s);cout <<endl<<endl<<endl;;



    cout << "you have chosen to generate the first improve neighbors "<<endl;
    while (i<nbiter && !stop){
        //getchar();
        neighbor_e=first_improve_neighbor(e,nbiterationv);
        i++;
        //cout << "neighbor: "<<i <<"="; print_solution(neighbor_e.s);cout <<endl;

        if (!compareSolution(neighbor_e.s,sol_init)){	// si le voisin est different de la solution initialement introduit
            best_sol=neighbor_e.s;

            if (isTabu(neighbor_e.mov)){ // s'ssurer que c'est un mouvement tabou ou non, can't happen, unless the neighbir_e == e ^_^, we check anyway
                cout<<endl;
                //cout << "l'element" ;print_solution(neighbor_e.s);cout <<" est un mouvement tabou"<<endl;
            }
            else{ // si le voisin n'est pas tabou, on l'ajoute a liste tabou en la mettant à jour
                tabu_list.push_back(neighbor_e.mov); // ajouter a liste tabou
                if (tabu_list.size() >maxsize_tabulist) // si la taille deborde
                    tabu_list.erase(tabu_list.begin()); //supprimer le plus ancien  element ( le premier dans la file
            }

        }
        else{ // le voisin généré est égale à la solution initiale <_<
            stop=true;
            cout << "on vient de généer la solution initilae"<<endl;
        }
        cout << "\t contenu Tabu a la "<<i<< " iteration:"<<endl;
        cout << "****" << "i" << " --" << "nbi"<< " --"<< "j" << " --" << "nbj" <<endl;
        for(int j=0;j<tabu_list.size();j++)
            cout << "--->" << tabu_list.at(j).i << " --" << tabu_list.at(j).inb << " --"<< tabu_list.at(j).j << " --" << tabu_list.at(j).jnb <<endl;
        cout <<endl <<endl;
        e=neighbor_e;
    }
    cout << " Fin  tabu avec best solution == "; print_solution(best_sol); cout<<endl <<endl;
    return best_sol;
}
solution tabuSearchRandom(solution s,int nbiterationv,int nbiter){
    solution sol_init, best_sol;
    movSol e;
    movSol neighbor_e;
    int i=0;
    bool stop=false;

    /**** initialisation***/
    e=init_movsol(e);
    sol_init=s;
    best_sol=s;
    e.s=sol_init;
    neighbor_e=e;

    cout <<endl<<endl<< " Debut tabu"<<endl <<endl;
    cout << "solution initiale: " ; print_solution(s);cout <<endl<<endl<<endl;;



    cout << "you have chosen to generate random neighbors "<<endl;
    while (i<nbiter && !stop){

        neighbor_e=random_neighbor(e,nbiterationv);
        i++;
        //cout << "neighbor: "<<i <<"="; print_solution(neighbor_e.s);cout <<endl;

        if (!compareSolution(neighbor_e.s,sol_init)){	// si le voisin est different de la solution initialement introduit
            // we should check if this neighbor is better than previous neighbors and results
            if (neighbor_e.s.eval > best_sol.eval && neighbor_e.s.volumeCons<=volumeSac_traitement){
                best_sol=neighbor_e.s;
            }

            if (isTabu(neighbor_e.mov)){ // s'ssurer que c'est un mouvement tabou ou non, can't happen, unless the neighbir_e == e ^_^, we check anyway
                cout<<endl;
                //cout << "l'element" ;print_solution(neighbor_e.s);cout <<" est un mouvement tabou"<<endl;
            }
            else{ // si le voisin n'est pas tabou, on l'ajoute a liste tabou en la mettant à jour
                tabu_list.push_back(neighbor_e.mov); // ajouter a liste tabou
                if (tabu_list.size() >maxsize_tabulist) // si la taille deborde
                    tabu_list.erase(tabu_list.begin()); //supprimer le plus ancien  element ( le premier dans la file

            }

        }
        else{ // le voisin généré est égale à la solution initiale <_<
            stop=true;
            cout << "on vient de généer la solution initilae"<<endl;
        }
        cout << "\t contenu Tabu a la "<<i<< " iteration:"<<endl;
        cout << "****" << "i" << " --" << "nbi"<< " --"<< "j" << " --" << "nbj" <<endl;
        for(int j=0;j<tabu_list.size();j++)
            cout << "--->" << tabu_list.at(j).i << " --" << tabu_list.at(j).inb << " --"<< tabu_list.at(j).j << " --" << tabu_list.at(j).jnb <<endl;
        cout <<endl <<endl;
        e=neighbor_e;
    }
    cout << " Fin  tabu avec best solution == "; print_solution(best_sol); cout<<endl <<endl;
    return best_sol;
}
solution tabuSearch(solution s, char choix, int nbiterationv,int nbiter){

    solution sol_init=s; // pour faire la comparaison, et ne plus revenir à cette solution
    solution best_sol=s;
    movSol e;
    movSol neighbor_e;
    int i=0;
    bool stop=false;

    e=init_movsol(e);

    e.s=sol_init;
    neighbor_e=e;

    cout <<endl<<endl<< " Debut tabu"<<endl <<endl;
    cout << "solution initiale: " ; print_solution(s);cout <<endl<<endl<<endl;;
    switch (choix)
    {
        //********************** random neighbor********************//
        case 'r':
            break;

//_____________________________________________________________________________________________________________________________//
            //********************first improve**********************/

        case 'f':
            cout << "you have chosen ythe first improve neighbors "<<endl;
            while (i<nbiter && !stop){
                neighbor_e=first_improve_neighbor( e, nbiterationv);
                i++;
                cout << "neighbor: "<<i <<"="; print_solution(neighbor_e.s);cout <<endl;
                //cout << endl;

                if (!compareSolution(neighbor_e.s,sol_init)){
                        best_sol=neighbor_e.s;

                    if (isTabu(neighbor_e.mov)){ // il serai iintelligent d'arreter l'algorithme, si un element tabou a été trouvé <3
                        //stop =true;
                        cout<<endl;
                        cout << "l'element" ;print_solution(neighbor_e.s);cout <<" est un mouvement tabou"<<endl;
                    }
                    else{
                        tabu_list.push_back(neighbor_e.mov); // ajouter a liste tabou
                        if (tabu_list.size() >maxsize_tabulist)
                            tabu_list.erase(tabu_list.begin()); //supprimer le plus ancien  element ( le premier dans la file

                    }

                }
                else{ // le voisin généré est égale à la solution initiale <_<
                    stop=true;
                    cout << "on vient de généer la solution initilae"<<endl;
                }
                cout << "\t contenu Tabu a la "<<i<< " iteration:"<<endl;
                cout << "****" << "i" << " --" << "nbi"<< " --"<< "j" << " --" << "nbj" <<endl;
                for(int j=0;j<tabu_list.size();j++)
                    cout << "--->" << tabu_list.at(j).i << " --" << tabu_list.at(j).inb << " --"<< tabu_list.at(j).j << " --" << tabu_list.at(j).jnb <<endl;
                cout <<endl <<endl;
                e=neighbor_e;
    }
    cout << " Fin  tabu avec best solution == "; print_solution(best_sol); cout<<endl <<endl;
    return best_sol;
            break;

            /********************************  best neighbor************************/
        case 'b':
            cout << "you have chosen ythe best neighbors "<<endl;
            while (i<nbiter && !stop){
                neighbor_e=best_neighbor( e, nbiterationv);
                i++;
                cout << "neighbor: "<<i <<"="; print_solution(neighbor_e.s);cout <<endl;
                //cout << endl;

                if (!compareSolution(neighbor_e.s,sol_init)){
                        best_sol=neighbor_e.s;

                    if (isTabu(neighbor_e.mov)){
                        //stop =true;
                        cout<<endl;
                        cout << "l'element" ;print_solution(neighbor_e.s);cout <<" est un mouvement tabou"<<endl;
                    }
                    else{
                        tabu_list.push_back(neighbor_e.mov); // ajouter a liste tabou
                        if (tabu_list.size() >maxsize_tabulist)
                            tabu_list.erase(tabu_list.begin()); //supprimer le plus ancien  element ( le premier dans la file

                    }

                }
                else{ // le voisin généré est égale à la solution initiale <_<
                    stop=true;
                    cout << "on vient de généer la solution initilae"<<endl;
                }
                cout << "\t contenu Tabu a la "<<i<< " iteration:"<<endl;
                cout << "****" << "i" << " --" << "nbi"<< " --"<< "j" << " --" << "nbj" <<endl;
                for(int j=0;j<tabu_list.size();j++)
                    cout << "--->" << tabu_list.at(j).i << " --" << tabu_list.at(j).inb << " --"<< tabu_list.at(j).j << " --" << tabu_list.at(j).jnb <<endl;
                cout <<endl <<endl;
                e=neighbor_e;
    }
    cout << " Fin  tabu avec best solution == "; print_solution(best_sol); cout<<endl <<endl;
    return best_sol;
            break;
        default:
            break;
    }


}



/**** Génération de nombres aléatoires ***/
int random_number_traitement()
{
    return rand();
}

int bounded_random_traitement(int min, int max)
{
    return rand()%(max-min) + min;
}

float random_01_traitement()
{
    return (float) (rand()%10000) / 10000;
}


/*********** initialiser les données du problemes **************/
void tri_tableau_traitement()
{
    int saveTaille=nbobj_traitement;
    int save0,save1,save2;
    bool permutation=false;
    // Tri
    cout << "\n Va trier" << nbobj_traitement << "  " << volumeSac_traitement << " " << min_volume_traitement;

    do
    {
        permutation=false;
        for(int i=0;i<saveTaille-1;i++){

            if((double)MVB_traitement[1][i]/(double)MVB_traitement[0][i] < (double)MVB_traitement[1][i+1]/(double)MVB_traitement[0][i+1])
            {
                permutation=true;
                save0=MVB_traitement[0][i+1];
                MVB_traitement[0][i+1]=MVB_traitement[0][i];
                MVB_traitement[0][i]=save0;

                save1=MVB_traitement[1][i+1];
                MVB_traitement[1][i+1]=MVB_traitement[1][i];
                MVB_traitement[1][i]=save1;

                save2=ordre_traitement[i+1];
                ordre_traitement[i+1]=ordre_traitement[i];
                ordre_traitement[i]=save2;

                //cout << "si si je trie";
            }
        }
        saveTaille--;

    } while (permutation);


}


void init_tableau_traitement(char* filename)
{
    //Récupère les données à partir du benchmark
    recup_data_traitement(filename);
}


/***** Récupération des données à partir du fichier benchmark *****/
std::vector<std::string> &split_traitement(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split_traitement(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split_traitement(s, delim, elems);
    return elems;
}
void recup_data_traitement(char* filepath)
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
            nbobj_traitement=atoi(row);
            //cout << nbobj_traitement;
            file.getline(row,512,'\n');
            //cout << row;
            volumeSac_traitement=atoi(row);
            //cout << volumeSac_traitement;
            file.getline(row,512,'\n');
            //cout << row
            min_volume_traitement=atoi(row);
            //cout << min_volume_traitement;

            MVB_traitement=new int*[2];
            MVB_traitement[0]=new int[nbobj_traitement];
            MVB_traitement[1]=new int[nbobj_traitement];
            ordre_traitement=new int[nbobj_traitement];

            for(int z=0;z<nbobj_traitement; z++) ordre_traitement[z]=z;

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
                tokens=split_traitement(phrase,'\t');
                //cout << "\n" << atoi(tokens[0].c_str()) << "  " << atoi(tokens[1].c_str());
                tmp=atoi(tokens[0].c_str());
                if(tmp<min_volume_traitement) min_volume_traitement=tmp;
                MVB_traitement[0][i]=tmp;
                MVB_traitement[1][i]=atoi(tokens[1].c_str());
                if(MVB_traitement[1][i]==0)
                {
                    //cout << "\n ici";
                    MVB_traitement[1][i]=atoi(tokens[2].c_str());
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

//****** generer une solution initiale du probele ******/

solution LM_Branch_traitement(solution n)
{
    int VR=volumeSac_traitement;
    list<int> L;
    int obj=0;
    int j=0;
    int b=0;
    //solution n;

    time_t t=clock();

    while(VR>min_volume_traitement)
    {
        b=VR/MVB_traitement[0][j];
        n.chromosome[j]=b;
        obj+=b*MVB_traitement[1][j];
        VR-=b*MVB_traitement[0][j];
        j++;
    }

    n.eval=obj;
    n.volumeCons=volumeSac_traitement-VR;

    print_solution(n);
    return n;
}

