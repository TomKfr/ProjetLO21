/*!
 *  \file visiteur2.h
 *  \brief Fichier contenant la déclaration du second visiteur.
 */


#ifndef VISITEUR2_H
#define VISITEUR2_H

#include<QDebug>

class Dossier;
class UV;
class UVManager;
class DossierManager;

/*!
 * \brief Classe implémentant le design pattern visiteur.
 */
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
            for (int i=0; i<taille; i++) {tabRes[i]=list2[i]; qDebug()<<tabRes[i]; }
    }
    void visitUVmanager();
    void visitDossierManager(DossierManager* man);
};

#endif // VISITEUR2_H
