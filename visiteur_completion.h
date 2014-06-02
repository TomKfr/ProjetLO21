#ifndef VISITEUR_COMPLETION_H
#define VISITEUR_COMPLETION_H
#include"completion.h"
#include<QDebug>

class Dossier;
class UV;
class UVManager;
class DossierManager;
class ChoixAppliSemestre;

class visiteurCompletion
{
    ChoixAppliSemestre * choix;
    QStringList list;
    UV** tab;
    int taille;
    Dossier * dossier;

public:
    visiteurCompletion(ChoixAppliSemestre * c, const QStringList& l, Dossier* dos): choix(c), list(l),  tab(0), taille(list.length()), dossier(dos) {}
    void visitUVmanager();
    void visitDossierManager(Dossier* d);
};


#endif // VISITEUR_COMPLETION_H
