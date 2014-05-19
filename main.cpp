#include"menu.h"
#include"uvGUI.h"
#include<QApplication>
#include<QWidget>
#include<QLineEdit>
#include<QTextEdit>
#include<QPushButton>
#include<QVBoxLayout>
#include<QString>
#include<QFileDialog>
#include <QDebug>
#include"UTProfiler.h"
#include "cursus.h"
#include"dossier.h"
#include"dossierGUI2.h"
#include "cursusGUI.h"



int main(int argc,char*argv[]) {
QApplication app(argc, argv);
<<<<<<< HEAD
MenuDebut fenetre;
fenetre.show();
=======

/*Debut fenetre;
fenetre.show();*/
try {
cursusManager& m=cursusManager::getInstance();
UVManager& u=UVManager::getInstance();
DossierManager& d=DossierManager::getInstance();
//QString chemin=QFileDialog::getOpenFileName(0,"Ouvrir un fichier de dossiers");
//d.load(chemin);

menuFormation* fenetre =new menuFormation(&m,&u);
fenetre->show();

//MenuDossier fenetre;
//fenetre.show();

}
catch(UTProfilerException& e){qDebug()<<e.getInfo(); exit(0);}
>>>>>>> f85b1c97d71dc8cd6e0f53086e4d3014dff8b897


return app.exec();
}
