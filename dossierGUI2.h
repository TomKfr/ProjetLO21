/// \file dossierGUI2.h
/// \brief Ce fichier contient les déclarations de classes d'objets qui permettent à l'utilisateur d'internvenir sur les paramètres des dossiers.

#ifndef DOSSIERGUI_H
#define DOSSIERGUI_H

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

class DossierManager;
class UV;
class Dossier;
class Equivalences;

/*!
 * \brief Menu de gestion des dossiers
 */
class MenuDossier : public QWidget {
    Q_OBJECT
    DossierManager* dman;
    QLabel * numero;
    QComboBox* dossiers;
    QPushButton* modifier;
    QPushButton* sup;
    QPushButton* sauver;
    QPushButton* terminer;
    QPushButton* ajouter;
    QPushButton* completion;
    QHBoxLayout* coucheH;
    QHBoxLayout* coucheH0;
    QVBoxLayout* coucheV;


public :
    MenuDossier();
    void update();

public slots:
    void ajout();
    void suppression();
    void supDossier(unsigned int num, DossierManager& dm);
    void modif();
    void fin();
    void calcul_completion();
    void sauvegarder();
};

/*!
 * \brief Fenêtre de création d'un nouveau dossier
 */
class DossierAjout : public QWidget{
    Q_OBJECT

    Dossier * dos;
    unsigned int nbUV;
    unsigned int nbMaxUV;
    DossierManager& M;
    MenuDossier* parent;
    QLineEdit* num;
    QLabel* numLabel;
    QLineEdit* nom;
    QLabel* nomLabel;
    QLineEdit* prenom;
    QLabel* prenomLabel;
    QComboBox* f;
    QLabel* formationLabel;
    QComboBox* fil;
    QLabel* filiereLabel;
    QLabel * semestreLabel;
    QSpinBox * semestre;

    QLabel* listeUVLabel;
    QLabel* Label;

    QPushButton* SelectUV;
    QPushButton* SelectEquivalences;
    QPushButton* sauver;
    QPushButton* quitter;

    QVBoxLayout * couche;
    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;
    QHBoxLayout* coucheH3;
    QHBoxLayout* coucheH4;
    QHBoxLayout* coucheH5;

public:
 DossierAjout(DossierManager& uvm, MenuDossier* p, Dossier* d);

 void ajouter_UV(UV* nouv);


public slots:
 void slot_ajoutDossier();
 void slot_selectUV();
 void update();
 void select_equivalences();
 void disable();
 void setrightFil();
};


/*!
 * \brief Fenêtre permettant d'ajouter des uvs réalisées dans un dossier.
 */
class AjoutUV : public QWidget {
    Q_OBJECT

    QComboBox * Liste;
    QComboBox * Result ;
    QLabel* LabelListe;
    QLabel* LabelResult;
    QPushButton * submit ;
    QPushButton * retour;

    QVBoxLayout * couche;
    QHBoxLayout* coucheH1;

    DossierAjout * DA;
    Dossier *dos;



public :
    AjoutUV(Dossier* d, DossierAjout* dossier=0);

public slots :
    void end_listeUV();
    void ajout_UVDossier();
    void update();

};

/*!
 * \brief Fenêtre permettant la modification d'un dossier
 */
class ModifierDossier : public QWidget
{
    Q_OBJECT
    DossierManager& M;
    Dossier* dos;
    MenuDossier * menu;

    QLineEdit* num;
    QLabel* numLabel;
    QLineEdit* nom;
    QLabel* nomLabel;
    QLineEdit* prenom;
    QLabel* prenomLabel;
    QLabel* formationLabel;
    QLabel* semestreLabel;
    QPushButton* modifUV;
    QPushButton* sauver;
    QPushButton* modifFormation;
    QPushButton* modifEquivalences;
    QSpinBox* numsem;
    QVBoxLayout * couche;
    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;
    QHBoxLayout* coucheH3;


public:
 ModifierDossier(DossierManager& uvm, Dossier * dos, MenuDossier * md);

public slots:
 void slot_modifFormation();
 void slot_modifUV();
 void slot_finModifDossier();
 void slot_modifEquivalences();

};

/*!
 * \brief Fenêtre permettant de modifier la formation d'un étudiant.
 */
class ModifFormation : public QWidget
{
    Q_OBJECT
    Dossier * dossier;
    QLabel * formationLabel;
    QComboBox* f;
    QLabel * filiereLabel;
    QComboBox* fil;
    QPushButton* valider;
    QVBoxLayout * couche;
    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;

public :
    ModifFormation(Dossier* d);

public slots :
   void enregistrer_formation();
   void update();
   void setrightFil();
};

/*!
 * \brief Fenêtre permettant de gérer les UVs d'un dossier.
 */
class ModifUV : public QWidget
{
    Q_OBJECT

    QPushButton* ajouter;
    QPushButton* supprimer;
    QPushButton* modifResultat;
    QPushButton* fin;
    QComboBox * uvs;
    QLabel * explication;
    QComboBox * resultats;
    QVBoxLayout * couche;
    QHBoxLayout* coucheH0;
    QHBoxLayout* coucheH1;
    Dossier* dos;

public :
    ModifUV(Dossier* d);

public slots :
   void ajouterUV();
   void supprimerUV();
   void finUV();
   void update();
   void modifierResult();
   void affResult();
};

/*!
 * \brief Fenêtre permettant de modifier le résultat obtenu à une UV.
 */
class ModifResult : public QWidget
{
    Q_OBJECT
    QLabel * explication;
    QComboBox * uvs;
    QComboBox * resultats;
    QPushButton* valider;
    QPushButton* retour;
    QVBoxLayout * couche;
    QHBoxLayout* coucheH0;
    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;
    Dossier* dos;
    ModifUV* modifuv;

public : ModifResult(Dossier* d, ModifUV* mu) ;

public slots :
    void update();
    void enregistrer();
    void fin2();
    void affResult();
};

/*!
 * \brief Fenêtre permettant de retirer une UV d'un dossier.
 */
class SuppressionUV : public QWidget
{
    Q_OBJECT
    QComboBox* liste;
    QPushButton* supprimer;
    QPushButton* fin;
    QVBoxLayout * couche;
    QHBoxLayout* coucheH1;
    Dossier* dos;

public :
    SuppressionUV(Dossier* d);
    void update();

public slots :
   void suppression_une_uv();
   void finSuppression();
};

/*!
 * \brief Fenêtre permettant de modifier les équvaleces associées à un dossier.
 */
class ModifEquivalences : public QWidget {
    Q_OBJECT

    Dossier * dossier;

    QComboBox* choix;
    QPushButton * valider ;
    QPushButton* ajouter;
    QPushButton* supprimer;
    QPushButton* quitter;

    QVBoxLayout * couche;
    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;
    QHBoxLayout* coucheH3;
    QHBoxLayout* coucheH4;
public :
    ModifEquivalences(Dossier * dos);

public slots :
    void slot_valider();
    void slot_quitter();
    void update();
    void slot_ajouter();
    void slot_supprimer();
};

/*!
 * \brief Fenêtre permettant d'ajouter des équivalences à un dossier.
 */
class AjoutEquivalences : public QWidget
{
    Q_OBJECT

    Dossier * dos;
    ModifEquivalences * me;
    QLabel * typeLabel;
    QComboBox * type ;
    QLabel * creditsLabel;
    QLineEdit * credits ;
    QLabel * descriptionLabel ;
    QLineEdit * description ;
    QPushButton * valider ;

    QVBoxLayout * couche;
    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;
    QHBoxLayout* coucheH3;

public :

    AjoutEquivalences(Dossier * d, ModifEquivalences * me=0) ;
public slots :
    void ajouter_equivalence();
};

/*!
 * \brief Fenêtre permettant de modifier une équivalence d'un dossier.
 */
class EquivalenceEditeur : public QWidget {

     Q_OBJECT

    Dossier * dos;
    Equivalences * eq;
    ModifEquivalences * me;

    QLabel * typeLabel;
    QComboBox * type ;
    QLabel * creditsLabel;
    QLineEdit * credits ;
    QLabel * descriptionLabel ;
    QLineEdit * description ;
    QPushButton * valider ;

    QVBoxLayout * couche;
    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;
    QHBoxLayout* coucheH3;

public :
    EquivalenceEditeur(Dossier * d, Equivalences * e, ModifEquivalences* m);
public slots :
    void modifier_equivalence();

};
#endif // DOSSIERGUI_H
