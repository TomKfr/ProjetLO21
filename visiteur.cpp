#include "visiteur.h"
#include "UTProfiler.h"
#include "cursus.h"

void visiteur::visitUVmanager()
{
    //aller dans l'uv manager pour récupérer un tableau de pointeurs d'uvs correspondant à l'attribut stringlist
    UVManager& uman=UVManager::getInstance();
    for(int i=0;i<taille;i++)
    {
        UV& newuv=uman.getUV(list.first());
        listuvs.insert(newuv.getCode(),&newuv);
        list.removeFirst();
    }
}

void visiteur::visitCursusManager(cursusManager* cman, QString c)
{
    //retrouver le cursus qui vient d'être créée dans le cursus manager.
    if(c=="form")
    {
        formation* form=cman->trouverForm(nom);
        for(QMap<QString,UV*>::iterator it=listuvs.begin();it!=listuvs.end();it++)
        {
            form->ajouter_UV(it.value());
        }
    }
    else
    {
        filiere* fil=cman->trouverFil(nom);
        for(QMap<QString,UV*>::iterator it=listuvs.begin();it!=listuvs.end();it++)
        {
            fil->ajouter_UV(it.value());
        }
    }
}

