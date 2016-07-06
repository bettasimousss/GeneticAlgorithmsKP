
#include <iostream>
#include <list>
#include <stack>
using namespace std;

class node {

    public:
    list<int> L;
    double eval;
    int volumeCons;
    int obj_dad;

    node()
    {

    }

    ~node()
    {

    }

    node(list<int> l,double e, int vc){
        L=l;
        eval=e;
        volumeCons=vc;
    }

    void print_node()
    {
        cout << "\n Evaluation=" << eval << "  Volume consomme=" << volumeCons << " fct_obj=" << obj_dad <<"\n";
        for(list<int>::iterator it=L.begin();it!=L.end();it++)
        {
            cout << (*it) <<"-";
        }
    }

    int dernier()
    {
        return L.back();
    }

};

