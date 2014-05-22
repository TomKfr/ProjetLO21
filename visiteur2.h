#ifndef VISITEUR2_H
#define VISITEUR2_H

#include "dossier.h"
#include "UTProfiler.h"
#include<QDebug>

class Dossier;
class UV;
class UVManager;
class DossierManager;

class visiteur2
{
    unsigned int num;
    QStringList list;
    QStringList list2;
    UV** tab;
    QString* tabRes;
    int taille;

public:
    visiteur2(unsigned int n, const QStringList& l, const QStringList& l2): num(n), list(l), list2(l2),  tab(0), taille(list.length())
    {
            tabRes= new QString[taille];
            qDebug()<<"constructeur de visiteur2";
            for (int i=0; i<taille; i++) {tabRes[i]=list2[i]; qDebug()<<tabRes[i]; }
    }
    void visitUVmanager();
    void visitDossierManager(DossierManager* man);
};

#endif // VISITEUR2_H
