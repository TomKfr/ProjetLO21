#ifndef COMPLETION_H
#define COMPLETION_H
#include"UTProfiler.h"
#include"dossier.h"

#include <QSet>

class Dossier;
class StrategieConcrete;
class ChoixAppli;
class ChoixManager;
enum Reponse {Valider, Refuser,Avancer, Retarder};
Reponse StringToReponse(const QString& s);
QString ReponseToString(Reponse c);

class Strategie {

public :
    virtual ChoixAppli* algoCompletion(ChoixManager& cm, Dossier * d) const=0;
};

class StrategieConcrete : public Strategie {

public :
    ChoixAppli* algoCompletion(ChoixManager& cm, Dossier * d) const ; //a completer
};

class ChoixManager{
    ChoixAppli ** ensemblePropositions; //l'integralite des propositions de l'appli
    ChoixAppli* lastProposition;
    bool creationLastProposition; //le dernier calcul a t il généré un nouveau choix appli ?
    unsigned int nbPropositions; //sert de compteur pour les id des choix appli
    unsigned int nbPropositionsMax;
    unsigned int nbChoixAppliSemestre; //sert de compteur pour les id des chois appli semestre
    QString file;
    const StrategieConcrete& completion;
    Semestre SemestreActuel;

    ChoixManager(const StrategieConcrete & s) : ensemblePropositions(0), nbPropositions(0), lastProposition(0), nbPropositionsMax(0), nbChoixAppliSemestre(0), completion(s) {}
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

    ChoixAppli * trouverProposition(unsigned int id) ; //trouver une proposition d'identifiant id
    ChoixAppli** trouverPropositionsDossier(Dossier * d) ; //trouver toutes les propositions pour un dossier en particulier
    unsigned int trouverNbPropositionsDossier(Dossier * d);
    void removeChoix(Dossier * d);
    //void removeSemestres(ChoixAppli* c);

    Semestre getSemestreActuel() const {return SemestreActuel; }
    unsigned int getNbChoixSemestre() const {return nbChoixAppliSemestre; }
    unsigned int getNbPropositions() const {return nbPropositions; }
    ChoixAppli* getLastProposition() const {return lastProposition;}
    bool getCreationLastProposition() const {return creationLastProposition;}

    void setNbChoixSemestre(unsigned int i) {nbChoixAppliSemestre=i;}
    void setSemestreActuel(Semestre s) {SemestreActuel=s;}
    void setLastProposition(ChoixAppli * p) {lastProposition=p;}
    void setCreationLastProposition(bool b) {creationLastProposition=b;}

    static ChoixManager& getInstance();
    static void libererInstance();

    void ajouterProposition(ChoixAppli* c);
    bool verifCompletion(Dossier * d) const ;
    ChoixAppli* calculCompletion(Dossier * d) {return (completion.algoCompletion(*this, d ));}


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
    bool stage ; //l'etudiant est-il en stage pendant tout le semestre ? 1 oui 0 non
    ChoixAppli * parent;

    Dossier* dos; //dossier concerne

public :

    ChoixAppliSemestre (unsigned int id, Dossier*d, Semestre s, ChoixAppli* ensemble, unsigned int cr=0 ,unsigned int nbuv=0) : idChoix(id), semestre_concerne(s), nbCredits(cr), nbUV(nbuv), parent(ensemble), dos(d)
    {
        ChoixManager& cm=ChoixManager::getInstance();
        unsigned int tot=cm.getNbChoixSemestre();
        cm.setNbChoixSemestre(++tot);

    }

    QMap<QString,UV*> getPropositionUV() const {return propositionUV;}
    Semestre getSemestre() const {return semestre_concerne;}
    unsigned int getNbCredits() const {return nbCredits;}
    unsigned int getNbUV() const {return nbUV;}
    unsigned int getId() const {return idChoix;}
    Dossier * getDossier() const {return dos;}
    ChoixAppli* getParent() const {return parent;}

    void ajoutUV(UV* uv);
    void supprimerUV(UV* uv);

    void setChoixAppli(ChoixAppli* c) {parent=c;}
    void setNbCredits(unsigned int i) {nbCredits=i;}
    void setNbUVs(unsigned int i) {nbUV=i;}
    void setStage(bool s) {stage=s; }


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
        ChoixAppli(unsigned int i, Dossier* d) : idProposition(i), listePropositions(0), nbSemestre(0), nbMaxSemestre(0), dossier(d) {}
        Reponse getReponse() const {return rep;}
        ChoixAppliSemestre** getListePropositions() const {return listePropositions;}
        unsigned int getIdentifiant() const {return idProposition;}
        unsigned int getNbSemestres() const {return nbSemestre;}
        Dossier * getDossier() const {return dossier;}

        void setReponse(Reponse r) {rep=r;}
        void setNbSemestres(unsigned int i) {nbSemestre=0;}

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

    QSet<QString> getExigences() const {return exigences; }
    QSet<QString> getPreferences() const {return preferences; }
    QSet<QString> getRejets() const {return rejets; }
    void setExigences(QSet<QString> s) {exigences=s;}
    void setPreferences(QSet<QString> s) {preferences=s;}
};

class prevision
{
    QString destination;
    QPair<unsigned int, unsigned int> bornesCS; //first=borne inférieure, second=borne supérieure
    QPair<unsigned int, unsigned int> bornesTM;
    QPair<unsigned int, unsigned int> bornesTSH;
    /*unsigned int borneSupCS;
    unsigned int borneInfCS;
    unsigned int borneSupTM;
    unsigned int borneInfTM;
    unsigned int borneSupTSH;
    unsigned int borneInfTSH;*/

public:
    prevision(const QString& d, unsigned int scs, unsigned int ics, unsigned int stm, unsigned int itm, unsigned int stsh, unsigned int itsh): destination(d)
    {
        bornesCS.second=scs;
        bornesCS.first=ics;
        bornesTM.second=stm;
        bornesTM.first=itm;
        bornesTSH.second=stsh;
        bornesTSH.first=itsh;
    }
    QString getdestination() {return destination;}
    unsigned int getbsCS() {return bornesCS.second;}
    unsigned int getbsTM() {return bornesTM.second;}
    unsigned int getbsTSH() {return bornesTSH.second;}
    unsigned int getbiCS() {return bornesCS.first;}
    unsigned int getbiTM() {return bornesTM.first;}
    unsigned int getbiTSH() {return bornesTSH.first;}
    /*
     * unsigned int getbsCS() {return borneSupCS;}
    unsigned int getbsTM() {return borneSupTM;}
    unsigned int getbsTSH() {return borneSupTSH;}
    unsigned int getbiCS() {return borneInfCS;}
    unsigned int getbiTM() {return borneInfTM;}
    unsigned int getbiTSH() {return borneInfTSH;}
     */
};



#endif // COMPLETION_H
