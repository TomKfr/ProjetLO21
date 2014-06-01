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

class MenuDossier : public QWidget {
    Q_OBJECT
    DossierManager* dman;
    QLabel * numero;
    QComboBox* dossiers;
    //QPushButton* visu;
    QPushButton* modifier;
    QPushButton* sup;
    QPushButton* souhaits;
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
    void menusouhaits();
    void sauvegarder();
};

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
    QLabel * semestreLabel;
    QSpinBox * semestre;

    QLabel* listeUVLabel;
    QLabel* Label;

    QPushButton* SelectUV;
    QPushButton* SelectEquivalences;
    QPushButton* sauver;

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
};



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

class ModifFormation : public QWidget
{
    Q_OBJECT
    Dossier * dossier;
    QLabel * formationLabel;
    QComboBox* f;
    QPushButton* valider;
    QVBoxLayout * couche;
    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;

public :
    ModifFormation(Dossier* d);

public slots :
   void enregistrer_formation();
   void update();


};

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
};

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
    void update(); //avec que les uvs et les resultats du dossier
    void enregistrer();
    void fin2();


};

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
