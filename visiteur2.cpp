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
    UVManager& uman=UVManager::getInstance();
    tab = new UV*[taille];

    for(int i=0;i<taille;i++)
    {

        UV& newuv=uman.getUV(list.first());
        tab[i]=&newuv;
        list.removeFirst();

    }
}
/*!
 * \brief Visite le cursusManager pour ajouter les UVs aux dossiers.
 * \param man pointeur vers le DossierManager
 */
void visiteur2::visitDossierManager(DossierManager* man)
{

    Dossier* dos=man->trouverDossier(num);

    for(int i=0;i<taille;i++)
    {
        dos->ajouterUV(tab[i]->getCode(),String2Note(tabRes[i]));
    }
}

