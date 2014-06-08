#include"menu.h"
#include"cursusGUI.h"
#include<QWidget>
#include<QObject>
#include<QPushButton>
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
#include<QXmlStreamReader>
#include"dossierGUI2.h"
#include"uvGUI.h"
#include "dossier.h"
#include "cursus.h"
#include"UTProfiler.h"

/*!
 * \brief Constructeur du menu initial
 */
MenuDebut::MenuDebut() {

    this->setWindowTitle(QString("Projet LO21"));

    texte = new QLabel("Bienvenue !", this);
    choixOP=new QLabel("Sur quelle partie du projet souhaitez-vous travailler ?", this);
    op_UV=new QPushButton("Les UVs", this);
    op_Dossiers=new QPushButton("Les dossiers étudiants", this);
    op_Formations=new QPushButton("Les formations", this);
    op_Filieres= new QPushButton("Les filières", this);
    no_op= new QPushButton("Terminer", this);
    initload= new QPushButton("Fucking load this !", this);
    SemestreActuel= new QLabel("Quel est le semestre actuel :", this);
    saison = new QComboBox(this);
    saison->addItem("Automne");
    saison->addItem("Printemps");

    Annee = new QComboBox(this);
    Annee->addItem("2014");
    Annee->addItem("2015");
    Annee->addItem("2016");
    Annee->addItem("2017");
    Annee->addItem("2018");


    coucheH1=new QHBoxLayout;
    coucheH1->addWidget(texte);

    coucheH7=new QHBoxLayout;
    coucheH7->addWidget(SemestreActuel);
    coucheH7->addWidget(saison);
    coucheH7->addWidget(Annee);

    coucheH8=new QHBoxLayout;
    coucheH8->addWidget(choixOP);

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
    coucheV->addLayout(coucheH7);
    coucheV->addLayout(coucheH8);
    coucheV->addLayout(coucheH2);
    coucheV->addLayout(coucheH3);
    coucheV->addLayout(coucheH4);
    coucheV->addLayout(coucheH5);
    coucheV->addLayout(coucheH6);
    coucheV->addWidget(initload);


    setLayout(coucheV);

    QObject::connect(op_UV, SIGNAL(clicked()), this, SLOT(lancer_UV()));
    QObject::connect(op_Dossiers, SIGNAL(clicked()), this, SLOT(lancer_Dossiers()));
    QObject::connect(op_Formations, SIGNAL(clicked()), this, SLOT(lancer_Formations()));
    QObject::connect(op_Filieres, SIGNAL(clicked()), this, SLOT(lancer_Filieres()));
    QObject::connect(no_op, SIGNAL(clicked()), this, SLOT(lancer_rien()));
    QObject::connect(initload,SIGNAL(clicked()),this,SLOT(launch_this_fucking_initial_load()));

}

/*!
 * \brief Ouvre le menu de gestion des UVs
 */

void MenuDebut::enregistrer_semestre() {

Saison s= StringToSaison(saison->currentText()) ;

bool ok;
QString n1=Annee->currentText();
unsigned int n2=n1.toInt(&ok);
qDebug()<<"saison : "<<s<<" annee :"<<n2;

Semestre * sem= new Semestre(s, n2);

ChoixManager& cm=ChoixManager::getInstance();
cm.setSemestreActuel(*sem);

}


void MenuDebut::lancer_UV() {

    Debut * fenetre1 = new Debut;
    fenetre1->show();
}

/*!
 * \brief Ouvre le menu de gestion des dossiers
 */
void MenuDebut::lancer_Dossiers() {
    qDebug()<<"avant le constructeur";
    //DossierManager& d=DossierManager::getInstance();
    //d.load();

    enregistrer_semestre();

    MenuDossier * fenetre= new MenuDossier();
    fenetre->show();

}
/*!
 * \brief Ouvre le menu de gestion des formations
 */
void MenuDebut::lancer_Formations() {
    menuFormation* fenetre3 =new menuFormation();
    fenetre3->show();
}
/*!
 * \brief Ouvre le menu de gestion des filières
 */
void MenuDebut::lancer_Filieres(){
    menuFiliere* fenetre4=new menuFiliere();
    fenetre4->show();
}
/*!
 * \brief Ferme l'application
 */
void MenuDebut::lancer_rien(){
    this->close();
}

void MenuDebut::launch_this_fucking_initial_load()
{
    UVManager& uman=UVManager::getInstance();
    cursusManager& cman=cursusManager::getInstance();

    QString fileout= QFileDialog::getOpenFileName(this);
    qDebug()<<"Ouverture du fichier "<<fileout;
    QFile fin(fileout);
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"erreur ouverture fichier !!";
        exit(2);
    }
    QXmlStreamReader xml(&fin);
    while(!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartDocument) continue;
        if(token == QXmlStreamReader::StartElement)
        {
            if(xml.name()=="UVSection") xml.readNext();
            if(xml.name()=="uv")
            {
                QString form;
                QString uv;
                QString titre;
                QString cat;
                unsigned int cr=0;
                xml.readNext();
                xml.readNext();
                while(!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="uv"))
                {
                    if(xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="code")
                    {
                        xml.readNext();
                        uv=xml.text().toString();
                    }
                    if(xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="nom")
                    {
                        xml.readNext();
                        titre=xml.text().toString();
                    }
                    if(xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="credit")
                    {
                        QXmlStreamAttributes attr=xml.attributes();
                        cat=attr.value("type").toString();
                        xml.readNext();
                        cr=xml.text().toUInt();
                    }
                    if(xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="branche")
                    {
                        xml.readNext();
                        form=xml.text().toString();
                        formation* newform=cman.trouverForm(form);
                        if(!newform)
                        {
                            qDebug()<<"erreur ajout formation ! Création d'une nouvelle";
                            newform=cman.ajouterFormation(form,0,0,0,0,0, 0);
                        }
                        else
                        {
                            UV* newuv=uman.trouverUV(uv);
                            if(newuv)
                            {
                                newform->ajouter_UV(newuv);
                            }
                            else
                            {
                                qDebug()<<"UV non trouvée, création d'une nouvelle";
                                newuv=uman.ajouterUV(uv,titre,cr,StringToCategorie(cat),false,false);
                            }
                        }
                    }
                    xml.readNext();
                }
            }
        }
        xml.readNext();
    }
}
