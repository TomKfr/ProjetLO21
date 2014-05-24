#ifndef DOSSIER_H
#define DOSSIER_H

#include "iterateur.h"
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
class UV;

enum TypeEquivalence {Semestre_a_letranger, Cursus_Anterieur };
class Equivalences {
    TypeEquivalence type;
    unsigned int nb_credits;
    QString description;

    public :
    Equivalences(TypeEquivalence t, unsigned int n, QString d) : type(t), nb_credits(n), description(d) {}
};

class Dossier {

    unsigned int numero;
    QString nom;
    QString prenom;
    QString F;
    //unsigned int nbSemestre; //GI 01/02/03
    QMap<QString,UV*> listeUV;
    QString * listeResultats;
    //unsigned int nbUV;
    //unsigned int nbMaxUV;
    unsigned int nbResultats;
    unsigned int nbMaxResultats;
    Equivalences* equivalence1; //equivalence etranger
    Equivalences* equivalence2; //equivalence cursus
    Dossier(unsigned int num, const QString& n, const QString& p, const QString& f) /*unsigned int ns*/ : numero(num), nom(n), prenom(p), F(f), equivalence1(0), equivalence2(0) /*nbSemestre(ns)*/, listeResultats(0), nbMaxResultats(0) {}
    friend class DossierManager;

public :
    unsigned int getNumero() const {return numero;}
    const QString& getNom() const {return nom;}
    const QString& getPrenom() const {return prenom;}
    const QString& getFormation() const {return F;}
    //unsigned int getNumSemestre() const {return nbSemestre;}
    //UV** getlisteUV() const {return listeUV;}
    QString* getlisteResultats() const {return listeResultats;}
    void setNumero(unsigned int n) { numero=n; }
    void setNom(const QString& n) { nom=n; }
    void setPrenom(const QString& n) { prenom=n; }
    void setFormation(const QString& f) { F=f; }
    //void setListeUV(UV** l) { listeUV=l; }
    void setListeResultats(QString* l) { listeResultats=l; }
    void ajouterUV(UV* nouv);
    void supprimerUV(UV* uv);

    void ajouterResultat(const QString & res);

    const QMap<QString,UV*>::const_iterator trouverUV(const QString& code); // utiliser un const find !!!

    QMap<QString,UV*>::iterator getQmapIteratorUVbegin() {return listeUV.begin();}
    QMap<QString,UV*>::iterator getQmapIteratorUVend() {return listeUV.end();}

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

    void ajouterDossier(unsigned int num, const QString& n, const QString& p, const QString& f /*unsigned int ns*/);
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
