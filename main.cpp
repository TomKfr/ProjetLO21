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

cursusManager* m=new cursusManager();
UVManager& u=UVManager::getInstance();

menuFormation* fenetre =new menuFormation(m,&u);
fenetre->show();


return app.exec();

}
