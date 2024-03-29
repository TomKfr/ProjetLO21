///\file completionGUI.h
/// \brief Ce fichier contient les déclarations des classes d'objets gérant l'interface graphique de la fonctionnalité de
/// complétion automatique d'un cursus.

#ifndef COMPLETIONGUI_H
#define COMPLETIONGUI_H

#include"dossier.h"
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

/*!
 * \brief Fenêtre d'acceuil de la partie complétion, elle permet de lancer le calcul d'une solution et de consulter celles précédemment calculées.
 */
class MenuCompletion : public QWidget{

     Q_OBJECT

    QPushButton* historique ;
    QPushButton* souhaits ;
    QPushButton* previsions ;
    QPushButton* terminer;
    QPushButton* calcul;

    Dossier* dos;
    QHBoxLayout *coucheH1;
    QHBoxLayout *coucheH2;
    QHBoxLayout *coucheH3;
    QHBoxLayout *coucheH4;

    QVBoxLayout *couche;


public : MenuCompletion(Dossier* dos);
public slots :
    void consulter_historique();
    void lancer_completion();
    void saisir_souhaits();
    void saisir_previsions();
    void fin();

};
/*!
 * \brief Fenêtre d'affichage d'une proposition.
 */
class Proposition : public QWidget {
Q_OBJECT
    //affiche toutes les propositions et demande la réponse

    Dossier * d;
    QLabel * semestreLabel;
    QComboBox * saison_concernee ;
    QComboBox * annee_concernee ;
    QPushButton * afficher; //affiche pour un semestre
    QLabel * reponseLabel;
    QComboBox * reponse;

    QPushButton * terminer;



    QVBoxLayout *couche;
    QHBoxLayout *coucheH1;
    QHBoxLayout *coucheH2;
    QHBoxLayout *coucheH3;

public : Proposition(Dossier * dos) ;
    bool verifierValiditeSemestre(Semestre s, ChoixAppli * c);
public slots :
    void afficher_proposition();
    void enregistrer_reponse();

};
/*!
 * \brief Classe dont les objets permettent d'afficher les détails d'unbe proposition à l'écran.
 */
class AfficherProposition : public QWidget {
    Q_OBJECT

    QLabel * blabla ;
    QLabel * credits ;
    QLabel * uvs ;
    QPushButton * terminer;
    ChoixAppliSemestre * c;


   QVBoxLayout *couche;
   QHBoxLayout *coucheH1;
   QHBoxLayout *coucheH2;
   QHBoxLayout *coucheH3;
   QHBoxLayout *coucheH4;

public :
   AfficherProposition(ChoixAppliSemestre * choix);

public slots :
   void fin() ;


};
/*!
 * \brief Menu permettant à l'utilisateur de saisir un éventuel semestre à l'étranger prévu.
 */
class menuprevision : public QWidget
{
    Q_OBJECT
    Dossier* dos;
    QVBoxLayout *mainbox;
    QHBoxLayout *hbox1;
    QHBoxLayout *hbox2;
    QHBoxLayout *hbox3;
    QVBoxLayout *vbox1;
    QVBoxLayout *vbox2;
    QVBoxLayout *vbox3;

    QLabel* lbldest;
    QLabel* lblcs;
    QLabel* lbltm;
    QLabel* lbltsh;

    QLineEdit* destination;

    QSpinBox* bornesupCS;
    QSpinBox* borneinfCS;
    QSpinBox* bornesupTM;
    QSpinBox* borneinfTM;
    QSpinBox* bornesupTSH;
    QSpinBox* borneinfTSH;

    QPushButton* valider;
    QPushButton* annuler;

public:
    menuprevision(Dossier* d);
    void update();

public slots:
    void valider_prev();
};
/*!
 * \brief Menu permettant de saisir les souhaits d'UVs de l'étudiant.
 */
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
    MenuSouhaits(Dossier* d, souhaits* sht);
    void update();

public slots:
    void ajUV();
    void suprexigee();
    void suprpref();
    void suprrejet();
    void fermer();
};
/*!
 * \brief Fenêtre permettant d'afficher l'historiques des propositions.
 */
class Historique : public QWidget {

Q_OBJECT

    QLabel * intitule;
    QLabel* contenu ;
    QPushButton * retour ;

    QVBoxLayout *couche;
    QHBoxLayout *coucheH1;
    QHBoxLayout *coucheH2;
    QHBoxLayout *coucheH3;

    Dossier * dos;

public : Historique(Dossier * d);
public slots : void fin();

};

#endif // COMPLETIONGUI_H
