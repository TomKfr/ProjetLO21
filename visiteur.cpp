#include "visiteur.h"
#include "UTProfiler.h"
#include "cursus.h"


void visiteur::visitUVmanager(UVManager *uman)
{
    //aller dans l'uv manager pour récupérer un tableau de pointeurs d'uvs correspondant à l'attribut stringlist
    tab = new UV*[list.length()];
}

void visiteur::visitFormation(formation *f)
{
    //aller dans la formation qie vient d'être créée pour lui passer le tableau d'uvs.
}
