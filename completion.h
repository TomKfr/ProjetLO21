///\file completion.h
///\brief Ce fichier contient classes d'objets gérant la complétion automatique du cursus d'un étudiant.

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

/*!
 * \brief Classe abstraite mettant en place une interface unique pour exécuter un algorithme de complétion automatique.
 *
 * Cette classe fait partie de l'implémentation du design pattern <em>Strategy</em>, elle définit une interface unique
 * <em>algoCompletion</em> pour le calcul d'une solution, permettant par l'héritage de développer plus tard différents algorithmes
 * capables de traiter différamment les données pour proposer une solution.
 */
class Strategie {

public :
    virtual void algoCompletion(ChoixManager& cm, Dossier * d) const=0;
};
/*!
 * \brief Hérite de la classe Strategie, cette classe implémente l'algorithme de complétion choisi pour l'application.
 */
class StrategieConcrete : public Strategie {

public :
    void algoCompletion(ChoixManager& cm, Dossier * d) const ;
};
/*!
 * \brief Singleton en charge du calcul des différentes proposition de complétion automatique.
 */
class ChoixManager{
    ChoixAppli ** ensemblePropositions; //l'integralite des propositions de l'appli
    ChoixAppli* lastProposition;
    bool creationLastProposition; //le dernier calcul a t il généré un nouveau choix appli ?
    unsigned int nbPropositions; //sert de compteur pour les id des choix appli
    unsigned int nbPropositionsMax;
    unsigned int nbChoixAppliSemestre; //sert de compteur pour les id des chois appli semestre
    QString file;
    const Strategie& completion;
    Semestre SemestreActuel;

    ChoixManager(const Strategie & s) : ensemblePropositions(0), nbPropositions(0), lastProposition(0), nbPropositionsMax(0), nbChoixAppliSemestre(0), completion(s) {}
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
    void calculCompletion(Dossier * d) {completion.algoCompletion(*this, d );}


    void load_completion();
    void save_completion();

};
/*!
 * \brief classe représentant les décisions prises par l'algorithme quant aux UVs sur un seul semestre.
 *
 * Un objet de cette classe est un conteneur reflétant une proposition de l'application pour un semestre.
 */
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
/*!
 * \brief Classe représentant les décisions prises par l'algorithme pour compléter la formation d'un étudiant.
 *
 * Un objet de la classe ChoixAppli est un conteneur reflétant une proposition de l'application jusqu'à la fin du cursus de l'étudiant.
 */
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


/*!
 * \brief Classe d'objets conteneurs pour le stockage d'une prévision de semestre à l'étranger.
 */
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
