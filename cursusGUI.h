#ifndef CURSUSGUI_H
#define CURSUSGUI_H

#include <QString>
#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QTextEdit>

class cursusManager;
class UVManager;
class UV;
class filiere;
class formation;

/*!
 * \brief Affiche le menu de gestion des formations.
 *
 * Cette classe-fenêtre permet d'afficher le menu de gestion des formations dans le lequel l'utilisateur peut
 * soit ajouter une nouvelle formation, soit en choisir une existante et la supprimer ou la modifier.
 */
class menuFormation : public QWidget
{
    Q_OBJECT
    cursusManager* m;
    UVManager* uvman;
    QVBoxLayout* mainbox;
    QHBoxLayout* hbox1;
    QHBoxLayout* hbox2;
    QLabel* titre;
    QComboBox* select;
    QPushButton* visualiser;
    QPushButton* ajouter;
    QPushButton* modifier;
    QPushButton* fil;
    QPushButton* ajfil;
    QPushButton* supprimer;
    QPushButton* quit;
    QPushButton* sauver;

public:
    menuFormation();

public slots:
    void voir();
    void ajout();
    void modif();
    void filir();
    void ajfilir();
    void suppr();
    void update();
    void save();
};

/*!
 * \brief Affiche la fenêtre d'ajout d'une formation.
 */
class ajoutFormation : public QWidget {
    Q_OBJECT
    cursusManager* man;
    menuFormation* parent;
    QVBoxLayout* mainbox;
    QHBoxLayout* hbox1;
    QHBoxLayout* hbox2;
    QHBoxLayout* hbox3;
    QHBoxLayout* hbox4;
    QLabel* lbl1;
    QLabel* lbl2;
    QLabel* lbl3;
    QLabel* lblcs;
    QLabel* lbltm;
    QLabel* lbltsh;
    QLineEdit* nom;
    QSpinBox* credits;
    QSpinBox* creditscs;
    QSpinBox* creditstm;
    QSpinBox* creditstsh;
    QSpinBox* semstr;
    QPushButton* valider;


public :
    ajoutFormation(cursusManager *m, menuFormation* p);

public slots:
    void ajout();
};


/*!
 * \brief Affiche la fenêtre permettant de modifier une formation.
 */
class modifFormation : public QWidget {
    Q_OBJECT
    cursusManager* man;
    menuFormation* parent;
    formation* form;
    QVBoxLayout* mainbox;
    QHBoxLayout* hbox1;
    QHBoxLayout* hbox2;
    QHBoxLayout* hbox3;
    QHBoxLayout* hbox4;
    QLabel* lbl1;
    QLabel* lbl2;
    QLabel* lbl3;
    QLabel* lblcs;
    QLabel* lbltm;
    QLabel* lbltsh;
    QLineEdit* nom;
    QSpinBox* credits;
    QSpinBox* creditscs;
    QSpinBox* creditstm;
    QSpinBox* creditstsh;
    QSpinBox* semstr;
    QPushButton* valider;


public :
    modifFormation(cursusManager *m, menuFormation* p, formation* f);

public slots:
    void modif();
};


/*!
 * \brief Affiche la fenêtre de gestion d'une formation.
 *
 * Cette fenêtre permet de visualiser les détail d'une formation, et de gérer les UVs qui en font partie.
 */
class visualiserFormation : public QWidget
{
    Q_OBJECT
    cursusManager* cman;
    UVManager* uman;
    formation* objet;
    QHBoxLayout* mainbox;
    QVBoxLayout* vbox1;
    QVBoxLayout* vbox2;
    QHBoxLayout* hbox1;
    QHBoxLayout* hbox2;
    QHBoxLayout* hbox3;
    QVBoxLayout* vbox3;
    QLabel* form;
    QLabel* cred;
    QLabel* semstr;
    QLabel* lbluvs;
    QTextEdit* uvs;
    QLabel* ccs;
    QLabel* ctm;
    QLabel* ctsh;
    QComboBox* supprUV;
    QPushButton* retour;
    QPushButton* modif;
    QPushButton* suppr;

public:
    visualiserFormation(cursusManager* cmanager, UVManager* umanager, formation* f);
public slots:
    void moduvs();
    void update();
    void supprimer();

};

/*!
 * \brief Fenêtre de gestion des UVs pour une formation particulière.
 */
class selectUVsFormation : public QWidget
{
    Q_OBJECT
    cursusManager* cman;
    UVManager* uman;
    formation* objet;
    visualiserFormation* parent;
    QVBoxLayout* mainbox;
    QLabel* label1;
    QComboBox* choix;
    QPushButton* retour;
    QPushButton* ajouter;
    QCheckBox* required;

public:
    selectUVsFormation(cursusManager* cm, UVManager* um, formation* f, visualiserFormation* p);
public slots:
    void ajouterUV();
    void update();

};


// ////////////////////// fin formations ////////////////////////

/*!
 * \brief Fenêtre de gestion des filières inscrites dans une formation.
 */
class GestionFiliereFormation : public QWidget
{
    Q_OBJECT
    UVManager& uman;
    cursusManager& cman;
    formation* objet;
    //menuFiliere* parent;
    QVBoxLayout* mainbox;
    QHBoxLayout* hbox1;
    QVBoxLayout* vbox1;
    QVBoxLayout* vbox2;
    QLabel* lbl1;
    QLabel* lbl2;
    QLabel* lbl3;
    QComboBox* ajt;
    QComboBox* suppr;
    QPushButton* retour;
    QPushButton* ajouter;
    QPushButton* supprimer;

public:
    GestionFiliereFormation(formation* f);
public slots:
    void ajouterFiliere();
    void update();
    void supprimerFiliere();
};


/*!
 * \brief Menu de gestion des filières.
 *
 * Cette classe-fenêtre permet d'afficher le menu de gestion des filières dans le lequel l'utilisateur peut
 * soit ajouter une nouvelle filière, soit en choisir une existante et la supprimer ou la modifier.
 */
class menuFiliere : public QWidget
{
    Q_OBJECT
    cursusManager* m;
    UVManager* uvman;
    QVBoxLayout* mainbox;
    QHBoxLayout* hbox1;
    QHBoxLayout* hbox2;
    QLabel* titre;
    QComboBox* select;
    QPushButton* visualiser;
    QPushButton* ajouter;
    QPushButton* modifier;
    QPushButton* supprimer;
    QPushButton* quit;
    QPushButton* sauver;

public:
    menuFiliere();

public slots:
    void voir();
    void ajout();
    void modif();
    void suppr();
    void update();
    void save();
};

/*!
 * \brief Fenêtre permettant de créer une nouvelle filière.
 */
class ajoutFiliere: public QWidget {
    Q_OBJECT
    menuFiliere* parent;
    QVBoxLayout* mainbox;
    QHBoxLayout* hbox1;
    QHBoxLayout* hbox2;
    QHBoxLayout* hbox3;
    QLabel* lbl1;
    QLabel* lbl2;
    QLineEdit* nom;
    QSpinBox* credits;
    QPushButton* valider;

public :
    ajoutFiliere(menuFiliere* p);

public slots:
    void ajout();
};

/*!
 * \brief Fenêtre permettant de visualiser les détail d'une filière et de gérer les UVs qui en font partie.
 */
class visualiserFiliere : public QWidget
{
    Q_OBJECT
    filiere* objet;
    QHBoxLayout* mainbox;
    QVBoxLayout* vbox1;
    QVBoxLayout* vbox2;
    QHBoxLayout* hbox1;
    QHBoxLayout* hbox2;
    QHBoxLayout* hbox3;
    QLabel* form;
    QLabel* cred;
    QLabel* lbluvs;
    QLabel* uvs;
    QComboBox* supprUV;
    QPushButton* retour;
    QPushButton* modif;
    QPushButton* suppr;

public:
    visualiserFiliere(filiere* f);
public slots:
    void moduvs();
    void update();
    void supprimer();
};

/*!
 * \brief Fenêtre permettant de modifier les caractéristiques d'une filière.
 */
class modifFiliere : public QWidget {
    Q_OBJECT
    menuFiliere* parent;
    filiere* fil;
    QVBoxLayout* mainbox;
    QHBoxLayout* hbox1;
    QHBoxLayout* hbox2;
    QHBoxLayout* hbox3;
    QLabel* lbl1;
    QLabel* lbl2;
    QLineEdit* nom;
    QSpinBox* credits;
    QPushButton* valider;

public :
    modifFiliere(menuFiliere* p, filiere* f);

public slots:
    void modif();
};

/*!
 * \brief Fenêtre permettant de gérer les UVs inscrites dans une filière.
 */
class selectUVsFiliere : public QWidget
{
    Q_OBJECT
    cursusManager& cman;
    UVManager& uman;
    filiere* objet;
    visualiserFiliere* parent;
    QVBoxLayout* mainbox;
    QLabel* label1;
    QComboBox* choix;
    QPushButton* retour;
    QPushButton* ajouter;

public:
    selectUVsFiliere(filiere* f, visualiserFiliere* p);
public slots:
    void ajouterUV();
    void update();
};

#endif // CURSUSGUI_H
