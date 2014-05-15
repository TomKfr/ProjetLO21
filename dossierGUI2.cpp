#include"dossierGUI2.h"
#include"UTProfiler.h"
#include"dossier.h"
#include<QDebug>
#include<sstream>



MenuDossier::MenuDossier() {

    this->setWindowTitle(QString("Opération choisie sur les dossiers ?"));
    dman=&DossierManager::getInstance();
    dossiers=new QComboBox(this);
    visu=new QPushButton("Visualiser dossier",this);
    ajouter=new QPushButton("Ajouter", this);
    modifier=new QPushButton("Consulter/Modifier des informations", this);
    sup=new QPushButton("Supprimer", this);
    sauver=new QPushButton("sauver",this);

    coucheH=new QHBoxLayout;
    coucheH->addWidget(visu);
    coucheH->addWidget(sup);
    coucheH->addWidget(ajouter);
    coucheH->addWidget(modifier);
    coucheH->addWidget(sauver);

    coucheV=new QVBoxLayout;
    coucheV->addWidget(dossiers);
    coucheV->addLayout(coucheH);
    setLayout(coucheV);

    update();

    QObject::connect(ajouter, SIGNAL(clicked()), this, SLOT(ajout()));
    //QObject::connect(sup, SIGNAL(clicked()), this, SLOT(suppression()));
    //QObject::connect(modifier, SIGNAL(clicked()), this, SLOT(modif()));
    QObject::connect(visu,SIGNAL(clicked()),this,SLOT(visualiser()));
    QObject::connect(sauver, SIGNAL(clicked()),this, SLOT(sauvegarder()));

}

void MenuDossier::ajout() {
    DossierAjout * fenetre= new DossierAjout(*dman,this);
    fenetre->show();
}//OK



DossierAjout::DossierAjout(DossierManager& dm, MenuDossier* p) :  nbUV(0), nbMaxUV(0), M(dm),parent(p) {

    this->setWindowTitle(QString("Ajout d'un Dossier"));

    numLabel=new QLabel("num", this);
    nomLabel=new QLabel("nom", this);
    prenomLabel=new QLabel("prenom", this);
    formationLabel=new QLabel("formation", this);
    SelectUV= new QPushButton("Remplir la liste des UVs");
    sauver=new QPushButton("Sauver", this);

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
    couche->addLayout(coucheH3);
    couche->addLayout(coucheH4);

    setLayout(couche);

    //bouton desactive par defaut
    //sauver->setEnabled(false);

    QMessageBox::warning(this, "Attention", "Sauvegarder le dossier avant d'y ajouter des UVs !",QMessageBox::Ok);

   QObject::connect(sauver, SIGNAL(clicked()), this, SLOT(slot_ajoutDossier()));
   QObject::connect(SelectUV, SIGNAL(clicked()), this, SLOT(slot_selectUV()));

   update();

   //pour que ça sactive que si modif :
   //QObject::connect(code, SIGNAL(textEdited(QString)), this, SLOT(activerSauverUV(QString)));
}

void DossierAjout::slot_ajoutDossier() {

    bool ok;

    unsigned int n=num->text().toInt(&ok);
    const QString& name=nom->text();
    const QString& fn=prenom->text();
    const QString& F=f->currentText();

    M.ajouterDossier(n, name , fn, F); //DABORD LES AJOUTS SIMPLES. PUIS ON GERE LES UVS

    //void ajouterUV(const QString& c, const QString& t, unsigned int nbc, Categorie cat, bool a, bool p);
    QMessageBox::information(this, "sauvegarde", "Dossier sauvegarde");
    parent->update();
}


void DossierAjout::slot_selectUV() {
    bool ok;
    //ATTENTION ! ajouter le dossier avant !!
    unsigned int n=num->text().toInt(&ok);
    Dossier* d=M.trouverDossier(n);

    qDebug()<<"ad du dossier avant selectuv"<<d; // CEST BON

    AjoutUV* fenetre= new AjoutUV(this, d);
    fenetre->show();
}

AjoutUV::AjoutUV(DossierAjout* dossier, Dossier*d) {
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

    qDebug()<<nouvelleUV->getCode(); // OK  A CE NIVEAU
    qDebug()<<"ajout uv dossier";
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


void MenuDossier::visualiser()
{
    if(!dman->listempty())
    {
        Dossier* d=dman->trouverDossier(dossiers->currentText().toUInt());
        qDebug()<<"envoi du dossier à l'adresse :"<<d;
        if(d!=0)
        {
            visualiserDossier* fen=new visualiserDossier(d);
            fen->show();
        }
    }
    else QMessageBox::information(this,"erreur","Pas de dossier !",QMessageBox::Ok);
}

void MenuDossier::sauvegarder()
{
    QString chemin=QFileDialog::getOpenFileName(0,"Ouvrir un fichier de dossiers");
    dman->save(chemin);
    QMessageBox::information(this,"sauvegarde","liste de dossiers enregistrée");
}

visualiserDossier::visualiserDossier(Dossier *d)
{
    qDebug()<<"réception de l'adresse :"<<d;
    dos=d;
    numdos=new QLabel(dos->getNom(),this);
    listuv=new QLabel(this);
    mainbox=new QHBoxLayout();
    quit=new QPushButton("fermer",this);
    mainbox->addWidget(numdos);
    mainbox->addWidget(listuv);
    mainbox->addWidget(quit);
    setLayout(mainbox);
    QString uvs="";
    for(iterateur<UV>& it=dos->getIterateurUV();!it.isDone();it.next())
    {
        uvs+=it.courant()->getCode()+"\n";
    }
    listuv->setText(uvs);

    QObject::connect(quit,SIGNAL(clicked()),this,SLOT(close()));
}





//OSEF de cette partie ça marche bien :
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



