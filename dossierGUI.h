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



class DebutDossier : public QWidget {
    Q_OBJECT
    QPushButton* modifier;
    QPushButton* sup;
    QPushButton* ajouter;
    QHBoxLayout* coucheH;
    QVBoxLayout* coucheV;


public :
    DebutDossier();

public slots:
    void ajout();
    void suppression();
    void modif();
};

class DossierSuppression : public QWidget {
    Q_OBJECT
    DossierManager& M;
    QLabel* numLabel;
    QLineEdit* code2;
    QPushButton* submit;
    QHBoxLayout* coucheH;
    QVBoxLayout* coucheV;

public : DossierSuppression(UVManager & uvm);

public slots :
    void supprDossier();
};


class DossierModif : public QWidget {
    Q_OBJECT
    DossierManager& M;
    QLabel* codeLabel;
    QLineEdit* code;
    QPushButton* submit;
    QHBoxLayout* coucheH;
    QVBoxLayout* coucheV;

public : DossierModif(UVManager & uvm);

public slots :
    void modifDossier();
};

class DossierAjout : public QWidget{
    Q_OBJECT


    DossierManager& M;

    QLineEdit* num;
    QLabel* numLabel;
    QLineEdit* nom;
    QLabel* nomLabel;
    QLineEdit* prenom;
    QLabel* prenomLabel;
    QSpinBox* formation;
    QLabel* formationLabel;
    QSpinBox* listeUV;
    QLabel* listeUVLabel;
    QLabel* Label;

    QPushButton* sauver;
    QPushButton* annuler;

    QVBoxLayout * couche;
    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;
    QHBoxLayout* coucheH3;
    QHBoxLayout* coucheH4;

public:
 DossierAjout(DossierManager& uvm);
public slots:
 void slot_ajoutDossier();

};

class DossierEditeur : public QWidget {
    Q_OBJECT //macro qui déploie toutes les instructions pour gérer signaux et slots
    Dossier& dos;
    DossierManager& M;

       QLineEdit* num;
       QLabel* numLabel;
       QTextEdit* nom;
       QLabel* nomLabel;
       QTextEdit* prenom;
       QLabel* prenomLabel;
       QSpinBox* formation;
       QLabel* formationLabel;
       QSpinBox* listeUV;
       QLabel* listeUVLabel;

       QPushButton* sauver;
       QPushButton* annuler;

       QVBoxLayout * couche;
       QHBoxLayout* coucheH1;
       QHBoxLayout* coucheH2;
       QHBoxLayout* coucheH3;
       QHBoxLayout* coucheH4;

public:
    DossierEditeur(Dossier& dos, DossierManager & dosM, QWidget* parent=0);
public slots:
    void sauverDossier();

};

#endif // DOSSIERGUI_H
