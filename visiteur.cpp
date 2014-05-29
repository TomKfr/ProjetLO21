#include "visiteur.h"
#include "UTProfiler.h"
#include "cursus.h"

void visiteur::visitUVmanager()
{
    //aller dans l'uv manager pour récupérer un tableau de pointeurs d'uvs correspondant à l'attribut stringlist
    UVManager& uman=UVManager::getInstance();
    for(QMap<QString,bool>::iterator it=list.begin();it!=list.end();it++)
    {
        UV& newuv=uman.getUV(it.key());
        listuvs.insert(newuv.getCode(),&newuv);
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
            if(list.find(it.key()).value()) form->ajt_UV_obligatoire(it.key());
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

