#ifndef VISITEUR2_H
#define VISITEUR2_H

#include "dossier.h"
#include "UTProfiler.h"

class Dossier;
class UV;
class UVManager;
class DossierManager;

class visiteur2
{
    unsigned int num;
    QStringList list;
    UV** tab;
    int taille;

public:
    visiteur2(unsigned int n, const QStringList& l): num(n), list(l), tab(0), taille(list.length()) {}
    void visitUVmanager();
    void visitDossierManager(DossierManager* man);
};

#endif // VISITEUR2_H
