#ifndef CURSUS_H
#define CURSUS_H

#include <iostream>
#include "UTProfiler.h"
#include "cursusGUI.h"
#include "visiteur.h"
#include <QString>
#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QComboBox>
#include <QDebug>
#include <QStringList>
#include <QMap>

class UV;
template<class I> class iterateur;
class menuFormation;
class UVManager;

class abstract_cursus_item
{
    QString nom;
    unsigned int nbCredits;
    QMap<QString,UV*> uvs;

    friend class cursusManager;
    abstract_cursus_item(const QString& n, unsigned int c): nom(n), nbCredits(c) {}
    virtual ~abstract_cursus_item() {}

public:
    void ajouter_UV(UV*);
    virtual void supprimer_UV(const QString& code);
    QString getNom() const {return nom;}
    unsigned int getNbCred() const {return nbCredits;}
    virtual void modif(const QString& n, unsigned int c)=0;
    const QMap<QString,UV*>::const_iterator trouverUV(const QString& code);
    QMap<QString,UV*>::iterator getQmapIteratorUVbegin() {return uvs.begin();}
    QMap<QString,UV*>::iterator getQmapIteratorUVend() {return uvs.end();}
};

class formation
{
    friend class cursusManager;

    QString nom;
    unsigned int nbCredits; //Le nombre de credits à obtenir pour valider la formation
    unsigned int nbSemestres; //Le nombre de semestres (théoriques) de la formation
    QMap<QString,UV*> uvs; //la liste des uvs appartenant à la formation mais à aucune de ses filières

    formation(const QString& n, unsigned int c, unsigned int s): nom(n), nbCredits(c), nbSemestres(s) {}

public:
    void ajouter_UV(UV*);//template method ??
    void supprimer_UV(const QString &code);
    ~formation() {}
    QString getNom() const {return nom;}
    unsigned int getNbCred() const {return nbCredits;}
    unsigned int getNbSem() const {return nbSemestres;}
    void modif(const QString& n, unsigned int c, unsigned int s);
    const QMap<QString,UV*>::const_iterator trouverUV(const QString& code); // utiliser un const find !!!

    QMap<QString,UV*>::iterator getQmapIteratorUVbegin() {return uvs.begin();}
    QMap<QString,UV*>::iterator getQmapIteratorUVend() {return uvs.end();}
    /*class iterateur<UV>;
    iterateur<UV>& getIterateurUV();*/
};

class filiere
{
    QString nom;
    formation* form; //formation à laquelle appartieint la filière
    QMap<QString,UV*> uvs; //la liste des uvs appartenant à la filière et donc à la formation à laquelle appartient la filière

public:
    filiere(const QString& n="", formation* f=0): nom(n), form(f) {}
    void ajouter_UV(const UV&);
    ~filiere();
};

class cursusManager // gestionnaire des cursus
{
    QMap<QString,formation*> formations;
    QMap<QString,filiere*> filieres;

public:
    cursusManager() {this->chargerCursus();}
    ~cursusManager() {qDebug()<<"Destruction cursusManager";}

    friend struct Handler;
    struct Handler{
        cursusManager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; instance=0; }
    };
    static Handler handler;

    formation* trouverForm(const QString &n);
    void ajouterFiliere(const QString& nom, formation* fo);
    void chargerCursus();
    void ajouterFormation(const QString& nom, unsigned int c, unsigned int s);
    void supprimerFormation(const QString& nom);
    void sauverCursus(QWidget* parent);
    void accept(visiteur* v);

    QMap<QString,formation*>::iterator getQmapIteratorFormbegin() {return formations.begin();}
    QMap<QString,formation*>::iterator getQmapIteratorFormend() {return formations.end();}

    static cursusManager& getInstance();
    static void libererInstance();

    /*class iterateur<formation>;
    iterateur<formation>& getIterateurForm();*/
};


class ajoutFormation : public QWidget {
    Q_OBJECT
    cursusManager* man;
    menuFormation* parent;
    QVBoxLayout* mainbox;
    QHBoxLayout* hbox1;
    QHBoxLayout* hbox2;
    QHBoxLayout* hbox3;
    QLabel* lbl1;
    QLabel* lbl2;
    QLabel* lbl3;
    QLineEdit* nom;
    QSpinBox* credits;
    QSpinBox* semstr;
    QPushButton* valider;


public :
    ajoutFormation(cursusManager *m, menuFormation* p);

public slots:
    void ajout();
};

class modifFormation : public QWidget {
    Q_OBJECT
    cursusManager* man;
    formation* form;
    QVBoxLayout* mainbox;
    QHBoxLayout* hbox1;
    QHBoxLayout* hbox2;
    QHBoxLayout* hbox3;
    QLabel* lbl1;
    QLabel* lbl2;
    QLabel* lbl3;
    QLineEdit* nom;
    QSpinBox* credits;
    QSpinBox* semstr;
    QPushButton* valider;


public :
    modifFormation(cursusManager *m, formation* f);

public slots:
    void modif();
};

class visualiserFormation : public QWidget
{
    Q_OBJECT
    cursusManager* cman;
    UVManager* uman;
    formation* objet;
    QHBoxLayout* mainbox;
    QVBoxLayout* vbox1;
    QVBoxLayout* vbox2;
    QHBoxLayout* hbox1;
    QHBoxLayout* hbox2;
    QHBoxLayout* hbox3;
    QLabel* form;
    QLabel* cred;
    QLabel* semstr;
    QLabel* lbluvs;
    QLabel* uvs;
    QComboBox* supprUV;
    QPushButton* retour;
    QPushButton* modif;
    QPushButton* suppr;

public:
    visualiserFormation(cursusManager* cmanager, UVManager* umanager, formation* f);
public slots:
    void moduvs();
    void update();
    void supprimer();

};

class selectUVsFormation : public QWidget
{
    Q_OBJECT
    cursusManager* cman;
    UVManager* uman;
    formation* objet;
    visualiserFormation* parent;
    QVBoxLayout* mainbox;
    QLabel* label1;
    QComboBox* choix;
    QPushButton* retour;
    QPushButton* ajouter;

public:
    selectUVsFormation(cursusManager* cm, UVManager* um, formation* f, visualiserFormation* p);
public slots:
    void ajouterUV();
    void update();

};

#endif // CURSUS_H
