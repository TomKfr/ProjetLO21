#ifndef DOSSIER_H
#define DOSSIER_H

#include "iterateur.h"
#include"completion.h"
#include"visiteur_completion.h"
#include <QString>
#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QComboBox>
#include <QDebug>

class visiteur2;
class visiteurCompletion;
class UV;
class souhaits;
class prevision;
class ChoixAppli;
class ChoixAppliSemestre;

class Equivalences {
    QString type;
    unsigned int nb_credits;
    QString description;

    public :
    Equivalences(QString t, unsigned int n, QString d) : type(t), nb_credits(n), description(d) {}
    QString getType() {return type;}
    QString getDescription() {return description;}
    unsigned int getNbCredits() {return nb_credits;}

    void setNbCredits(unsigned int n) {nb_credits=n;}
    void setDescription(QString s) {description=s;}
    void setType(QString s) {type=s;}
};

class Dossier {

    unsigned int numero;
    QString nom;
    QString prenom;
    QString F;
    unsigned int nbSemestre; //GI 01/02/03
    QMap<QString,UV*> listeUV;
    QString * listeResultats;
    unsigned int nbResultats;
    unsigned int nbMaxResultats;
    Equivalences** equivalence;
    unsigned int nbEquivalences;

    souhaits * Souhaits;
    QMap<QString,prevision*> previsions; //tableau pour stocker les prévisions.
    ChoixAppli** Completion;
    unsigned int nbPropositions;
    unsigned int nbMaxPropositions;

    Dossier(unsigned int num, const QString& n, const QString& p, const QString& f, unsigned int nb) : numero(num), nom(n), prenom(p), F(f),
        nbSemestre(nb), listeResultats(0), nbResultats(0), nbMaxResultats(0), nbEquivalences(0),
        Souhaits(0), Completion(0), nbPropositions(0), nbMaxPropositions(0)
    {
        equivalence=new Equivalences*[5];
        for (unsigned int i=0; i<5; i++) equivalence[i]=0;
    }

    //void ajouterCompletionDossier(ChoixAppli * c);
    friend class DossierManager;

public :

    unsigned int getNumero() const {return numero;}
    unsigned int getNbResultats() const {return nbResultats;}
    const QString& getNom() const {return nom;}
    const QString& getPrenom() const {return prenom;}
    const QString& getFormation() const {return F;}
    unsigned int getNumSemestre() const {return nbSemestre;}
    QMap<QString,UV*> getlisteUV() const {return listeUV;}
    QString* getlisteResultats() const {return listeResultats;}
    Equivalences ** getEquivalences() const {return equivalence;}
    souhaits * getSouhaits() const {return Souhaits;}

    unsigned int getNbEquivalences() const {return nbEquivalences;}

    void setNbEquivalences(unsigned int nb) {nbEquivalences=nb;}

    void setNumero(unsigned int n) { numero=n; }
    void setNom(const QString& n) { nom=n; }
    void setPrenom(const QString& n) { prenom=n; }
    void setFormation(const QString& f) { F=f; }
    void setSemestre(unsigned int nb) { this->nbSemestre=nb; }
    //void setListeUV(UV** l) { listeUV=l; }
    void setListeResultats(QString* l) { listeResultats=l; }
    void setResultat(unsigned int i, QString note) {if (i>=nbResultats) throw UTProfilerException("erreur indice resultat"); listeResultats[i]=note;}
    void setEquivalences(Equivalences** l) { equivalence=l; }
    void setSouhaits(souhaits * s) {Souhaits=s;}
    void ajouterUV(UV* nouv);
    void supprimerUV(UV* uv);
    bool estFaite(const QString& code);
    ChoixAppliSemestre* trouverCompletion();

    void ajouterResultat(const QString & res);

    void ajouterSouhait(souhaits* s) {Souhaits=s;}
    const souhaits* getSouhait() const {return Souhaits;}

    void ajt_prevision(const QString& d, unsigned int scs, unsigned int ics, unsigned int stm, unsigned int itm, unsigned int stsh, unsigned int itsh);
    void sup_prevision(const QString &d);

    const QMap<QString,UV*>::const_iterator trouverUV(const QString& code);

    QMap<QString,UV*>::iterator getQmapIteratorUVbegin() {return listeUV.begin();}
    QMap<QString,UV*>::iterator getQmapIteratorUVend() {return listeUV.end();}
    QMap<QString,prevision*>::iterator getPrevisionsBegin() {return previsions.begin();}
    QMap<QString,prevision*>::iterator getPrevisionEnd() {return previsions.end();}
    void acceptCompletion(visiteurCompletion* v);

    /*class iterateur<UV>;
    iterateur<UV>& getIterateurUV();*/
};


class DossierManager {
    Dossier** tabDossiers;
    unsigned int nbDos;
    unsigned int nbMaxDos;
    QString file;
    DossierManager():tabDossiers(0), nbDos(0), nbMaxDos(0) {this->load();}
    ~DossierManager();
    void operator=(const DossierManager&);
    DossierManager(const DossierManager&);
    friend struct Handler;
    struct Handler{
        DossierManager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; instance=0; }
    };
    static Handler handler;


public:
    void load();
    void save();
    unsigned int getnbDos() const {return nbDos;}
    unsigned int getnbMaxDos() const {return nbMaxDos;}
    Dossier* trouverDossier(unsigned int n) const;

    void ajouterDossier(unsigned int num, const QString& n, const QString& p, const QString& f, unsigned int nb);
    void removeDossier(Dossier * dos);

    void addItem(Dossier* dos);
    static DossierManager& getInstance();
    static void libererInstance();
    void accept(visiteur2* v);
    bool listempty() {return tabDossiers==0;}

    class iterateur<Dossier>;
    iterateur<Dossier>& getIterateurDos();
};

#endif // DOSSIER_H
