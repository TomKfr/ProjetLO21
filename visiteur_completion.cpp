/*!
 *  \file visiteur_completion.cpp
 *  \brief Fichier contenant la définition des méthodes du visiteur utilisé lors de la complétion.
 */

#include "visiteur_completion.h"
#include "UTProfiler.h"
#include "dossier.h"


class Dossier;

/*!
 * \brief Visite l'UVManager pour retrouver les pointeurs d'UVs correspondants à la liste stockéen en attribut.
 */
void visiteurCompletion::visitUVmanager()
{
    UVManager& uman=UVManager::getInstance();
    tab = new UV*[taille];
    qDebug()<<taille;//OK

    for(int i=0;i<taille;i++)
    {
        UV& newuv=uman.getUV(list.first());
        tab[i]=&newuv;
        list.removeFirst();

    }
}

/*!
 * \brief Visite le DossierManager pour ajouter les solutions de complétion aux dossiers.
 * \param d pointeur vers le Dossier concerné
 */
void visiteurCompletion::visitDossierManager(Dossier* d)
{
    for(int i=0;i<taille;i++)
    {
        choix->ajoutUV(tab[i]);
    }
}


