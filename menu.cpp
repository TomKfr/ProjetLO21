#include "menu.h"
#include "cursusGUI.h"
#include "uvGUI.h"
#include "dossierGUI2.h"
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
#include<QDebug>

MenuDebut::MenuDebut() {

    this->setWindowTitle(QString("Projet LO21"));

    texte = new QLabel("Bienvenue ! Sur quel partie du projet souhaitez-vous travailler ?", this);
    op_UV=new QPushButton("Les UVs", this);
    op_Dossiers=new QPushButton("Les dossiers étudiants", this);
    op_Formations=new QPushButton("Les formations", this);
    op_Filieres= new QPushButton("Les filières", this);
    no_op= new QPushButton("Terminer", this);

    coucheH1=new QHBoxLayout;
    coucheH1->addWidget(texte);

    coucheH2=new QHBoxLayout;
    coucheH2->addWidget(op_UV);

    coucheH3=new QHBoxLayout;
    coucheH3->addWidget(op_Dossiers);

    coucheH4=new QHBoxLayout;
    coucheH4->addWidget(op_Formations);

    coucheH5=new QHBoxLayout;
    coucheH5->addWidget(op_Filieres);

    coucheH6=new QHBoxLayout;
    coucheH6->addWidget(no_op);


    coucheV=new QVBoxLayout;
    coucheV->addLayout(coucheH1);
    coucheV->addLayout(coucheH2);
    coucheV->addLayout(coucheH3);
    coucheV->addLayout(coucheH4);
    coucheV->addLayout(coucheH5);
    coucheV->addLayout(coucheH6);


    setLayout(coucheV);

    QObject::connect(op_UV, SIGNAL(clicked()), this, SLOT(lancer_UV()));
    QObject::connect(op_Dossiers, SIGNAL(clicked()), this, SLOT(lancer_Dossiers()));
    QObject::connect(op_Formations, SIGNAL(clicked()), this, SLOT(lancer_Formations()));
    QObject::connect(op_Filieres, SIGNAL(clicked()), this, SLOT(lancer_Filieres()));
    QObject::connect(no_op, SIGNAL(clicked()), this, SLOT(lancer_rien()));

}

void MenuDebut::lancer_UV() {
    qDebug()<<"lancer uv";
    Debut * fenetre1 = new Debut;
    qDebug()<<"apres constructeur";
    fenetre1->show();

}


void MenuDebut::lancer_Dossiers() {
    DossierManager& d=DossierManager::getInstance();
    d.load();
    MenuDossier * fenetre= new MenuDossier;
    fenetre->show();

}
void MenuDebut::lancer_Formations() {
    //menuFormation* fenetre3 =new menuFormation();
    //fenetre3->show();
}
void MenuDebut::lancer_Filieres(){

}
void MenuDebut::lancer_rien(){
    this->close();
}

