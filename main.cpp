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

try {
cursusManager& m=cursusManager::getInstance();
UVManager& u=UVManager::getInstance();
DossierManager& d=DossierManager::getInstance();

MenuDebut* fenetre=new MenuDebut();
fenetre->show();

/*Debut fenetre;
fenetre.show();*/

//QString chemin=QFileDialog::getOpenFileName(0,"Ouvrir un fichier de dossiers");
//d.load(chemin);

//menuFormation* fenetre =new menuFormation(&m,&u);
//fenetre->show();

//menuFiliere* f=new menuFiliere();
//f->show();

//MenuDossier fenetre;
//fenetre.show();

}
catch(UTProfilerException& e){qDebug()<<e.getInfo(); exit(0);}


return app.exec();
}
