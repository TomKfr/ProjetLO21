#ifndef COMPLETION_H
#define COMPLETION_H
#include"UTProfiler.h"
#include"dossier.h"

#include <QSet>

class Dossier;
class ChoixAppli;
enum Reponse {Valider, Refuser,Avancer, Retarder};

class ChoixManager{
    ChoixAppli ** ensemblePropositions; //l'integralite des propositions de l'appli
    unsigned int nbPropositions;
    unsigned int nbPropositionsMax;
    QString file;

    unsigned int totalPropositionsSemestre;

    ChoixManager() : ensemblePropositions(0), nbPropositions(0), nbPropositionsMax(0), totalPropositionsSemestre(0) {}
    ~ChoixManager() {}
    void operator=(const ChoixManager&);
    ChoixManager(const ChoixManager&);
    friend struct Handler;
    struct Handler{
        ChoixManager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; instance=0; }
    };
    static Handler handler;

public :

    ChoixAppli * trouverProposition(unsigned int id) ;
    ChoixAppli** trouverPropositionsDossier(Dossier * d) ; //trouver toutes les propositions pour un dossier en particulier
    void ajoutProposition(unsigned int i, Dossier* d);
    static ChoixManager& getInstance();
    static void libererInstance();
    unsigned int getTotalPropositionsSemestre() const {return totalPropositionsSemestre;}
    void setTotalPropositionsSemestre(unsigned int i) {totalPropositionsSemestre=i;}

    void load_completion();
    void save_completion();

};

class ChoixAppliSemestre {//proposition pour 1 semestre donne par l'application
    //faire un load pour ça aussi .. ? comment on sorganise ?

    unsigned int idChoix;

    QMap<QString,UV*> propositionUV;
    Semestre semestre_concerne;
    unsigned int nbCredits ; //nb de credits accumules avec ce semestre : pas plus de 35
    unsigned int nbUV ; //pas plus de 7
    ChoixAppli * parent;

    Dossier* dos; //dossier concerne

public :

    ChoixAppliSemestre (unsigned int id, unsigned int annee=0, Saison s=Automne, Dossier*d=0,  unsigned int cr=0 ,unsigned int nbuv=0, ChoixAppli* ensemble=0) : semestre_concerne(Semestre(s,annee)), nbCredits(cr), nbUV(nbuv), dos(d), idChoix(id), parent(ensemble)
    {
        ChoixManager& cm=ChoixManager::getInstance();
        unsigned int tot=cm.getTotalPropositionsSemestre();
        cm.setTotalPropositionsSemestre(++tot);

    }

    QMap<QString,UV*> getPropositionUV() const {return propositionUV;}
    Semestre getSemestre() const {return semestre_concerne;}
    unsigned int getNbCredits() const {return nbCredits;}
    unsigned int getNbUV() const {return nbUV;}
    unsigned int getId() const {return idChoix;}
    Dossier * getDossier() const {return dos;}

    void ajoutUV(UV* uv);
    void supprimerUV(UV* uv);


    QMap<QString,UV*>::iterator getQmapIteratorUVbegin() {return propositionUV.begin();}
    QMap<QString,UV*>::iterator getQmapIteratorUVend() {return propositionUV.end();}

    void calculerProposition();//A DEFINIR

};

class ChoixAppli { //regroupe tous les semestres proposes jusqu'à la fin des etudes

    unsigned int idProposition;
    ChoixAppliSemestre** listePropositions;
    unsigned int nbSemestre;
    unsigned int nbMaxSemestre ;
    Dossier * dossier;
    Reponse rep; //reponse donnee par l'etudiant

public :
        ChoixAppli(unsigned int i, Dossier* d) : idProposition(i), dossier(d), listePropositions(0), nbSemestre(0), nbMaxSemestre(0) {}
        Reponse getReponse() const {return rep;}
        ChoixAppliSemestre** getListePropositions() const {return listePropositions;}
        unsigned int getIdentifiant() const {return idProposition;}
        unsigned int getNbSemestres() const {return nbSemestre;}
        Dossier * getDossier() const {return dossier;}

        void setReponse(Reponse r) {rep=r;}

        ChoixAppliSemestre* trouverChoix(Semestre S) ;

        void ajouter_proposition(ChoixAppliSemestre * prop); //une methode de suppression est-elle nécessaire ? je ne pense pas ..

};

class souhaits
{
    Dossier *dos;
    QSet<QString> exigences;
    QSet<QString> preferences;
    QSet<QString> rejets;

public:
    souhaits() {} //tu ne remplis pas dos ?
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
