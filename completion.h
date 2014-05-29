#ifndef COMPLETION_H
#define COMPLETION_H
#include"UTProfiler.h"

enum Reponse {Valide, Refuse,Avance, Retarde};

class ChoixAppliSemestre {//proposition pour 1 semestre donne par l'application

    QMap<QString,UV*> propositionUV;
    Semestre semestre_concerne;
    unsigned int nbCredits ; //nb de credits accumules avec ce semestre : pas plus de 35
    unsigned int nbUV ; //pas plus de 7
    Reponse rep; //reponse donnee par l'etudiant

public :
    ChoixAppliSemestre ( unsigned int annee, Saison s, unsigned int cr=0 ,unsigned int nbuv=0) : Semestre(annee, s), nbCredits(cr), nbUV(nbuv) {}
    //ajout d'une uv dans la proposition, ...
};

class ChoixAppli { //regroupe tous les semestres proposes jusqu'à la fin des etudes

    ChoixAppliSemestre** tab_propositions; //tableau des propositions
    unsigned int nbPropositions;

public :
        ChoixAppli();
        void ajouter_proposition();

    }

#endif // COMPLETION_H
