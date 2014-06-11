/*!
 *  \file visiteur2.cpp
 *  \brief Fichier contenant la définition des méthodes du second visiteur.
 */

#include "visiteur2.h"
#include "UTProfiler.h"
#include "dossier.h"


class Dossier;

/*!
 * \brief Visite l'UVManager pour retrouver les pointeurs d'UVs correspondants à la liste stockéen en attribut.
 */
void visiteur2::visitUVmanager()
{
    //aller dans l'uv manager pour récupérer un tableau de pointeurs d'uvs correspondant à l'attribut stringlist
    UVManager& uman=UVManager::getInstance();
    tab = new UV*[taille];
    qDebug()<<taille;//OK

    for(int i=0;i<taille;i++)
    {
        qDebug()<<"dans le visiteur";
        qDebug()<<tabRes[i];
        qDebug()<<list.first();
        UV& newuv=uman.getUV(list.first());
        qDebug()<<"coucou"; // NE VA PAS ICI
        tab[i]=&newuv;
        list.removeFirst();

    }

    qDebug()<<"fin de visitUVManager";
}
/*!
 * \brief Visite le cursusManager pour ajouter les UVs aux dossiers.
 * \param man pointeur vers le DossierManager
 */
void visiteur2::visitDossierManager(DossierManager* man)
{
    //retrouver le dossier qui vient d'être créée dans le dossier manager.
    qDebug()<<"visitdossierManager";
    Dossier* dos=man->trouverDossier(num);
    qDebug()<<dos; //NUL
    qDebug()<<num;
    qDebug()<<"dossier trouvé1";
    qDebug()<<taille;
    for(int i=0;i<taille;i++)
    {
        qDebug()<<"dossier trouve2";
        dos->ajouterUV(tab[i]->getCode(),String2Note(tabRes[i]));
        qDebug()<<"dossier trouvé4";
    }
    qDebug()<<"dossier trouvé2";
    qDebug()<<"UVs récupérées !";
}

