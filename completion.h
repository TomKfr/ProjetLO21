#ifndef COMPLETION_H
#define COMPLETION_H
#include"UTProfiler.h"

#include <QSet>

class Dossier;
enum Reponse {Valider, Refuser,Avancer, Retarder};

class ChoixAppliSemestre {//proposition pour 1 semestre donne par l'application

    QMap<QString,UV*> propositionUV;
    Semestre semestre_concerne;
    unsigned int nbCredits ; //nb de credits accumules avec ce semestre : pas plus de 35
    unsigned int nbUV ; //pas plus de 7

    Dossier* dos; //dossier concerne

public :
    ChoixAppliSemestre (unsigned int annee=0, Saison s=Automne, Dossier*d=0,  unsigned int cr=0 ,unsigned int nbuv=0) : semestre_concerne(Semestre(s,annee)), nbCredits(cr), nbUV(nbuv), dos(d) {}

    QMap<QString,UV*> getPropositionUV() const {return propositionUV;}
    Semestre getSemestre() const {return semestre_concerne;}
    unsigned int getNbCredits() const {return nbCredits;}
    unsigned int getNbUV() const {return nbUV;}

    void ajoutUV(UV* uv);
    void supprimerUV(UV* uv);

    void calculerProposition();//A DEFINIR

};

class ChoixAppli { //regroupe tous les semestres proposes jusqu'à la fin des etudes


    ChoixAppliSemestre** listePropositions;
    unsigned int nbSemestre;
    unsigned int nbMaxSemestre ;
    Dossier * dossier;
    Reponse rep; //reponse donnee par l'etudiant

public :
        ChoixAppli(Dossier* d) : dossier(d), listePropositions(0), nbSemestre(0), nbMaxSemestre(0) {}
        Reponse getReponse() const {return rep;}
        ChoixAppliSemestre** getListePropositions() const {return listePropositions;}
        void setReponse(Reponse r) {rep=r;}
        ChoixAppliSemestre* trouverChoix(Semestre S) ;

        void ajouter_proposition(ChoixAppliSemestre * prop); //une methode de suppression est-elle nécessaire ? je ne pense pas ..

};

class souhaits
{
    friend class DossierManager;

    Dossier *dos;
    QSet<QString> exigences;
    QSet<QString> preferences;
    QSet<QString> rejets;

public:
    souhaits(Dossier* d, QSet<QString>& e, QSet<QString>& p, QSet<QString>& r): dos(d), exigences(e), preferences(p), rejets(r) {}
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
