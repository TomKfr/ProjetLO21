#include "visiteur2.h"
#include "UTProfiler.h"
#include "dossier.h"


class Dossier;


void visiteur2::visitUVmanager()
{
    //aller dans l'uv manager pour récupérer un tableau de pointeurs d'uvs correspondant à l'attribut stringlist
    UVManager& uman=UVManager::getInstance();
    tab = new UV*[taille];
    for(int i=0;i<taille;i++)
    {
        UV& newuv=uman.getUV(list.first());
        tab[i]=&newuv;
        list.removeFirst();
    }
}

void visiteur2::visitDossierManager(DossierManager* man)
{
    //retrouver la formation qui vient d'être créée dans le cursus manager.
    Dossier* dos=man->trouverDossier(num);
    for(int i=0;i<taille;i++)
    {
        dos->ajouterUV(tab[i]);
    }
}

