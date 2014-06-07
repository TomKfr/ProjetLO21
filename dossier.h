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

/*!
 * \brief Un objet équivalences permet de stocker d'éventuelles équivalences de crédits obtenues.
 */
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

/*!
 * \brief Un objet dossier permet de stocker toutes les informations relatives à un étudiant.
 */
class Dossier {

    unsigned int numero;
    QString nom;
    QString prenom;
    QString F;
    unsigned int nbSemestre; //GI 01/02/03
    //QMap<QString,UV*> listeUV; // A CHANGER !!!!!!
    //QString * listeResultats;
    QMap<QString,Note> listeUV; //Code de l'UV + note obtenue !!
    unsigned int nbResultats;
    unsigned int nbMaxResultats;
    Equivalences** equivalence;
    unsigned int nbEquivalences;
    prevision* semestreprevu;
    souhaits * Souhaits;
    //QMap<QString,prevision*> previsions; //tableau pour stocker les prévisions.
    ChoixAppli** Completion;
    unsigned int nbPropositions;
    unsigned int nbMaxPropositions;

    Dossier(unsigned int num, const QString& n, const QString& p, const QString& f, unsigned int nb) : numero(num), nom(n), prenom(p), F(f),
        nbSemestre(nb), nbResultats(0), nbMaxResultats(0), nbEquivalences(0), semestreprevu(0),
        Souhaits(0), Completion(0), nbPropositions(0), nbMaxPropositions(0)
    {
        equivalence=new Equivalences*[5];
        for (unsigned int i=0; i<5; i++) equivalence[i]=0;
    }

    friend class DossierManager;

public :

    unsigned int getNumero() const {return numero;}
    unsigned int getNbResultats() const {return nbResultats;}
    QMap<QString,Note> getListeUV() const {return listeUV; }
    const QString& getNom() const {return nom;}
    const QString& getPrenom() const {return prenom;}
    const QString& getFormation() const {return F;}
    unsigned int getNumSemestre() const {return nbSemestre;}
    Equivalences ** getEquivalences() const {return equivalence;}
    souhaits * getSouhaits() const {return Souhaits;}
    unsigned int getNbEquivalences() const {return nbEquivalences;}
    prevision* getprevisions() {return semestreprevu;}
    const souhaits* getSouhait() const {return Souhaits;}

    void setNbEquivalences(unsigned int nb) {nbEquivalences=nb;}
    void setNumero(unsigned int n) { numero=n; }
    void setNom(const QString& n) { nom=n; }
    void setPrenom(const QString& n) { prenom=n; }
    void setFormation(const QString& f) { F=f; }
    void setSemestre(unsigned int nb) { this->nbSemestre=nb; }
    void setResultat(const QString& code, Note n);
    void setEquivalences(Equivalences** l) { equivalence=l; }
    void setprevision(prevision* prv) {semestreprevu=prv;}
    void setSouhaits(souhaits * s) {Souhaits=s;}

    void ajouterUV(const QString& code, Note n);
    void supprimerUV(UV* uv);
    bool estValidee(const QString& code);


    ChoixAppli * calculCompletion();
    ChoixAppliSemestre* trouverCompletion();

    void ajouterResultat(const QString & res);

    void ajouterSouhait(souhaits* s) {Souhaits=s;}

    void ajt_prevision(const QString& d, unsigned int scs, unsigned int ics, unsigned int stm, unsigned int itm, unsigned int stsh, unsigned int itsh);
    void sup_prevision(const QString &d);

    const QMap<QString,Note>::const_iterator trouverUV(const QString& code);

    QMap<QString,Note>::iterator getQmapIteratorUVbegin() {return listeUV.begin();}
    QMap<QString,Note>::iterator getQmapIteratorUVend() {return listeUV.end();}
    //QMap<QString,prevision*>::iterator getPrevisionsBegin() {return previsions.begin();}
    //QMap<QString,prevision*>::iterator getPrevisionEnd() {return previsions.end();}
    void acceptCompletion(visiteurCompletion* v);

};

/*!
 * \brief Singleton gestionnaire des dossiers.
 */
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
