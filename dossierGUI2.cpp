#include"dossierGUI2.h"
#include"cursus.h"
#include"UTProfiler.h"
#include"dossier.h"
#include<QDebug>
#include<sstream>


MenuDossier::MenuDossier() {

    qDebug()<<"constructeur de menudossier";
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
    bool ok;
    QString n1=dossiers->currentText();
    unsigned int n2=n1.toInt(&ok);

    Dossier* dos=dman->trouverDossier(n2);

    DossierAjout * fenetre= new DossierAjout(*dman,this, dos);
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
    qDebug()<<"juste avant l'ouverture";
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

void MenuDossier::update()
{
    dossiers->clear();
    for(iterateur<Dossier>& it=dman->getIterateurDos();!it.isDone();it.next())
    {
        dossiers->addItem(QString::number(it.courant()->getNumero()));
    }
}


DossierAjout::DossierAjout(DossierManager& dm, MenuDossier* p, Dossier* d) :  nbUV(0), nbMaxUV(0), M(dm),parent(p), dos(d) {
    qDebug()<<"ici";

    this->setWindowTitle(QString("Ajout d'un Dossier"));

    numLabel=new QLabel("numero de dossier", this);
    nomLabel=new QLabel("nom de l'etudiant", this);
    prenomLabel=new QLabel("prenom de l'etudiant", this);
    formationLabel=new QLabel("formation suivie", this);
    semestreLabel=new QLabel("numero de semestre actuel", this);
    SelectUV= new QPushButton("2 - Remplir la liste des UVs");
    SelectEquivalences=new QPushButton("3 - Saisir des equivalences");
    sauver=new QPushButton("1 - Sauver", this);

    num= new QLineEdit("", this);
    nom= new QLineEdit("", this);
    prenom= new QLineEdit("", this);

    f=new QComboBox(this);
    cursusManager& cman=cursusManager::getInstance();
    for(QMap<QString,formation*>::iterator it=cman.getQmapIteratorFormbegin();it!=cman.getQmapIteratorFormend();it++)
    {
        f->addItem(it.key());
    }
    semestre=new QSpinBox(this);
    semestre->setRange(1,8);
    semestre->setValue(1);


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
    coucheH2->addWidget(semestreLabel);
    coucheH2->addWidget(semestre);

    coucheH3=new QHBoxLayout;
    coucheH3->addWidget(SelectUV);

    coucheH4=new QHBoxLayout;
    coucheH4->addWidget(sauver);

    coucheH5=new QHBoxLayout;
    coucheH5->addWidget(SelectEquivalences);

    couche=new QVBoxLayout;

    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH4);
    couche->addLayout(coucheH3);
    couche->addLayout(coucheH5);

    setLayout(couche);

    qDebug()<<"iciii dans dossier ajout avant cliquer";

    QMessageBox::information(this, "Attention", "Sauvegarder le dossier avant d'y ajouter des UVs !",QMessageBox::Ok);
    qDebug()<<"iciii dans dossier ajout avant cliquer2";
    QObject::connect(sauver, SIGNAL(clicked()), this, SLOT(slot_ajoutDossier()));
    qDebug()<<"iciii dans dossier ajout avant cliquer3";
    QObject::connect(SelectUV, SIGNAL(clicked()), this, SLOT(slot_selectUV()));
    qDebug()<<"iciii dans dossier ajout avant cliquer4";
    QObject::connect(SelectEquivalences, SIGNAL(clicked()), this, SLOT(select_equivalences()));
    //update();
    qDebug()<<"iciii dans dossier ajout avant cliquer5";

}

void DossierAjout::slot_ajoutDossier() {

    bool ok;
    unsigned int n=num->text().toInt(&ok);
    qDebug()<<"avant ajout";
    unsigned int ns=semestre->value();
    const QString& name=nom->text();
    const QString& fn=prenom->text();
    const QString& F=f->currentText();


    M.ajouterDossier(n, name , fn, F, ns);
    Dossier* d=M.trouverDossier(n);
    dos=d;

    qDebug()<<"apres ajout";

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
    qDebug()<<"uv ajoutee";
    UVManager& m=UVManager::getInstance();
    UV* nouvelleUV=m.trouverUV(Liste->currentText());
    QString res=Result->currentText();
    dos->ajouterUV(nouvelleUV);
    dos->ajouterResultat(res);
    QMessageBox::information(this,"Ajout UV","UV "+nouvelleUV->getCode()+" ajoutée au dossier n°"+QString::number(dos->getNumero()));

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
    qDebug()<<"update1";
    cursusManager& m=cursusManager::getInstance();
    for(QMap<QString,formation*>::iterator it=m.getQmapIteratorFormbegin();it!=m.getQmapIteratorFormend();it++)
    {qDebug()<<"update2";
        f->addItem(it.value()->getNom());
    }
    qDebug()<<"update3";
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
    semestreLabel=new QLabel("Numéro de semestre actuel :",this);
    modifUV=new QPushButton("voir / modifier les UVs de ce dossier et les resultats", this);
    modifFormation=new QPushButton("modifier la formation de l'etudiant", this);
    sauver=new QPushButton("Modification terminee", this);
    modifEquivalences= new QPushButton("Modifier les equivalences", this);

    numsem=new QSpinBox(this);
    numsem->setRange(1,6);
    numsem->setValue(1);

    coucheH1=new QHBoxLayout;
    coucheH1->addWidget(numLabel);
    coucheH1->addWidget(num);
    coucheH1->addWidget(nomLabel);
    coucheH1->addWidget(nom);
    coucheH1->addWidget(prenomLabel);
    coucheH1->addWidget(prenom);

    coucheH2=new QHBoxLayout;
    coucheH2->addWidget(formationLabel);
    coucheH2->addWidget(semestreLabel);
    coucheH2->addWidget(numsem);

    coucheH3=new QHBoxLayout;
    coucheH3->addWidget(modifUV);
    coucheH3->addWidget(modifFormation);
    coucheH3->addWidget(sauver);
    coucheH3->addWidget(modifEquivalences);

    couche=new QVBoxLayout;
    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);
    setLayout(couche);

    QObject::connect(sauver, SIGNAL(clicked()), this, SLOT(slot_finModifDossier()));
    QObject::connect(modifUV, SIGNAL(clicked()), this, SLOT(slot_modifUV()));
    QObject::connect(modifFormation, SIGNAL(clicked()), this, SLOT(slot_modifFormation()));
    QObject::connect(modifEquivalences, SIGNAL(clicked()), this, SLOT(slot_modifEquivalences()));


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
    dos->setSemestre(numsem->value());
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
    modifResultat=new QPushButton("Modifier un resultat", this);
    fin=new QPushButton("Fin", this);
    coucheH1=new QHBoxLayout;
    coucheH0= new QHBoxLayout;

    explication=new QLabel("UVs actuelles du dossier et resultat associe :", this);

    uvs=new QComboBox(this);
    resultats=new QComboBox(this);
    //update();

    coucheH0->addWidget(explication);
    coucheH0->addWidget(uvs);
    coucheH0->addWidget(resultats);
    coucheH1->addWidget(ajouter);
    coucheH1->addWidget(supprimer);
    coucheH1->addWidget(modifResultat);
    coucheH1->addWidget(fin);

    couche=new QVBoxLayout;
    couche->addLayout(coucheH0);
    couche->addLayout(coucheH1);
    setLayout(couche);

    QObject::connect(ajouter, SIGNAL(clicked()), this, SLOT(ajouterUV()));
    QObject::connect(supprimer, SIGNAL(clicked()), this, SLOT(supprimerUV()));
    QObject::connect(fin, SIGNAL(clicked()), this, SLOT(finUV()));
    QObject::connect(modifResultat, SIGNAL(clicked()), this, SLOT(modifierResult()));

};

void ModifUV::update() {//mauvais
}

void ModifUV::modifierResult() {

    ModifResult* fenetre= new ModifResult(dos);
    fenetre->show();
}

ModifResult::ModifResult(Dossier * d) : dos(d) {
    explication=new QLabel("UVs actuelles du dossier et resultat associe :", this);

    uvs=new QComboBox(this);
    resultats=new QComboBox(this);
    valider=new QPushButton("Valider", this);

    coucheH1=new QHBoxLayout;
    coucheH0= new QHBoxLayout;

    update();

    coucheH0->addWidget(explication);
    coucheH0->addWidget(uvs);
    coucheH0->addWidget(resultats);
    coucheH1->addWidget(valider);

    couche=new QVBoxLayout;
    couche->addLayout(coucheH0);
    couche->addLayout(coucheH1);
    setLayout(couche);

    QObject::connect(valider, SIGNAL(clicked()), this, SLOT(enregistrer()));

}

void ModifResult::enregistrer() {}
void ModifResult::update() {

    qDebug()<<"dans modifresult";
    uvs->clear();
    resultats->clear();
    unsigned int i=0;
    QString * res=dos->getlisteResultats();


    for(QMap<QString,UV*>::iterator it=dos->getQmapIteratorUVbegin(); it!=dos->getQmapIteratorUVend();++it)
    {
       // uvs->addItem(*it->getCode());
        resultats->addItem(res[i]);
        i++;
    }



}

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

AjoutEquivalences::AjoutEquivalences(Dossier * d, ModifEquivalences * m) : dos(d), me(m) {

    typeLabel = new QLabel ("Type d'equivalence :", this);
    type = new QComboBox(this) ;
    type->addItem("Semestre a l'etranger");
    type->addItem("Cursus Anterieur");
    creditsLabel =new QLabel ("Credits valides :", this);
    credits =new QLineEdit("", this);
    descriptionLabel =new QLabel ("Description :", this);
    description = new QLineEdit("", this);
    valider =new QPushButton("Valider", this);


    coucheH1=new QHBoxLayout;
    coucheH1->addWidget(typeLabel);
    coucheH1->addWidget(type);
    coucheH1->addWidget(creditsLabel);
    coucheH1->addWidget(credits);

    coucheH2=new QHBoxLayout;
    coucheH1->addWidget(descriptionLabel);
    coucheH1->addWidget(description);

    coucheH3=new QHBoxLayout;
     coucheH3->addWidget(valider);


    couche=new QVBoxLayout;
    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);
    setLayout(couche);

     QObject::connect(valider, SIGNAL(clicked()), this, SLOT(ajouter_equivalence()));

}

void DossierAjout::select_equivalences(){
    AjoutEquivalences* fenetre = new AjoutEquivalences(dos);
    qDebug()<<"dos dans dossier ajout"<<dos;
    fenetre->show();
}

void AjoutEquivalences::ajouter_equivalence() {
    //on cree une equivalence

    bool ok;
    const QString& n1=credits->text();
    const QString& truc = type->currentText();
    const QString& desc = description->text();
    unsigned int n2=n1.toInt(&ok);

    qDebug()<<"dans ajouter aquivalence";
    qDebug()<<dos;

    Equivalences ** tab=dos->getEquivalences();
    qDebug()<<tab;
    unsigned int nb = dos->getNbEquivalences();
    qDebug()<<"dans ajouter aquivalence2";

    tab[nb]= new Equivalences(truc, n2, desc);
    qDebug()<<"ici la";
    nb++;
    dos->setNbEquivalences(nb);

    qDebug()<<"equivalence ajoutée!";
    QMessageBox::information(this, "sauvegarde", "Equivalence ajoutee");

   if (me!=0) me->update();
    this->close();
}

ModifEquivalences::ModifEquivalences(Dossier * dos) : dossier(dos) {

    valider=new QPushButton("Modifier cette equivalence", this);
    ajouter=new QPushButton("Ajouter une equivalence", this);
    supprimer=new QPushButton("Supprimer cette equivalence", this);
    quitter=new QPushButton("Modification des equivalences terminee", this);

    choix=new QComboBox(this);
    update();

    coucheH1=new QHBoxLayout;
    coucheH1->addWidget(choix);
    coucheH1->addWidget(valider);

    coucheH2=new QHBoxLayout;
    coucheH2->addWidget(ajouter);

    coucheH3=new QHBoxLayout;
    coucheH3->addWidget(supprimer);

    coucheH4=new QHBoxLayout;
    coucheH4->addWidget(quitter);

    couche=new QVBoxLayout;
    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);
    couche->addLayout(coucheH4);

    setLayout(couche);

    QObject::connect(valider, SIGNAL(clicked()), this, SLOT(slot_valider()));
    QObject::connect(ajouter, SIGNAL(clicked()), this, SLOT(slot_ajouter()));
    QObject::connect(supprimer, SIGNAL(clicked()), this, SLOT(slot_supprimer()));
    QObject::connect(quitter, SIGNAL(clicked()), this, SLOT(ajouter_quitter()));

}

void ModifEquivalences::update() { // FONCTIONNE

    Equivalences** tab=dossier->getEquivalences();
    unsigned int i=0;

    choix->clear();
    qDebug()<<"update";
    qDebug()<<dossier->getNbEquivalences();
    qDebug()<<tab[i];
    if (dossier->getNbEquivalences()!=0)
   {  while (tab[i]!=0) {
        qDebug()<<tab[i]->getDescription();
        choix->addItem(tab[i]->getDescription());
        i++;}
    }
}

void ModifierDossier::slot_modifEquivalences() {

    ModifEquivalences* fenetre= new ModifEquivalences(dos);
    fenetre->show();

}

void ModifEquivalences::slot_ajouter() {

    AjoutEquivalences* fenetre = new AjoutEquivalences(dossier, this);
    fenetre->show();

}

EquivalenceEditeur::EquivalenceEditeur(Dossier * d, Equivalences* e, ModifEquivalences * m) : dos(d), eq(e), me(m) {

    typeLabel = new QLabel ("Type d'equivalence :", this);
    type = new QComboBox(this) ;
    type->addItem("Semestre a l'etranger");
    type->addItem("Cursus Anterieur");
    //type->setCurrentIndex(int(e->getDescription());

    creditsLabel =new QLabel ("Credits valides :", this);
    QString truc = QString::number(e->getNbCredits());
    credits =new QLineEdit(truc, this);
    descriptionLabel =new QLabel ("Description :", this);
    description = new QLineEdit(e->getDescription(), this);
    valider =new QPushButton("Valider", this);


    coucheH1=new QHBoxLayout;
    coucheH1->addWidget(typeLabel);
    coucheH1->addWidget(type);
    coucheH1->addWidget(creditsLabel);
    coucheH1->addWidget(credits);

    coucheH2=new QHBoxLayout;
    coucheH1->addWidget(descriptionLabel);
    coucheH1->addWidget(description);

    coucheH3=new QHBoxLayout;
     coucheH3->addWidget(valider);


    couche=new QVBoxLayout;
    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);
    setLayout(couche);

    QObject::connect(valider, SIGNAL(clicked()), this, SLOT(modifier_equivalence()));
}

void EquivalenceEditeur::modifier_equivalence() {//MARCHE

    eq->setDescription(description->text());
    eq->setType(type->currentText());

    bool ok;
    const QString& n1=credits->text();
    unsigned int n2=n1.toInt(&ok);
    eq->setNbCredits(n2);

    this->close();

}

void ModifEquivalences::slot_valider() {

    Equivalences** tab=dossier->getEquivalences();
    unsigned int nb=dossier->getNbEquivalences();
    unsigned int i=0;

    while (tab[i]->getDescription()!=choix->currentText()) {i++;}

    EquivalenceEditeur * fenetre= new EquivalenceEditeur(dossier, tab[i], this);
    fenetre->show();
}

void ModifEquivalences::slot_quitter() {this->close();}

void  ModifEquivalences::slot_supprimer() {

    Equivalences** tab=dossier->getEquivalences();
    int nb=dossier->getNbEquivalences();
    unsigned int i=0;

    qDebug()<<"dans suppr";

    while (tab[i]->getDescription()!=choix->currentText()) {i++;}
    qDebug()<<"nombre deq : "<<nb;//OK
    qDebug()<<tab[i]->getDescription();//OK
    qDebug()<<i;//OK

    Equivalences* tmp;

    for (int j=i; j<nb-2; j++) {tmp=tab[i]; tab[j]=tab[j+1], tab[j+1]=tmp;}
    qDebug()<<"apres le for";

    delete tab[nb-1];
    qDebug()<<"apres le delete";
    nb--;
    dossier->setNbEquivalences(nb);
    qDebug()<<"a la fin de la suppression";

    update();

    QMessageBox::information(this, "sauvegarde", "Equivalence supprimee");

}




