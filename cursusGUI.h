#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "UTProfiler.h"
#include "cursus.h"
#include <QString>
#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QComboBox>

class cursusManager;
class UVManager;
class UV;
class filiere;
template<class I> class iterateur;


class menuFormation : public QWidget
{
    Q_OBJECT
    cursusManager* m;
    UVManager* uvman;
    QVBoxLayout* mainbox;
    QHBoxLayout* hbox1;
    QHBoxLayout* hbox2;
    QLabel* titre;
    QComboBox* select;
    QPushButton* visualiser;
    QPushButton* ajouter;
    QPushButton* modifier;
    QPushButton* supprimer;
    QPushButton* quit;
    QPushButton* sauver;

public:
    menuFormation(cursusManager* m, UVManager *u);

public slots:
    void voir();
    void ajout();
    void modif();
    void suppr();
    void update();
    void save();
};

class menuFiliere : public QWidget
{
    Q_OBJECT
    cursusManager* m;
    UVManager* uvman;
    QVBoxLayout* mainbox;
    QHBoxLayout* hbox1;
    QHBoxLayout* hbox2;
    QLabel* titre;
    QComboBox* select;
    QPushButton* visualiser;
    QPushButton* ajouter;
    QPushButton* modifier;
    QPushButton* supprimer;
    QPushButton* quit;
    QPushButton* sauver;

public:
    menuFiliere();

public slots:
    void voir();
    void ajout();
    void modif();
    void suppr();
    void update();
    void save();
};

class ajoutFiliere: public QWidget {
    Q_OBJECT
    menuFiliere* parent;
    QVBoxLayout* mainbox;
    QHBoxLayout* hbox1;
    QHBoxLayout* hbox2;
    QHBoxLayout* hbox3;
    QLabel* lbl1;
    QLabel* lbl2;
    QLineEdit* nom;
    QSpinBox* credits;
    QPushButton* valider;

public :
    ajoutFiliere(menuFiliere* p);

public slots:
    void ajout();
};

class visualiserFiliere : public QWidget
{
    Q_OBJECT
    filiere* objet;
    QHBoxLayout* mainbox;
    QVBoxLayout* vbox1;
    QVBoxLayout* vbox2;
    QHBoxLayout* hbox1;
    QHBoxLayout* hbox2;
    QHBoxLayout* hbox3;
    QLabel* form;
    QLabel* cred;
    QLabel* lbluvs;
    QLabel* uvs;
    QComboBox* supprUV;
    QPushButton* retour;
    QPushButton* modif;
    QPushButton* suppr;

public:
    visualiserFiliere(filiere* f);
public slots:
    void moduvs();
    void update();
    void supprimer();
};

class modifFiliere : public QWidget {
    Q_OBJECT
    menuFiliere* parent;
    filiere* fil;
    QVBoxLayout* mainbox;
    QHBoxLayout* hbox1;
    QHBoxLayout* hbox2;
    QHBoxLayout* hbox3;
    QLabel* lbl1;
    QLabel* lbl2;
    QLineEdit* nom;
    QSpinBox* credits;
    QPushButton* valider;

public :
    modifFiliere(menuFiliere* p, filiere* f);

public slots:
    void modif();
};

class selectUVsFiliere : public QWidget
{
    Q_OBJECT
    cursusManager& cman;
    UVManager& uman;
    filiere* objet;
    visualiserFiliere* parent;
    QVBoxLayout* mainbox;
    QLabel* label1;
    QComboBox* choix;
    QPushButton* retour;
    QPushButton* ajouter;

public:
    selectUVsFiliere(filiere* f, visualiserFiliere* p);
public slots:
    void ajouterUV();
    void update();
};

/*class menuCursus : public QWidget
{
    Q_OBJECT
    QPushButton* form;
    QPushButton* fil;
    QVBoxLayout* mainbox;

public:
   menuCursus()
   {
       mainbox=new QVBoxLayout(this);
       form=new QPushButton("Formations",this);
       fil=new QPushButton("Filières",this);
       mainbox->addWidget(form);
       QObject::connect(form,SIGNAL(clicked()),this,SLOT(menuformation()));
       QObject::connect(fil,SIGNAL(clicked()),this,SLOT(menufiliere()));
   }

public slots:
   void menuformation()
   {
       cursusManager& m=cursusManager::getInstance();
       UVManager& u=UVManager::getInstance();
       menuFormation* f1=new menuFormation(&m,&u);
       f1->show();
   }
   void menufiliere()
   {
        menuFiliere* f2=new menuFiliere();
        f2->show();
   }
};*/

#endif // MENU_H
