#ifndef MENU_H
#define MENU_H

#include<QWidget>
#include<QObject>
#include<QPushButton>
#include<QApplication>
#include<QWidget>
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
#include<QSpinBox>
#include<QMessageBox>

class cursusManager;
class UVManager;

class MenuDebut : public QWidget{
    Q_OBJECT

    QPushButton* op_UV;
    QPushButton* op_Dossiers;
    QPushButton* op_Formations;
    QPushButton* op_Filieres;
    QPushButton* no_op;

    QLabel* texte;

    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;
    QHBoxLayout* coucheH3;
    QHBoxLayout* coucheH4;
    QHBoxLayout* coucheH5;
    QHBoxLayout* coucheH6;

    QVBoxLayout* coucheV;

public :
    MenuDebut();


public slots:
    void lancer_UV();
    void lancer_Dossiers();
    void lancer_Formations();
    void lancer_Filieres();
    void lancer_rien();
};

#endif // MENU_H
