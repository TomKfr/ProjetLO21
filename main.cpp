#include"menu.h"
#include"cursusGUI.h"
#include"UTProfiler.h"
#include<QApplication>
#include<QDebug>

int main(int argc,char*argv[]) {
QApplication app(argc, argv);

MenuDebut* fenetre=new MenuDebut();
fenetre->show();

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


return app.exec();
}
