#ifndef VISITEUR_H
#define VISITEUR_H

#include "cursus.h"
#include "UTProfiler.h"

class formation;
class UV;
class UVManager;
class cursusManager;


class visiteur
{
    QString nom;
    QStringList list;
    UV** tab;
    int taille;

public:
    visiteur(const QString& n, const QStringList& l): nom(n), list(l), tab(0), taille(list.length()) {}
    void visitUVmanager();
    void visitCursusManager(cursusManager* cman);
};


#endif // VISITEUR_H
