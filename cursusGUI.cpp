#include "cursus.h"
#include "cursusGUI.h"
#include "UTProfiler.h"
#include <QMessageBox>

menuFormation::menuFormation()
{
    m=&cursusManager::getInstance();
    uvman=&UVManager::getInstance();

    mainbox=new QVBoxLayout(this);
    hbox1=new QHBoxLayout(this);
    hbox2=new QHBoxLayout(this);
    titre=new QLabel("Choisissez une formation et sélectionnez l'opération:",this);
    select=new QComboBox(this);
    visualiser=new QPushButton("Voir les détails",this);
    ajouter=new QPushButton("Ajouter une formation",this);
    modifier=new QPushButton("Modifier",this);
    fil=new QPushButton("Gérer les filières",this);
    supprimer=new QPushButton("Supprimer",this);
    quit=new QPushButton("Quitter",this);
    sauver=new QPushButton("Sauver",this);

    select->setFixedWidth(300);
    mainbox->addLayout(hbox1);
    mainbox->addLayout(hbox2);
    hbox1->addWidget(titre);
    hbox1->addWidget(select);
    hbox2->addWidget(visualiser);
    hbox2->addWidget(ajouter);
    hbox2->addWidget(modifier);
    hbox2->addWidget(fil);
    hbox2->addWidget(supprimer);
    hbox2->addWidget(sauver);
    hbox2->addWidget(quit);

    QObject::connect(visualiser,SIGNAL(clicked()),this,SLOT(voir()));
    QObject::connect(ajouter,SIGNAL(clicked()),this, SLOT(ajout()));
    QObject::connect(modifier,SIGNAL(clicked()),this, SLOT(modif()));
    QObject::connect(fil,SIGNAL(clicked()),this,SLOT(filir()));
    QObject::connect(supprimer,SIGNAL(clicked()),this, SLOT(suppr()));
    QObject::connect(quit,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(sauver, SIGNAL(clicked()),this,SLOT(save()));

    update();
}

void menuFormation::voir()
{
    visualiserFormation* fenetre=new visualiserFormation(m,uvman,m->trouverForm(select->currentText()));
    fenetre->show();
}

void menuFormation::update()
{
    select->clear();
    for(QMap<QString,formation*>::iterator it=m->getQmapIteratorFormbegin();it!=m->getQmapIteratorFormend();it++)
    {
        select->addItem(it.key());
    }
}

void menuFormation::ajout()
{
    ajoutFormation* fenetre=new ajoutFormation(m, this);
    fenetre->show();
}

void menuFormation::modif()
{
    modifFormation* fenetre=new modifFormation(m,this,m->trouverForm(select->currentText()));
    fenetre->show();
}

void menuFormation::filir()
{
    GestionFiliereFormation* f=new GestionFiliereFormation(m->trouverForm(select->currentText()));
    f->show();
    //menuFiliere* f=new menuFiliere();
    //f->show();
}

void menuFormation::suppr()
{
    if(QMessageBox::information(this,"Suppression","Voulez-vous supprimer la formation "+select->currentText()+" ?",QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Ok)
    {
        m->supprimerFormation(select->currentText());
        QMessageBox::information(this,"Suppression","Formation supprimée !",QMessageBox::Ok);
        this->update();
    }
}
void menuFormation::save()
{
    m->sauverCursus(this);
}

// ///////////////////////////////////////////////////////////////////
ajoutFormation::ajoutFormation(cursusManager* m, menuFormation* p) {

    this->setWindowTitle(QString("Ajout d'une formation"));

    man=m;
    parent=p;
    mainbox=new QVBoxLayout(this);
    hbox1=new QHBoxLayout(this);
    hbox2=new QHBoxLayout(this);
    hbox3=new QHBoxLayout(this);
    lbl1=new QLabel("Nom de la formation :",this);
    lbl2=new QLabel("Nombre de semestres :",this);
    lbl3=new QLabel("Nombre de crédits :",this);
    nom=new QLineEdit(this);
    valider=new QPushButton("Valider",this);
    valider->setDefault(true);
    credits=new QSpinBox(this);
    credits->setRange(100,400);
    credits->setSingleStep(10);
    semstr=new QSpinBox(this);
    semstr->setRange(4,6);

    hbox1->addWidget(lbl1);
    hbox1->addWidget(nom);
    hbox2->addWidget(lbl2);
    hbox2->addWidget(semstr);
    hbox2->addWidget(lbl3);
    hbox2->addWidget(credits);
    hbox3->addWidget(valider);
    mainbox->addLayout(hbox1);
    mainbox->addLayout(hbox2);
    mainbox->addLayout(hbox3);
    this->setLayout(mainbox);

    QObject::connect(valider, SIGNAL(clicked()),this,SLOT(ajout()));
}

void ajoutFormation::ajout()
{
    man->ajouterFormation(nom->text(),credits->value(), semstr->value());
    QMessageBox::information(this,"Ajout d'une formation", "Formation ajoutée !",QMessageBox::Ok);
    parent->update();
    this->close();
}

modifFormation::modifFormation(cursusManager* m, menuFormation *p, formation* f)
{
    this->setWindowTitle(QString("Ajout d'une formation"));
    this->setFixedWidth(200);
    man=m;
    parent=p;
    form=f;
    mainbox=new QVBoxLayout(this);
    hbox1=new QHBoxLayout(this);
    hbox2=new QHBoxLayout(this);
    hbox3=new QHBoxLayout(this);
    lbl1=new QLabel("Nom de la formation :",this);
    lbl2=new QLabel("Nombre de semestres :",this);
    lbl3=new QLabel("Nombre de crédits :",this);
    nom=new QLineEdit(this);
    nom->setText(f->getNom());
    valider=new QPushButton("Valider",this);
    valider->setDefault(true);
    credits=new QSpinBox(this);
    credits->setRange(100,400);
    credits->setSingleStep(10);
    credits->setValue(f->getNbCred());
    semstr=new QSpinBox(this);
    semstr->setRange(4,6);
    semstr->setValue(f->getNbSem());

    hbox1->addWidget(lbl1);
    hbox1->addWidget(nom);
    hbox2->addWidget(lbl2);
    hbox2->addWidget(semstr);
    hbox2->addWidget(lbl3);
    hbox2->addWidget(credits);
    hbox3->addWidget(valider);
    mainbox->addLayout(hbox1);
    mainbox->addLayout(hbox2);
    mainbox->addLayout(hbox3);
    this->setLayout(mainbox);

    QObject::connect(valider, SIGNAL(clicked()),this,SLOT(modif()));
}

void modifFormation::modif()
{
    man->modifFormation(form->getNom(),nom->text(),credits->value(), semstr->value());
    QMessageBox::information(this,"Modification","Modification effectuée",QMessageBox::Ok);
    parent->update();
    this->close();
}

visualiserFormation::visualiserFormation(cursusManager* cmanager, UVManager* umanager, formation* f)
{
    this->setWindowTitle(f->getNom());
    this->setFixedWidth(400);
    cman=cmanager;
    uman=umanager;
    objet=f;
    mainbox=new QHBoxLayout(this);
    vbox1=new QVBoxLayout(this);
    vbox2=new QVBoxLayout(this);
    hbox1=new QHBoxLayout(this);
    hbox2=new QHBoxLayout(this);
    hbox3=new QHBoxLayout(this);
    form=new QLabel(objet->getNom(),this);
    cred=new QLabel(QString::number(objet->getNbCred()),this);
    cred->setFixedWidth(50);
    semstr=new QLabel(QString::number(objet->getNbSem()),this);
    semstr->setFixedWidth(50);
    retour=new QPushButton("Retour",this);
    modif=new QPushButton("Modifier les UVs",this);
    lbluvs=new QLabel("UVs appartenant à la formation:",this);
    suppr=new QPushButton("Supprimer",this);
    supprUV=new QComboBox(this);
    uvs=new QLabel(this);
    update();

    hbox1->addWidget(form);
    hbox2->addWidget(cred);
    hbox2->addWidget(semstr);
    hbox3->addWidget(retour);
    hbox3->addWidget(modif);
    vbox1->addLayout(hbox1);
    vbox1->addLayout(hbox2);
    vbox1->addLayout(hbox3);
    vbox2->addWidget(lbluvs);
    vbox2->addWidget(uvs);
    vbox2->addWidget(supprUV);
    vbox2->addWidget(suppr);
    mainbox->addLayout(vbox1);
    mainbox->addLayout(vbox2);
    this->setLayout(mainbox);

    QObject::connect(retour, SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(modif,SIGNAL(clicked()),this,SLOT(moduvs()));
    QObject::connect(suppr,SIGNAL(clicked()),this,SLOT(supprimer()));
}

void visualiserFormation::moduvs()
{
    selectUVsFormation* fenetre=new selectUVsFormation(cman,uman,objet,this);
    fenetre->show();
}

void visualiserFormation::update()
{
    supprUV->clear();
    uvs->clear();
    QString txt="";
    for(QMap<QString,UV*>::iterator it=objet->getQmapIteratorUVbegin();it!=objet->getQmapIteratorUVend(); it++)
    {
        supprUV->addItem(it.key());
        txt+=it.key()+"\n";
    }
    uvs->setText(txt);
}

void visualiserFormation::supprimer()
{
    objet->supprimer_UV(supprUV->currentText());
    this->update();
}


selectUVsFormation::selectUVsFormation(cursusManager* cm, UVManager* um, formation* f, visualiserFormation *p)
{
    this->setWindowTitle("Modifier les UVs");
    cman=cm;
    uman=um;
    objet=f;
    parent=p;
    mainbox=new QVBoxLayout(this);
    label1=new QLabel("Sélectionnez une UV pour l'ajouter à la formation "+f->getNom(),this);
    choix=new QComboBox(this);

    update();

    retour=new QPushButton("Retour",this);
    ajouter=new QPushButton("Ajouter",this);
    mainbox->addWidget(label1);
    mainbox->addWidget(choix);
    mainbox->addWidget(ajouter);
    mainbox->addWidget(retour);
    this->setLayout(mainbox);

    QObject::connect(retour,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(ajouter,SIGNAL(clicked()),this,SLOT(ajouterUV()));
}

void selectUVsFormation::ajouterUV()
{
    objet->ajouter_UV(&uman->getUV(choix->currentText())); // MODIF ICI %%%§§§%
    QMessageBox::information(this,"Ajout d'une UV","UV "+choix->currentText()+" ajoutée à la formation "+objet->getNom(),QMessageBox::Ok);
    parent->update();
    this->update();
}

void selectUVsFormation::update()
{
    choix->clear();
    for(iterateur<UV>& it=uman->getIterateurForm();!it.isDone();it.next())
    {
        if(objet->trouverUV(it.courant()->getCode())==objet->getQmapIteratorUVend()) choix->addItem(it.courant()->getCode());
    }
}

// ///////////////////////////////////////////////////////////////////
GestionFiliereFormation::GestionFiliereFormation(formation *f): uman(UVManager::getInstance()), cman(cursusManager::getInstance()), objet(f)
{
    mainbox=new QVBoxLayout(this);
    hbox1=new QHBoxLayout(this);
    vbox1=new QVBoxLayout(this);
    vbox2=new QVBoxLayout(this);
    lbl1=new QLabel("Gestion des filières de la formation "+f->getNom(),this);
    lbl2=new QLabel("Ajouter une filière à la formation:",this);
    lbl3=new QLabel("Filières déjà incluses dans la formation:\n",this);
    ajt=new QComboBox(this);
    suppr=new QComboBox(this);
    retour=new QPushButton("Retour",this);
    ajouter=new QPushButton("Ajouter",this);
    supprimer=new QPushButton("Supprimer",this);

    mainbox->addLayout(hbox1);
    mainbox->addWidget(lbl1);
    hbox1->addLayout(vbox1);
    hbox1->addLayout(vbox2);
    vbox1->addWidget(lbl2);
    vbox1->addWidget(ajt);
    vbox1->addWidget(ajouter);
    vbox2->addWidget(lbl3);
    vbox2->addWidget(suppr);
    vbox2->addWidget(supprimer);
    mainbox->addWidget(retour);

    QObject::connect(ajouter,SIGNAL(clicked()),this,SLOT(ajouterFiliere()));
    QObject::connect(supprimer,SIGNAL(clicked()),this,SLOT(supprimerFiliere()));
    QObject::connect(retour,SIGNAL(clicked()),this,SLOT(close()));

    update();
}

void GestionFiliereFormation::ajouterFiliere()
{
    cman.inscrFilForm(objet,ajt->currentText());
    QMessageBox::information(this,"Ajout d'une filière","La filière "+ajt->currentText()+" a été ajoutée à la formation "+objet->getNom());
    this->update();
}
void GestionFiliereFormation::update()
{
    ajt->clear();
    suppr->clear();
    lbl3->clear();
    QString txt="";
    qDebug()<<"hello1";
    for(QMap<QString,filiere*>::iterator it=cman.getQmapIteratorFilBegin();it!=cman.getQmapIteratorFilEnd();it++)
    {
        qDebug()<<"hello2";
        if(cman.trouverFilForm(objet,it.key()))
        {
            suppr->addItem(it.key());
            txt+=it.key()+"\n";
        }
        else
        {
            ajt->addItem(it.key());
        }
    }
    qDebug()<<"hello";
    lbl3->setText("Filières déjà incluses dans la formation:\n"+txt);
}
void GestionFiliereFormation::supprimerFiliere()
{
    if(QMessageBox::information(this,"Retrait d'une filière","Voulez-vous supprimer la filière "+suppr->currentText()+" de la formation "+objet->getNom()+" ?",QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Ok)
    {
        cman.supprFilForm(objet,suppr->currentText());
        QMessageBox::information(this,"Retrait d'une filière","Filière retirée !");
        this->update();
    }
}



// ///////////////////////////////////////////////////////////////////
menuFiliere::menuFiliere()
{
    m=&cursusManager::getInstance();

    mainbox=new QVBoxLayout(this);
    hbox1=new QHBoxLayout(this);
    hbox2=new QHBoxLayout(this);
    titre=new QLabel("Choisissez une filière et sélectionnez l'opération:",this);
    select=new QComboBox(this);
    visualiser=new QPushButton("Voir les détails",this);
    ajouter=new QPushButton("Ajouter une filière",this);
    modifier=new QPushButton("Modifier",this);
    supprimer=new QPushButton("Supprimer",this);
    quit=new QPushButton("Quitter",this);
    sauver=new QPushButton("Sauver",this);

    select->setFixedWidth(300);
    mainbox->addLayout(hbox1);
    mainbox->addLayout(hbox2);
    hbox1->addWidget(titre);
    hbox1->addWidget(select);
    hbox2->addWidget(visualiser);
    hbox2->addWidget(ajouter);
    hbox2->addWidget(modifier);
    hbox2->addWidget(supprimer);
    hbox2->addWidget(sauver);
    hbox2->addWidget(quit);

    QObject::connect(visualiser,SIGNAL(clicked()),this,SLOT(voir()));
    QObject::connect(ajouter,SIGNAL(clicked()),this, SLOT(ajout()));
    QObject::connect(modifier,SIGNAL(clicked()),this, SLOT(modif()));
    QObject::connect(supprimer,SIGNAL(clicked()),this, SLOT(suppr()));
    QObject::connect(quit,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(sauver, SIGNAL(clicked()),this,SLOT(save()));

    update();
}

void menuFiliere::voir()
{
    cursusManager& m=cursusManager::getInstance();
    visualiserFiliere* f=new visualiserFiliere(m.trouverFil(select->currentText()));
    f->show();
}

void menuFiliere::update()
{
    select->clear();
    for(QMap<QString,filiere*>::iterator it=m->getQmapIteratorFilBegin();it!=m->getQmapIteratorFilEnd();it++)
    {
        select->addItem(it.key());
    }
}

void menuFiliere::ajout()
{
    ajoutFiliere* fenetre=new ajoutFiliere(this);
    fenetre->show();
}

void menuFiliere::modif()
{
    cursusManager& m=cursusManager::getInstance();
    modifFiliere* f=new modifFiliere(this,m.trouverFil(select->currentText()));
    f->show();
}

void menuFiliere::suppr()
{
    if(QMessageBox::information(this,"Suppression","Voulez-vous supprimer la filière "+select->currentText()+" ?",QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Ok)
    {
        m->supprimerFiliere(select->currentText());
        QMessageBox::information(this,"Suppression","Filière supprimée !",QMessageBox::Ok);
        this->update();
    }
}
void menuFiliere::save()
{
    m->sauverCursus(this);
}

ajoutFiliere::ajoutFiliere(menuFiliere *p)
{
    this->setWindowTitle(QString("Ajout d'une formation"));
    parent=p;
    mainbox=new QVBoxLayout(this);
    hbox1=new QHBoxLayout(this);
    hbox2=new QHBoxLayout(this);
    hbox3=new QHBoxLayout(this);
    lbl1=new QLabel("Nom de la filière :",this);
    lbl2=new QLabel("Nombre de crédits PSF :",this);
    nom=new QLineEdit(this);
    valider=new QPushButton("Valider",this);
    valider->setDefault(true);
    credits=new QSpinBox(this);
    credits->setRange(100,400);
    credits->setSingleStep(5);

    hbox1->addWidget(lbl1);
    hbox1->addWidget(nom);
    hbox2->addWidget(lbl2);
    hbox2->addWidget(credits);
    hbox3->addWidget(valider);
    mainbox->addLayout(hbox1);
    mainbox->addLayout(hbox2);
    mainbox->addLayout(hbox3);
    this->setLayout(mainbox);

    QObject::connect(valider, SIGNAL(clicked()),this,SLOT(ajout()));
}

void ajoutFiliere::ajout()
{
    cursusManager& m=cursusManager::getInstance();
    m.ajouterFiliere(nom->text(),credits->value());
    QMessageBox::information(this,"Ajout d'une filière", "Filière ajoutée !",QMessageBox::Ok);
    parent->update();
    this->close();
}

visualiserFiliere::visualiserFiliere(filiere *f)
{
    this->setWindowTitle(f->getNom());
    this->setFixedWidth(400);
    objet=f;
    mainbox=new QHBoxLayout(this);
    vbox1=new QVBoxLayout(this);
    vbox2=new QVBoxLayout(this);
    hbox1=new QHBoxLayout(this);
    hbox2=new QHBoxLayout(this);
    hbox3=new QHBoxLayout(this);
    form=new QLabel(objet->getNom(),this);
    cred=new QLabel(QString::number(objet->getNbCred()),this);
    cred->setFixedWidth(50);
    retour=new QPushButton("Retour",this);
    modif=new QPushButton("Modifier les UVs",this);
    lbluvs=new QLabel("UVs appartenant à la filière:",this);
    suppr=new QPushButton("Supprimer",this);
    supprUV=new QComboBox(this);
    uvs=new QLabel(this);
    update();

    hbox1->addWidget(form);
    hbox2->addWidget(cred);
    hbox3->addWidget(retour);
    hbox3->addWidget(modif);
    vbox1->addLayout(hbox1);
    vbox1->addLayout(hbox2);
    vbox1->addLayout(hbox3);
    vbox2->addWidget(lbluvs);
    vbox2->addWidget(uvs);
    vbox2->addWidget(supprUV);
    vbox2->addWidget(suppr);
    mainbox->addLayout(vbox1);
    mainbox->addLayout(vbox2);
    this->setLayout(mainbox);

    QObject::connect(retour, SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(modif,SIGNAL(clicked()),this,SLOT(moduvs()));
    QObject::connect(suppr,SIGNAL(clicked()),this,SLOT(supprimer()));
}

void visualiserFiliere::moduvs()
{
    selectUVsFiliere* f=new selectUVsFiliere(objet,this);
    f->show();
}

void visualiserFiliere::update()
{
    supprUV->clear();
    uvs->clear();
    QString txt="";
    for(QMap<QString,UV*>::iterator it=objet->getQmapIteratorUVbegin();it!=objet->getQmapIteratorUVend();it++)
    {
        supprUV->addItem(it.key());
        txt+=it.key()+"\n";
    }
    uvs->setText(txt);
}

void visualiserFiliere::supprimer()
{
    objet->supprimer_UV(supprUV->currentText());
    this->update();
}

modifFiliere::modifFiliere(menuFiliere *p, filiere* f)
{
    this->setWindowTitle(QString("Ajout d'une formation"));
    this->setFixedWidth(200);
    parent=p;
    fil=f;
    mainbox=new QVBoxLayout(this);
    hbox1=new QHBoxLayout(this);
    hbox2=new QHBoxLayout(this);
    hbox3=new QHBoxLayout(this);
    lbl1=new QLabel("Nom de la formation :",this);
    lbl2=new QLabel("Nombre de crédits :",this);
    nom=new QLineEdit(this);
    nom->setText(f->getNom());
    valider=new QPushButton("Valider",this);
    valider->setDefault(true);
    credits=new QSpinBox(this);
    credits->setRange(100,400);
    credits->setSingleStep(10);
    credits->setValue(f->getNbCred());

    hbox1->addWidget(lbl1);
    hbox1->addWidget(nom);
    hbox2->addWidget(lbl2);
    hbox2->addWidget(credits);
    hbox3->addWidget(valider);
    mainbox->addLayout(hbox1);
    mainbox->addLayout(hbox2);
    mainbox->addLayout(hbox3);
    this->setLayout(mainbox);

    QObject::connect(valider, SIGNAL(clicked()),this,SLOT(modif()));
}

void modifFiliere::modif()
{
    cursusManager& man=cursusManager::getInstance();
    man.modifFiliere(fil->getNom(),nom->text(),credits->value());
    QMessageBox::information(this,"Modification","Modification effectuée",QMessageBox::Ok);
    parent->update();
    this->close();
}

selectUVsFiliere::selectUVsFiliere(filiere* f, visualiserFiliere *p): cman(cursusManager::getInstance()), uman(UVManager::getInstance())
{
    this->setWindowTitle("Modifier les UVs");
    objet=f;
    parent=p;
    mainbox=new QVBoxLayout(this);
    label1=new QLabel("Sélectionnez une UV pour l'ajouter à la filiere "+f->getNom(),this);
    choix=new QComboBox(this);

    update();

    retour=new QPushButton("Retour",this);
    ajouter=new QPushButton("Ajouter",this);
    mainbox->addWidget(label1);
    mainbox->addWidget(choix);
    mainbox->addWidget(ajouter);
    mainbox->addWidget(retour);
    this->setLayout(mainbox);

    QObject::connect(retour,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(ajouter,SIGNAL(clicked()),this,SLOT(ajouterUV()));
}

void selectUVsFiliere::ajouterUV()
{
    objet->ajouter_UV(&uman.getUV(choix->currentText()));
    QMessageBox::information(this,"Ajout d'une UV","UV "+choix->currentText()+" ajoutée à la filiere "+objet->getNom(),QMessageBox::Ok);
    parent->update();
    this->update();
}

void selectUVsFiliere::update()
{
    choix->clear();
    for(iterateur<UV>& it=uman.getIterateurForm();!it.isDone();it.next())
    {
        if(objet->trouverUV(it.courant()->getCode())==objet->getQmapIteratorUVend()) choix->addItem(it.courant()->getCode());
    }
}
