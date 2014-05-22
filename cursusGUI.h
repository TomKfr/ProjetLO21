#ifndef MENU_H
#define MENU_H

#include <iostream>
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
class formation;

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
    QPushButton* fil;
    QPushButton* supprimer;
    QPushButton* quit;
    QPushButton* sauver;

public:
    menuFormation();

public slots:
    void voir();
    void ajout();
    void modif();
    void filir();
    void suppr();
    void update();
    void save();
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
    menuFormation* parent;
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
    modifFormation(cursusManager *m, menuFormation* p, formation* f);

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


// ////////////////////// fin formations ////////////////////////

class GestionFiliereFormation : public QWidget
{
    Q_OBJECT
    UVManager& uman;
    cursusManager& cman;
    formation* objet;
    //menuFiliere* parent;
    QVBoxLayout* mainbox;
    QHBoxLayout* hbox1;
    QVBoxLayout* vbox1;
    QVBoxLayout* vbox2;
    QLabel* lbl1;
    QLabel* lbl2;
    QLabel* lbl3;
    QComboBox* ajt;
    QComboBox* suppr;
    QPushButton* retour;
    QPushButton* ajouter;
    QPushButton* supprimer;

public:
    GestionFiliereFormation(formation* f);
public slots:
    void ajouterFiliere();
    void update();
    void supprimerFiliere();
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

#endif // MENU_H
