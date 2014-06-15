/// \file uvGUI.h
/// \brief Fichier contenant les classes nécessaires à l'interface graphique de
///  de gestion des UVs dans l'application.

#ifndef UVEDITEUR_H
#define UVEDITEUR_H

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

class UVManager;
class UV;

/*!
 * \brief Fenêtre menu de gestion des UVs
 */
class Debut : public QWidget {
    Q_OBJECT
    QComboBox * liste;
    QPushButton* modifier;
    QPushButton* sup;
    QPushButton* ajouter;
    QPushButton * consulter;
    QPushButton * terminer;
    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;
    QVBoxLayout* coucheV;


public :
    Debut();

public slots:
    void ajout();
    void suppression();
    void afficher();
    void modif();
    void fin();
    void update();
};


/*!
 * \brief Fenêtre de création d'une UV
 */
class UVAjout : public QWidget{
    Q_OBJECT

    Debut * parent;
    UVManager& M;

    QLineEdit* code;
    QLabel* codeLabel;
    QTextEdit* titre;
    QLabel* titreLabel;
    QSpinBox* credits;
    QLabel* creditsLabel;
    QComboBox* categorie;
    QLabel* categorieLabel;
    QLabel* ouvertureLabel;
    QCheckBox* automne;
    QCheckBox* printemps;
    QPushButton* sauver;
    QPushButton* annuler;

    QVBoxLayout * couche;
    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;
    QHBoxLayout* coucheH3;
    QHBoxLayout* coucheH4;

public:
 UVAjout(UVManager & uvm, Debut* p);
public slots:
 void slot_ajoutUV();

};

/*!
 * \brief Fenêtre permettant la modification d'une UV existante.
 */
class UVEditeur : public QWidget {
    Q_OBJECT
    UV& uv;
    UVManager& M;

       QLineEdit* code;
       QLabel* codeLabel;
       QTextEdit* titre;
       QLabel* titreLabel;
       QSpinBox* credits;
       QLabel* creditsLabel;
       QComboBox* categorie;
       QLabel* categorieLabel;
       QLabel* ouvertureLabel;
       QCheckBox* automne;
       QCheckBox* printemps;
       QPushButton* sauver;
       QPushButton* annuler;

       QVBoxLayout * couche;
       QHBoxLayout* coucheH1;
       QHBoxLayout* coucheH2;
       QHBoxLayout* coucheH3;
       QHBoxLayout* coucheH4;

public:
    UVEditeur(UV& u, UVManager & uvm, QWidget* parent=0);
public slots:
    void sauverUV();
};

/*!
 * \brief Fenêtre permettant de visualiser les caractéristiques d'une UV.
 */
class UvAfficheur : public QWidget {
    Q_OBJECT
    UV& uv;
    UVManager& M;

       QLabel* codeLabel;
       QLabel* titreLabel;
       QLabel* creditsLabel;
       QLabel* categorieLabel;
       QLabel* ouverturePLabel;
       QLabel* ouvertureALabel;
       QPushButton* fin;

       QVBoxLayout * couche;
       QHBoxLayout* coucheH1;
       QHBoxLayout* coucheH2;
       QHBoxLayout* coucheH3;
       QHBoxLayout* coucheH4;
       QHBoxLayout* coucheH5;
       QHBoxLayout* coucheH6;

public:
    UvAfficheur(UV& u, UVManager & uvm);
public slots:
    void termine();
};

#endif // UVEDITEUR_H
