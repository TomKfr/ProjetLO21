#include"uvGUI.h"
#include<QApplication>
#include<QWidget>
#include<QLineEdit>
#include<QTextEdit>
#include<QPushButton>
#include<QVBoxLayout>
#include<QString>
#include<QFileDialog>
#include"UTProfiler.h"
#include "cursus.h"
#include"dossier.h"
#include"dossierGUI2.h"
#include <QDebug>
#include "cursusGUI.h"


int main(int argc,char*argv[]) {
QApplication app(argc, argv);

/*Debut fenetre;
fenetre.show();*/

cursusManager& m=cursusManager::getInstance();
UVManager& u=UVManager::getInstance();
DossierManager& d=DossierManager::getInstance();
QString chemin=QFileDialog::getOpenFileName(0,"Ouvrir un fichier de dossiers");
d.load(chemin);
//m.chargerCursus();
//QString chemin=QFileDialog::getOpenFileName(0,"Ouvrir un fichier d'Uvs");
//u.load(chemin);
/*
menuFormation* fenetre =new menuFormation(&m,&u);
fenetre->show();*/

MenuDossier fenetre;
fenetre.show();

return app.exec();
}
