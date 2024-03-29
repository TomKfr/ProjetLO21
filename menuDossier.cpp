#include"dossierGUI2.h"
#include"cursus.h"
#include"completionGUI.h"
#include"UTProfiler.h"
#include"dossier.h"
#include "completion.h"
#include<QDebug>
#include<sstream>

/*!
 * \brief Constructeur de la fenêtre de gestion des dossiers
 */
MenuDossier::MenuDossier() {
    this->setWindowTitle(QString("Opération choisie sur les dossiers ?"));
    dman=&DossierManager::getInstance();
    dossiers=new QComboBox(this);
    ajouter=new QPushButton("Ajouter", this);
    modifier=new QPushButton("Consulter/Modifier ce dossier", this);
    completion=new QPushButton("Completion automatique", this);
    numero=new QLabel("Dossier n° :", this);
    sup=new QPushButton("Supprimer", this);
    sauver=new QPushButton("Sauver les modifications",this);
    terminer=new QPushButton("Operation sur les dossiers terminee", this);

    coucheH0=new QHBoxLayout;
    coucheH0->addWidget(numero);

    coucheH=new QHBoxLayout;
    coucheH->addWidget(sup);
    coucheH->addWidget(ajouter);
    coucheH->addWidget(modifier);
    coucheH->addWidget(completion);
    coucheH->addWidget(sauver);
    coucheH->addWidget(terminer);

    coucheV=new QVBoxLayout;
    coucheV->addLayout(coucheH0);
    coucheV->addWidget(dossiers);
    coucheV->addLayout(coucheH);
    setLayout(coucheV);
    update();

    QObject::connect(ajouter, SIGNAL(clicked()), this, SLOT(ajout()));
    QObject::connect(sup, SIGNAL(clicked()), this, SLOT(suppression()));
    QObject::connect(modifier, SIGNAL(clicked()), this, SLOT(modif()));
    QObject::connect(sauver, SIGNAL(clicked()),this, SLOT(sauvegarder()));
    QObject::connect(terminer, SIGNAL(clicked()),this, SLOT(fin()));
    QObject::connect(completion, SIGNAL(clicked()),this, SLOT(calcul_completion()));

}
/*!
 * \brief Ouvre le menu de complétion automatique
 */
void MenuDossier::calcul_completion() {
    bool ok;
    QString n1=dossiers->currentText();
    unsigned int n2=n1.toInt(&ok);
    Dossier* d=dman->trouverDossier(n2);
    ChoixManager& cm=ChoixManager::getInstance();
    cm.load_completion();
    MenuCompletion*  fenetre=new MenuCompletion(d);
    fenetre->show();

}
/*!
 * \brief Ouvre le menu de création d'un dossier
 */
void MenuDossier::ajout() {
    bool ok;
    QString n1=dossiers->currentText();
    unsigned int n2=n1.toInt(&ok);

    Dossier* dos=dman->trouverDossier(n2);

    DossierAjout * fenetre= new DossierAjout(*dman,this, dos);
    fenetre->show();
}
/*!
 * \brief Ferme ce menu
 */
void MenuDossier::fin() {

    this->close();
}
/*!
 * \brief Ouvre la fenêtre de modification du dossier
 */
void MenuDossier::modif() {
    bool ok;
    QString n1=dossiers->currentText();
    unsigned int n2=n1.toInt(&ok);

    Dossier* dos=dman->trouverDossier(n2);
    ModifierDossier * fenetre= new ModifierDossier(*dman,dos, this);
    fenetre->show();
}
/*!
 * \brief Supprime le dossier sélectionné
 */
void MenuDossier::suppression() {
    bool ok;

    QString n1=dossiers->currentText();
    unsigned int n2=n1.toInt(&ok);
    supDossier(n2, *dman);

    update();

}
/*!
 * \brief Supprime le dossier sélectionné
 */
void MenuDossier::supDossier(unsigned int num, DossierManager& dm) {
    Dossier* dos=dm.trouverDossier(num);
    try{
        if (dos==0) {
            throw UTProfilerException(QString("erreur, DossierManager, Dossier ")+num+QString("non existant, suppression impossible"));
        }else{
            dm.removeDossier(dos);
        }
    }
    catch(UTProfilerException& e){QMessageBox::warning(0,"Erreur",e.getInfo());}
}
/*!
 * \brief Mets à jour les champs de la fenêtre
 */
void MenuDossier::update()
{
    dossiers->clear();
    for(iterateur<Dossier>& it=dman->getIterateurDos();!it.isDone();it.next())
    {
        dossiers->addItem(QString::number(it.courant()->getNumero()));
    }
}
/*!
 * \brief Lance la sauvegarde des dossiers
 */
void MenuDossier::sauvegarder()
{
    dman->save();
    QMessageBox::information(this,"sauvegarde","liste de dossiers enregistrée");
}




