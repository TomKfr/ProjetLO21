#ifndef COMPLETION_H
#define COMPLETION_H
#include"UTProfiler.h"

#include <QSet>

class Dossier;
enum Reponse {Valide, Refuse,Avance, Retarde};

class ChoixAppliSemestre {//proposition pour 1 semestre donne par l'application

    QMap<QString,UV*> propositionUV;
    Semestre semestre_concerne;
    unsigned int nbCredits ; //nb de credits accumules avec ce semestre : pas plus de 35
    unsigned int nbUV ; //pas plus de 7
    Reponse rep; //reponse donnee par l'etudiant

public :
    ChoixAppliSemestre ( unsigned int annee, Saison s, unsigned int cr=0 ,unsigned int nbuv=0) : semestre_concerne(Semestre(s,annee)), nbCredits(cr), nbUV(nbuv) {}
    //ajout d'une uv dans la proposition, ...
};

class ChoixAppli { //regroupe tous les semestres proposes jusqu'à la fin des etudes

    ChoixAppliSemestre** tab_propositions; //tableau des propositions
    unsigned int nbPropositions;

public :
        ChoixAppli();
        void ajouter_proposition();

};

class souhaits
{
    Dossier *dos;
    QSet<QString> exigences;
    QSet<QString> preferences;
    QSet<QString> rejets;

public:
    souhaits() {}
    void Ajt_exigence(const QString& code);
    void Ajt_preference(const QString& code);
    void Ajt_rejet(const QString& code);
    void Suppr_exigence(const QString& code);
    void Suppr_prefernce(const QString& code);
    void Suppr_rejet(const QString& code);
    bool estExigee(const QString& code) const {return exigences.contains(code);}
    bool estPreferee(const QString& code) const {return preferences.contains(code);}
    bool estRejetee(const QString& code) const {return rejets.contains(code);}

    void save();
    void load();
};

#endif // COMPLETION_H
