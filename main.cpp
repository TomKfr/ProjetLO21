//#include"cursusGUI.h"
#include"menu.h"
#include "dossierGUI2.h"
#include"UTProfiler.h"
#include<QApplication>
#include<QDebug>

int main(int argc,char*argv[]) {
QApplication app(argc, argv);
try{
//MenuDebut* fenetre=new MenuDebut();
//fenetre->show();

MenuDossier* dos=new MenuDossier();
dos->show();

/*Debut fenetre;
fenetre.show();*/

//QString chemin=QFileDialog::getOpenFileName(0,"Ouvrir un fichier de dossiers");
//d.load(chemin);

//menuFormation* fenetre =new menuFormation();
//fenetre->show();

//menuFiliere* f=new menuFiliere();
//f->show();

//MenuDossier fenetre;
//fenetre.show();
}
catch(UTProfilerException e) {qDebug()<<e.getInfo();}

return app.exec();
}
