#ifndef OBJET_H
#define OBJET_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include "QObject"
class Objet:public QObject
{
public:
    explicit Objet();
    explicit Objet(int, int);
    int getVolume();
    int getBenefice();
private:
int benefice;
int volume;
};

#endif // OBJET_H
