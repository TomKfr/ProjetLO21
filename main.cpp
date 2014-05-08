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
#include <QDebug>
#include "cursusGUI.h"


int main(int argc,char*argv[]) {
QApplication app(argc, argv);

/*Debut fenetre;
fenetre.show();*/
try{
cursusManager* m=new cursusManager();
UVManager& u=UVManager::getInstance();

menuFormation* fenetre =new menuFormation(m,&u);
fenetre->show();
}
catch(UTProfilerException& e) {QMessageBox::warning(0,"Erreur",e.getInfo(),QMessageBox::Ok); exit(1);}

return app.exec();
}
