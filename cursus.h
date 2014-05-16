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
    friend class cursusManager;
protected:
    QString nom;
    unsigned int nbCredits;
    QMap<QString,UV*> uvs;

    abstract_cursus_item(const QString& n, unsigned int c): nom(n), nbCredits(c) {}
    virtual ~abstract_cursus_item() {}

public:
    void ajouter_UV(UV*);
    virtual void supprimer_UV(const QString& code);
    QString getNom() const {return nom;}
    unsigned int getNbCred() const {return nbCredits;}
    virtual void modif(const QString& n, unsigned int c, unsigned int s)=0;
    const QMap<QString,UV*>::const_iterator trouverUV(const QString& code);
    QMap<QString,UV*>::iterator getQmapIteratorUVbegin() {return uvs.begin();}
    QMap<QString,UV*>::iterator getQmapIteratorUVend() {return uvs.end();}
};

class formation : public abstract_cursus_item
{
    friend class cursusManager;

    unsigned int nbSemestres; //Le nombre de semestres (théoriques) de la formation
    formation(const QString& n, unsigned int c, unsigned int s): abstract_cursus_item(n,c), nbSemestres(s) {}
    ~formation() {}

public:
    void supprimer_UV(const QString &code);
    unsigned int getNbSem() const {return nbSemestres;}
    virtual void modif(const QString& n, unsigned int c, unsigned int s);
};

class filiere : public abstract_cursus_item
{
    friend class cursusManager;

    formation* form; //formation à laquelle appartieint la filière
    filiere(const QString& n, unsigned int c, formation* f=0): abstract_cursus_item(n,c), form(f) {}
    ~filiere();

public:
    void supprimer_UV(const QString &code);
    virtual void modif(const QString& n, unsigned int c, formation* f);
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
