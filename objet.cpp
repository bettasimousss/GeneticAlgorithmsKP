#include "objet.h"
#include <istream>


Objet::Objet()
{
}

Objet::Objet(int volume, int benefice)
{
    this->volume=volume;
    this->benefice=benefice;
}

int Objet::getBenefice(){
    return this->benefice;
}

int Objet::getVolume(){
    return this->volume;
}

