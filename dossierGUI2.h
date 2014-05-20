#ifndef DOSSIERGUI_H
#define DOSSIERGUI_H

#include<iostream>
#include<QWidget>
#include<QObject>
#include<QPushButton>
#include<QApplication>
#include<QWidget>
#include<QLineEdit>
#include<QTextEdit>
#include<QVBoxLayout>
#include<QString>
#include<QFileDialog>
#include<QLabel>
#include<QCheckBox>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QComboBox>
#include<QSpinBox>
#include<QMessageBox>
#include"UTProfiler.h"
#include"dossier.h"



class MenuDossier : public QWidget {
    Q_OBJECT
    DossierManager* dman;
    QLabel * numero;
    QComboBox* dossiers;
    //QPushButton* visu;
    QPushButton* modifier;
    QPushButton* sup;
    QPushButton* sauver;
    QPushButton* terminer;
    QPushButton* ajouter;
    QHBoxLayout* coucheH;
    QHBoxLayout* coucheH0;
    QVBoxLayout* coucheV;


public :
    MenuDossier();
    void update();

public slots:
    void ajout();
    void suppression();
    void supDossier(unsigned int num, DossierManager& dm);
    void modif();
    void fin();
    //void visualiser();
    void sauvegarder();
};


/*class visualiserDossier : public QWidget
{
    Q_OBJECT

    Dossier* dos;
    QLabel* numdos;
    QLabel* listuv;
    QHBoxLayout* mainbox;
    QPushButton* quit;

public:
    visualiserDossier(Dossier* d);
};*/

class DossierAjout : public QWidget{
    Q_OBJECT


    unsigned int nbUV;
    unsigned int nbMaxUV;
    DossierManager& M;
    MenuDossier* parent;
    QLineEdit* num;
    QLabel* numLabel;
    QLineEdit* nom;
    QLabel* nomLabel;
    QLineEdit* prenom;
    QLabel* prenomLabel;
    QComboBox* f;
    QLabel* formationLabel;

    QLabel* listeUVLabel;
    QLabel* Label;

    QPushButton* SelectUV;
    QPushButton* sauver;

    QVBoxLayout * couche;
    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;
    QHBoxLayout* coucheH3;
    QHBoxLayout* coucheH4;

public:
 DossierAjout(DossierManager& uvm, MenuDossier* p);

 void ajouter_UV(UV* nouv);


public slots:
 void slot_ajoutDossier();
 void slot_selectUV();
 void update();

};



class AjoutUV : public QWidget {
    Q_OBJECT

    QComboBox * Liste;
    QComboBox * Result ;
    QLabel* LabelListe;
    QLabel* LabelResult;
    QPushButton * submit ;
    QPushButton * retour;

    QVBoxLayout * couche;
    QHBoxLayout* coucheH1;

    DossierAjout * DA;
    Dossier *dos;



public :
    AjoutUV(Dossier* d, DossierAjout* dossier=0);

public slots :
    void end_listeUV();
    void ajout_UVDossier();
    void update();

};

class ModifierDossier : public QWidget
{
    Q_OBJECT


    DossierManager& M;
    Dossier* dos;

    QLineEdit* num;
    QLabel* numLabel;
    QLineEdit* nom;
    QLabel* nomLabel;
    QLineEdit* prenom;
    QLabel* prenomLabel;

    QLabel* formationLabel;

    QPushButton* modifUV;
    QPushButton* sauver;
    QPushButton* modifFormation;
    QVBoxLayout * couche;
    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;
    QHBoxLayout* coucheH3;


public:
 ModifierDossier(DossierManager& uvm, Dossier * dos);

public slots:
 void slot_modifFormation();
 void slot_modifUV();
 void slot_finModifDossier();


};

class ModifFormation : public QWidget
{
    Q_OBJECT
    Dossier * dossier;
    QLabel * formationLabel;
    QComboBox* f;
    QPushButton* valider;
    QVBoxLayout * couche;
    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;

public :
    ModifFormation(Dossier* d);

public slots :
   void enregistrer_formation();
   void update();


};

class ModifUV : public QWidget
{
    Q_OBJECT

    QPushButton* ajouter;
    QPushButton* supprimer;
    QPushButton* fin;
    QVBoxLayout * couche;
    QHBoxLayout* coucheH1;
    Dossier* dos;


public :
    ModifUV(Dossier* d);

public slots :
   void ajouterUV();
   void supprimerUV();
   void finUV();
};

class SuppressionUV : public QWidget
{
    Q_OBJECT
    QComboBox* liste;
    QPushButton* supprimer;
    QPushButton* fin;
    QVBoxLayout * couche;
    QHBoxLayout* coucheH1;
    Dossier* dos;


public :
    SuppressionUV(Dossier* d);
    void update();

public slots :
   void suppression_une_uv();
   void finSuppression();
};
#endif // DOSSIERGUI_H
