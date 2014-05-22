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


MenuDebut* fenetre=new MenuDebut();
fenetre->show();



return app.exec();
}
