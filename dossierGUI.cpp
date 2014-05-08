#include"dossierGUI.h"
#include"UTProfiler.h"
#include"dossier.h"
#include<QDebug>



DebutDossier::DebutDossier() {

    this->setWindowTitle(QString("Opération choisie sur les dossiers ?"));

    ajouter=new QPushButton("Ajouter", this);
    modifier=new QPushButton("Consulter/Modifier des informations", this);
    sup=new QPushButton("Supprimer", this);

    coucheH=new QHBoxLayout;
    coucheH->addWidget(sup);
    coucheH->addWidget(ajouter);
    coucheH->addWidget(modifier);

    coucheV=new QVBoxLayout;
    coucheV->addLayout(coucheH);
    setLayout(coucheV);

    QObject::connect(ajouter, SIGNAL(clicked()), this, SLOT(ajout()));
    QObject::connect(sup, SIGNAL(clicked()), this, SLOT(suppression()));
    QObject::connect(modifier, SIGNAL(clicked()), this, SLOT(modif()));

}




DossierModif::DossierModif(DossierManager& m) : M(m) {

    codeLabel=new QLabel("Numero de dossier", this);
    code= new QLineEdit("", this);
    submit=new QPushButton("Modifier ce dossier", this);

    coucheH=new QHBoxLayout;
    coucheH->addWidget(codeLabel);
    coucheH->addWidget(code);
    coucheH->addWidget(submit);

    coucheV=new QVBoxLayout;
    coucheV->addLayout(coucheH);
    setLayout(coucheV);

    QObject::connect(submit, SIGNAL(clicked()), this, SLOT(modifDossier()));

}


void DossierModif::modifDossier(){

    DossierManager& mana=DossierManager::getInstance();
    DossierEditeur * fenetre= new DossierEditeur(*(mana.trouverDossier(numero->text())), mana);
    fenetre->show();

}


void DebutDossier::ajout() {

    DossierManager& mana=DossierManager::getInstance();
    QString chemin = QFileDialog::getOpenFileName();
    try {
        mana.load(chemin);
    }
    catch (UTProfilerException e) {qDebug()<<e.getInfo();}

    DossierAjout * fenetre= new DossierAjout(mana);
    fenetre->show();
}


DossierEditeur::DossierEditeur(Dossier& dossierToEdit, DossierManager& dosm, QWidget* parent) : QWidget(parent), dos(uvToEdit), M(dosm) {

    this->setWindowTitle(QString("Edition du Dossier")+dos.getNumero());
    numLabel=new QLabel("numero", this);
    nomLabel=new QLabel("nom", this);
    prenomLabel=new QLabel("prenom", this);
    formationLabel=new QLabel("formation", this);
    listeUVLabel=new QLabel("liste d'UV", this);


    num= new QLineEdit(uv.getNumero(), this);
    nom=new QTextEdit(uv.getNom(), this);
    prenom=new QTextEdit(uv.getPrenom(), this);
    formation=new QSpinBox(this);
    /*credits->setRange(1,8);
    credits->setValue(uv.getNbCredits());*/

    sauver=new QPushButton("Sauver", this);
    annuler=new QPushButton("Annuler", this);
    //on cree plusieurs couches horizontales qu'on superpose ensuite en une couche veerticale
    coucheH1=new QHBoxLayout;
    coucheH1->addWidget(numLabel);
    coucheH1->addWidget(num);
    coucheH1->addWidget(nomLabel);
    coucheH1->addWidget(nom);
    coucheH1->addWidget(prenomLabel);
    coucheH1->addWidget(prenom);

    coucheH2=new QHBoxLayout;
    coucheH2->addWidget(formationLabel);
    coucheH2->addWidget(formation);

    coucheH3=new QHBoxLayout;


    coucheH4=new QHBoxLayout;
    coucheH4->addWidget(annuler);
    coucheH4->addWidget(sauver);

    couche=new QVBoxLayout;

    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);
    couche->addLayout(coucheH4);

    setLayout(couche);

    //bouton desactive par defaut
    //sauver->setEnabled(false);

   QObject::connect(sauver, SIGNAL(clicked()), this, SLOT(sauverDossier()));

   //pour que ça sactive que si modif :
  // QObject::connect(code, SIGNAL(textEdited(QString)), this, SLOT(activerSauverUV(QString)));


}


void DossierEditeur::sauverDossier() {
    dos.setNumero(num->text());  //modification du texte avec ce qu'à rentré l'utilisateur dans la QlineEdit
    dos.setNom(nom->text());
    dos.setPrenom(prenom->text());//on utilise des methodes accesseurs des classes QXXXX pour mettre les bonnes valeurs dans uv via les methodes set de uv
    dos.setFormation(formation->value());
    //dos.setListeUV();
    QMessageBox::information(this, "sauvegarde", "Dossier sauvegarde");
}


/*void UVEditeur::activerSauver(QString s){
    sauver->setEnabled(true); //une modification entraine une activation du bouton sauver
}*/

DossierSuppression::DossierSuppression(DossierManager& dm) : M(dm) {

    numLabel=new QLabel("numero de dossier", this);
    code2= new QLineEdit("", this);
    submit=new QPushButton("Supprimer ce Dossier", this);

    coucheH=new QHBoxLayout;
    coucheH->addWidget(codeLabel);
    coucheH->addWidget(code2);
    coucheH->addWidget(submit);

    coucheV=new QVBoxLayout;
    coucheV->addLayout(coucheH);
    setLayout(coucheV);

    QObject::connect(submit, SIGNAL(clicked()), this, SLOT(supprDossier()));

}

void DossierSuppression::supprDossier() {

    QMessageBox::information(this, "sauvegarde", "exec de suppression");

    try {

    M.supprimerDossier(code2->text()); } //il faut indiquer de quel UVManager il s'agit

    catch (UTProfilerException e) {qDebug()<<code2->text()<<e.getInfo();}

    QMessageBox::information(this, "sauvegarde", "Dossier supprime");
}



DossierAjout::DossierAjout(DossierManager& dm) : M(dm) {

    this->setWindowTitle(QString("Ajout d'un Dossier"));

    numLabel=new QLabel("num", this);
    nomLabel=new QLabel("nom", this);
    prenomLabel=new QLabel("prenom", this);
    formationLabel=new QLabel("formation", this);
    listeUVLabel=new QLabel("liste UV", this);

    num= new QLineEdit("", this);
    nom= new QLineEdit("", this);
    prenom= new QLineEdit("", this);

    formation=new QSpinBox(this);
    /*credits->setRange(1,8);
    credits->setValue(1);*/

    /*categorie=new QComboBox(this);
    categorie->addItem("CS");
    categorie->addItem("TM");
    categorie->addItem("SP");
    categorie->addItem("TSH");
    categorie->setCurrentIndex(0);*/

    sauver=new QPushButton("Sauver", this);
    annuler=new QPushButton("Annuler", this);

    //on cree plusieurs couches horizontales qu'on superpose ensuite en une couche veerticale
    coucheH1=new QHBoxLayout;
    coucheH1->addWidget(codeLabel);
    coucheH1->addWidget(code);
    coucheH1->addWidget(categorieLabel);
    coucheH1->addWidget(categorie);
    coucheH1->addWidget(creditsLabel);
    coucheH1->addWidget(credits);

    coucheH2=new QHBoxLayout;
    coucheH2->addWidget(titreLabel);
    coucheH2->addWidget(titre);

    coucheH3=new QHBoxLayout;
    coucheH3->addWidget(ouvertureLabel);
    coucheH3->addWidget(automne);
    coucheH3->addWidget(printemps);

    coucheH4=new QHBoxLayout;
    coucheH4->addWidget(annuler);
    coucheH4->addWidget(sauver);

    couche=new QVBoxLayout;

    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);
    couche->addLayout(coucheH4);

    setLayout(couche);

    //bouton desactive par defaut
    //sauver->setEnabled(false);

   QObject::connect(sauver, SIGNAL(clicked()), this, SLOT(slot_ajoutDossier()));

   //pour que ça sactive que si modif :
   //QObject::connect(code, SIGNAL(textEdited(QString)), this, SLOT(activerSauverUV(QString)));
}

void DossierAjout::slot_ajoutDossier() {

    M.ajouterDossier(num->text(), nom->text() , prenom->text(), formation->value());
    //void ajouterUV(const QString& c, const QString& t, unsigned int nbc, Categorie cat, bool a, bool p);
    QMessageBox::information(this, "sauvegarde", "Dossier sauvegardee");
}


void DebutDossier::suppression() { //lancement de la fenetre de suppression pour rentrer le code

    DossierManager& m=DossierManager::getInstance();
    QString chemin = QFileDialog::getOpenFileName();
    try {
        m.load(chemin);
    }
    catch (UTProfilerException e) {qDebug()<<e.getInfo();}

    DossierSuppression * fenetre = new DossierSuppression(m);
    fenetre->show();
}


void DebutDossier::modif() {

    DossierManager& m=DossierManager::getInstance();
    QString chemin = QFileDialog::getOpenFileName();
    try {
        m.load(chemin);
    }
    catch (UTProfilerException e) {qDebug()<<e.getInfo();}

    DossierModif * fenetre = new DossierModif(m);
    fenetre->show();

}

