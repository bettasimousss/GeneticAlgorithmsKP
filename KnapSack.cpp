#include <iostream>
#include "KnackSack.h"
#include <queue>
#include <vector>

using namespace std;



int main(int argc, char* argv[])
{
    generate_instance("save.txt",1000,130,250,120,450);
    init_tableau("save.txt");

    tri_tableau();

    knapsack();

    getchar();
    return 0;
}
