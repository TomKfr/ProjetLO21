#include "visiteur.h"
#include "UTProfiler.h"
#include "cursus.h"


void visiteur::visitUVmanager()
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

void visiteur::visitCursusManager(cursusManager* cman)
{
    //retrouver la formation qui vient d'être créée dans le cursus manager.
    formation* fr=cman->trouverForm(nom);
    for(int i=0;i<taille;i++)
    {
        fr->ajouter_UV(tab[i]);
    }
}

