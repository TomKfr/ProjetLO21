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
    QPushButton* modifier;
    QPushButton* sup;
    QPushButton* ajouter;
    QHBoxLayout* coucheH;
    QVBoxLayout* coucheV;


public :
    MenuDossier();

public slots:
    void ajout();
    //void suppression();
    //void modif();
};


class DossierAjout : public QWidget{
    Q_OBJECT


    unsigned int nbUV;
    unsigned int nbMaxUV;
    DossierManager& M;
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
 DossierAjout(DossierManager& uvm);

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
    AjoutUV(DossierAjout* dossier, Dossier* d);

public slots :
    void end_listeUV();
    void ajout_UVDossier();
    void update();

};

#endif // DOSSIERGUI_H
