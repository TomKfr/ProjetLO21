#ifndef ITERATEUR_H
#define ITERATEUR_H

#include "exception.h"

template<class I> class iterateur
{
    I** tab;
    unsigned int nbtot;
    unsigned int current;
public:
    iterateur(I** t, unsigned int n) : tab(t), nbtot(n), current(0) {}
    bool isDone() {return current==nbtot;}
    void next()
    {
        if(isDone()) throw UTProfilerException("Next sur un itérateur terminé !!");
        current++;
    }
    I* courant() {return tab[current];}
};


#endif // ITERATEUR_H
