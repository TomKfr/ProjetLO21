#ifndef COMPLETIONGUI_H
#define COMPLETIONGUI_H

#include <iostream>
#include <QString>
#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QComboBox>
#include <QRadioButton>

class souhaits;
class Dossier;

class MenuCompletion : public QWidget{





};

class MenuSouhaits : public QWidget
{
    Q_OBJECT
    souhaits *objet;
    Dossier* dos;

    QVBoxLayout *mainbox;
    QHBoxLayout *hbox1;
    QHBoxLayout *hbox2;
    QHBoxLayout *hbox3;
    QVBoxLayout *vbox1;
    QHBoxLayout *hbox4;
    QVBoxLayout *vbox2;
    QVBoxLayout *vbox3;
    QVBoxLayout *vbox4;
    QLabel *titre;

    QLabel *lblneutre;
    QComboBox *choix1;
    QRadioButton *exigeebutton;
    QRadioButton *prefereebutton;
    QRadioButton *rejeteebutton;
    QPushButton *valider1;

    QLabel *txtexigees;
    QLabel *listexigees;
    QComboBox *choix2;
    QPushButton *supprexigee;

    QLabel *txtpreferees;
    QLabel *listpreferees;
    QComboBox *choix3;
    QPushButton *supprpreferee;

    QLabel *txtrejetees;
    QLabel *listrejetees;
    QComboBox *choix4;
    QPushButton *supprrejetee;

    QPushButton *sauver;
    QPushButton *terminer;

public:
    MenuSouhaits(souhaits* sht);
    void update();

public slots:
    void ajUV();
    void suprexigee();
    void suprpref();
    void suprrejet();
    void save();

};

#endif // COMPLETIONGUI_H
