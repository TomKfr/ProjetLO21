#include"dossierGUI2.h"
#include"UTProfiler.h"
#include"dossier.h"
#include<QDebug>
#include<sstream>


MenuDossier::MenuDossier() {

    this->setWindowTitle(QString("Opération choisie sur les dossiers ?"));
    dman=&DossierManager::getInstance();
    dossiers=new QComboBox(this);
    //visu=new QPushButton("Visualiser dossier",this);
    ajouter=new QPushButton("Ajouter", this);
    modifier=new QPushButton("Consulter/Modifier ce dossier", this);
    numero=new QLabel("Dossier n° :", this);
    sup=new QPushButton("Supprimer", this);
    sauver=new QPushButton("Sauver les modifications",this);
    terminer=new QPushButton("Operation sur les dossiers terminee", this);

    coucheH0=new QHBoxLayout;
    coucheH0->addWidget(numero);

    coucheH=new QHBoxLayout;
    //coucheH->addWidget(visu);
    coucheH->addWidget(sup);
    coucheH->addWidget(ajouter);
    coucheH->addWidget(modifier);
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
    //QObject::connect(visu,SIGNAL(clicked()),this,SLOT(visualiser()));
    QObject::connect(sauver, SIGNAL(clicked()),this, SLOT(sauvegarder()));
    QObject::connect(terminer, SIGNAL(clicked()),this, SLOT(fin()));

}

void MenuDossier::ajout() {
    DossierAjout * fenetre= new DossierAjout(*dman,this);
    fenetre->show();
}

void MenuDossier::fin() {
    this->close();
}

void MenuDossier::modif() {
    bool ok;
    QString n1=dossiers->currentText();
    unsigned int n2=n1.toInt(&ok);

    Dossier* dos=dman->trouverDossier(n2);
    ModifierDossier * fenetre= new ModifierDossier(*dman,dos, this);
    fenetre->show();
}

void MenuDossier::suppression() {
    bool ok;

    QString n1=dossiers->currentText();
    unsigned int n2=n1.toInt(&ok);
    supDossier(n2, *dman);

    update();

}

void MenuDossier::supDossier(unsigned int num, DossierManager& dm) {
    Dossier* dos=dm.trouverDossier(num);

    if (dos==0) {
        throw UTProfilerException(QString("erreur, DossierManager, Dossier ")+num+QString("non existant, suppression impossible"));
    }else{
    dm.removeDossier(dos);
    }

}



DossierAjout::DossierAjout(DossierManager& dm, MenuDossier* p) :  nbUV(0), nbMaxUV(0), M(dm),parent(p) {

    this->setWindowTitle(QString("Ajout d'un Dossier"));

    numLabel=new QLabel("numero de dossier", this);
    nomLabel=new QLabel("nom de l'etudiant", this);
    prenomLabel=new QLabel("prenom de l'etudiant", this);
    formationLabel=new QLabel("formation suivie", this);
    SelectUV= new QPushButton("2 - Remplir la liste des UVs");
    sauver=new QPushButton("1 - Sauver", this);

    num= new QLineEdit("", this);
    nom= new QLineEdit("", this);
    prenom= new QLineEdit("", this);

    f=new QComboBox(this);

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
    coucheH2->addWidget(f);

    coucheH3=new QHBoxLayout;
    coucheH3->addWidget(SelectUV);

    coucheH4=new QHBoxLayout;
    coucheH4->addWidget(sauver);

    couche=new QVBoxLayout;

    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH4);
    couche->addLayout(coucheH3);

    setLayout(couche);

    QMessageBox::warning(this, "Attention", "Sauvegarder le dossier avant d'y ajouter des UVs !",QMessageBox::Ok);

   QObject::connect(sauver, SIGNAL(clicked()), this, SLOT(slot_ajoutDossier()));
   QObject::connect(SelectUV, SIGNAL(clicked()), this, SLOT(slot_selectUV()));


   update();

}

void DossierAjout::slot_ajoutDossier() {

    bool ok;

    unsigned int n=num->text().toInt(&ok);
    const QString& name=nom->text();
    const QString& fn=prenom->text();
    const QString& F=f->currentText();

    M.ajouterDossier(n, name , fn, F);


    QMessageBox::information(this, "sauvegarde", "Dossier sauvegarde");
    parent->update();
}


void DossierAjout::slot_selectUV() {
    bool ok;
    unsigned int n=num->text().toInt(&ok);
    Dossier* d=M.trouverDossier(n);

    AjoutUV* fenetre= new AjoutUV(d, this);
    fenetre->show();
}

AjoutUV::AjoutUV(Dossier*d, DossierAjout* dossier) {
    DA=dossier;
    dos=d;

    Liste = new QComboBox(this);
    LabelListe= new QLabel("Sélectionnez l'UV ", this);
    LabelResult= new QLabel("Resultat : ", this);
    Result= new QComboBox(this);
    Result->addItem("A");
    Result->addItem("B");
    Result->addItem("C");
    Result->addItem("D");
    Result->addItem("E");
    Result->addItem("F");
    Result->addItem("FX");
    Result->addItem("En cours");
    submit=new QPushButton("Ajouter cette UV a la liste", this);
    retour=new QPushButton("J'ai saisi toutes les UVs : retour", this);

    coucheH1=new QHBoxLayout;
    coucheH1->addWidget(LabelListe);
    coucheH1->addWidget(Liste);
    coucheH1->addWidget(LabelResult);
    coucheH1->addWidget(Result);
    coucheH1->addWidget(submit);
    coucheH1->addWidget(retour);

    couche=new QVBoxLayout;
    couche->addLayout(coucheH1);
    setLayout(couche);

    update();

    QObject::connect(submit, SIGNAL(clicked()), this, SLOT(ajout_UVDossier()));
    QObject::connect(retour, SIGNAL(clicked()), this, SLOT(end_listeUV()));

}

void AjoutUV::ajout_UVDossier() //Le slot ajout_UVDossier est appelé à chaque appui sur le bouton submit
{
    UVManager& m=UVManager::getInstance();
    UV* nouvelleUV=m.trouverUV(Liste->currentText());
    QString res=Result->currentText();
    dos->ajouterUV(nouvelleUV);
    dos->ajouterResultat(res);
    QMessageBox::information(this,"Ajout UV","UV "+nouvelleUV->getCode()+" ajoutée au dossier n°"+QString::number(dos->getNumero()));

}





void MenuDossier::update()
{
    dossiers->clear();
    for(iterateur<Dossier>& it=dman->getIterateurDos();!it.isDone();it.next())
    {
        dossiers->addItem(QString::number(it.courant()->getNumero()));
    }
}


/*void MenuDossier::visualiser()
{
    if(!dman->listempty())
    {
        Dossier* d=dman->trouverDossier(dossiers->currentText().toUInt());
        if(d!=0)
        {
            visualiserDossier* fen=new visualiserDossier(d);
            fen->show();
        }
    }
    else QMessageBox::information(this,"erreur","Pas de dossier !",QMessageBox::Ok);
}*/

void MenuDossier::sauvegarder()
{
    dman->save();
    QMessageBox::information(this,"sauvegarde","liste de dossiers enregistrée");
}



void DossierAjout::update()
{
    f->clear();
    cursusManager& m=cursusManager::getInstance();
    for(QMap<QString,formation*>::iterator it=m.getQmapIteratorFormbegin();it!=m.getQmapIteratorFormend();it++)
    {
        f->addItem(it.value()->getNom());
    }
}


void AjoutUV::update()
{
    Liste->clear();
    UVManager& m=UVManager::getInstance();
    for(iterateur<UV>& it=m.getIterateurForm();!it.isDone();it.next())
    {
        Liste->addItem(it.courant()->getCode());
    }
}

void AjoutUV::end_listeUV() {
    this->close();
}

ModifierDossier::ModifierDossier(DossierManager& dm, Dossier* d, MenuDossier * md) : M(dm), dos(d), menu(md)
{
    this->setWindowTitle(QString("Modification d'un dossier"));

    unsigned int n1=d->getNumero();
   QString n2=QString::number(n1);


    const QString& name=d->getNom();
    const QString& pn=d->getPrenom();
    const QString& forma=d->getFormation();

    num=new QLineEdit(n2, this);
    numLabel=new QLabel("numero de dossier :", this);
    nom=new QLineEdit(name, this);
    nomLabel=new QLabel("nom de l'etudiant : ", this);
    prenom=new QLineEdit(pn, this);
    prenomLabel= new QLabel("prenom de l'etudiant : ", this);;

    formationLabel=new QLabel("formation suivie : "+forma, this);

    modifUV=new QPushButton("modifier les UVs de ce dossier", this);
    modifFormation=new QPushButton("modifier la formation de l'etudiant", this);
    sauver=new QPushButton("Modification terminee", this);

    coucheH1=new QHBoxLayout;
    coucheH1->addWidget(numLabel);
    coucheH1->addWidget(num);
    coucheH1->addWidget(nomLabel);
    coucheH1->addWidget(nom);
    coucheH1->addWidget(prenomLabel);
    coucheH1->addWidget(prenom);

    coucheH2=new QHBoxLayout;
    coucheH2->addWidget(formationLabel);

    coucheH3=new QHBoxLayout;
    coucheH3->addWidget(modifUV);
    coucheH3->addWidget(modifFormation);
    coucheH3->addWidget(sauver);

    couche=new QVBoxLayout;
    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);
    setLayout(couche);

    QObject::connect(sauver, SIGNAL(clicked()), this, SLOT(slot_finModifDossier()));
    QObject::connect(modifUV, SIGNAL(clicked()), this, SLOT(slot_modifUV()));
    QObject::connect(modifFormation, SIGNAL(clicked()), this, SLOT(slot_modifFormation()));


};


void ModifierDossier::slot_modifFormation() {

    ModifFormation * fenetre= new ModifFormation(dos);
    fenetre->show();
}

void ModifFormation::enregistrer_formation() {
      dossier->setFormation(f->currentText());
      QMessageBox::information(this, "sauvegarde", "Formation enregistree");
      this->close();
}

ModifFormation ::ModifFormation(Dossier * d)
{
    this->setWindowTitle(QString("Modification de la formation de l'etudiant"));
    dossier=d;
    formationLabel=new QLabel("Choisissez une formation", this);
    f= new QComboBox;
    update();
    valider=new QPushButton("Valider", this);

    coucheH1=new QHBoxLayout;
    coucheH1->addWidget(formationLabel);
    coucheH1->addWidget(f);

    coucheH2=new QHBoxLayout;
    coucheH2->addWidget(valider);

    couche=new QVBoxLayout;
    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);

    setLayout(couche);
    QObject::connect(valider, SIGNAL(clicked()), this, SLOT(enregistrer_formation()));

}

void ModifFormation::update() {

        f->clear();
        cursusManager& m=cursusManager::getInstance();
        for(QMap<QString,formation*>::iterator it=m.getQmapIteratorFormbegin();it!=m.getQmapIteratorFormend();it++)
        {
            f->addItem(it.key());
        }

}

void ModifierDossier::slot_finModifDossier() {
    bool ok;

    QString n1=num->text();
    unsigned int newkey=n1.toInt(&ok);

    QString n=nom->text();
    QString p=prenom->text();


    unsigned int oldkey=dos->getNumero();
    QString oldname=dos->getNom();
    QString oldfirstname=dos->getPrenom();

    if (oldkey!=newkey) dos->setNumero(newkey);
    if (oldname!=n) dos->setNom(n);
    if (oldfirstname!=p) dos->setPrenom(p);
    menu->update();

    this->close();
}


ModifUV::ModifUV(Dossier* d) : dos(d)
{
    this->setWindowTitle(QString("Que souhaitez-vous faire ?"));
    ajouter=new QPushButton("Ajouter une UV", this);
    supprimer=new QPushButton("Supprimer une UV", this);
    fin=new QPushButton("Fin", this);
    coucheH1=new QHBoxLayout;

    coucheH1->addWidget(ajouter);
    coucheH1->addWidget(supprimer);
    coucheH1->addWidget(fin);

    couche=new QVBoxLayout;
    couche->addLayout(coucheH1);
    setLayout(couche);

    QObject::connect(ajouter, SIGNAL(clicked()), this, SLOT(ajouterUV()));
    QObject::connect(supprimer, SIGNAL(clicked()), this, SLOT(supprimerUV()));
    QObject::connect(fin, SIGNAL(clicked()), this, SLOT(finUV()));

};

void ModifierDossier::slot_modifUV(){
    ModifUV * fenetre= new ModifUV(dos);
    fenetre->show();
}

void ModifUV::supprimerUV() {
    SuppressionUV * fenetre= new SuppressionUV(dos);
    fenetre->show();
}
void ModifUV::ajouterUV() {
    AjoutUV * fenetre= new AjoutUV(dos);
    fenetre->show();
}
void ModifUV::finUV() {
    this->close();
}
SuppressionUV::SuppressionUV(Dossier* d) : dos(d)
{
    liste=new QComboBox;
    update();
    supprimer=new QPushButton("Supprimer cette UV", this);
    fin=new QPushButton("Suppressions terminees", this);

    coucheH1=new QHBoxLayout;
    coucheH1->addWidget(liste);
    coucheH1->addWidget(supprimer);
    coucheH1->addWidget(fin);


    couche=new QVBoxLayout;
    couche->addLayout(coucheH1);
    setLayout(couche);

    QObject::connect(supprimer, SIGNAL(clicked()), this, SLOT(suppression_une_uv()));
    QObject::connect(fin, SIGNAL(clicked()), this, SLOT(finSuppression()));

};

void SuppressionUV::finSuppression(){

    this->close();
}

void SuppressionUV::suppression_une_uv(){

    const QString& uv=liste->currentText();
    UVManager& uvm=UVManager::getInstance();
    UV* u=uvm.trouverUV(uv);

    dos->supprimerUV(u);
}

void SuppressionUV::update() {
    liste->clear();
    UVManager& m=UVManager::getInstance();
    for(iterateur<UV>& it=m.getIterateurForm();!it.isDone();it.next())
    {
        liste->addItem(it.courant()->getCode());
    }
}




