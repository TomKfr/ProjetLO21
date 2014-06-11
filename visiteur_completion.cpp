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
    //aller dans l'uv manager pour récupérer un tableau de pointeurs d'uvs correspondant à l'attribut stringlist
    UVManager& uman=UVManager::getInstance();
    tab = new UV*[taille];
    qDebug()<<taille;//OK

    for(int i=0;i<taille;i++)
    {
        qDebug()<<"dans le visiteur";
        qDebug()<<list.first();
        UV& newuv=uman.getUV(list.first());
        qDebug()<<"coucou"; // NE VA PAS ICI
        tab[i]=&newuv;
        list.removeFirst();

    }

    qDebug()<<"fin de visitUVManager";
}

/*!
 * \brief Visite le DossierManager pour ajouter les solutions de complétion aux dossiers.
 * \param d pointeur vers le Dossier concerné
 */
void visiteurCompletion::visitDossierManager(Dossier* d)
{
    //retrouver la completion qui vient detre creee dans le dossier
    qDebug()<<"visitdossierManager pour chargement completions";

    qDebug()<<dossier; //NUL
    qDebug()<<"completion trouvée1";
    qDebug()<<taille;
    for(int i=0;i<taille;i++)
    {
        qDebug()<<"completionTrouvee2";
        choix->ajoutUV(tab[i]);
         qDebug()<<"completionTrouvée3";

    }
    qDebug()<<"Completions récupérées !";
}


