#ifndef ITERATEUR_H
#define ITERATEUR_H

#include "exception.h"

/*!
 * \brief Template permettant de parcourir un ensemble d'objets dont le type est passé en paramètre.
 *
 * La structure à parcourir doit être un tableau de pointeurs vers les objets sur lesquels on itère.
 * Le constructeur nécessite donc ce pointeur (I**) et la taille de la * structure,
 *  le nombre d'objets stockés.
 */
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
