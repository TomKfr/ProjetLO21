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
#include"dossierGUI.h"
#include <QDebug>
#include "cursusGUI.h"


int main(int argc,char*argv[]) {
QApplication app(argc, argv);

/*Debut fenetre;
fenetre.show();*/
<<<<<<< HEAD

cursusManager& m=cursusManager::getInstance();
UVManager& u=UVManager::getInstance();
m.chargerCursus();
QString chemin=QFileDialog::getOpenFileName(0,"Ouvrir un fichier d'Uvs");
u.load(chemin);
/*
menuFormation* fenetre =new menuFormation(m,&u);
fenetre->show();*/

DebutDossier fenetre;
fenetre.show();

=======
try{
cursusManager* m=new cursusManager();
UVManager& u=UVManager::getInstance();

menuFormation* fenetre =new menuFormation(m,&u);
fenetre->show();
}
catch(UTProfilerException& e) {QMessageBox::warning(0,"Erreur",e.getInfo(),QMessageBox::Ok); exit(1);}
>>>>>>> enregistrement_formations

return app.exec();
}
