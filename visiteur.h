#ifndef VISITEUR_H
#define VISITEUR_H

#include "cursus.h"
#include "UTProfiler.h"
#include "visiteur.h"

class formation;
class UV;
class UVManager;

class visiteur
{
    QStringList list;
    UV** tab;

public:
    visiteur(const QStringList& l): list(l), tab(0) {}
    void visitUVmanager(UVManager* uman);
    void visitFormation(formation* f);
};

#endif // VISITEUR_H
