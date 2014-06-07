#include "cursus.h"
#include "cursusGUI.h"
#include "UTProfiler.h"
#include "dossier.h"
#include <QMessageBox>
#include <QCheckBox>

/*!
 * \brief Constructeur de la fenêtre menuFormation.
 */
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
    ajfil=new QPushButton("Gérer les filières de cette formation",this);
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
    hbox2->addWidget(ajfil);
    hbox2->addWidget(supprimer);
    hbox2->addWidget(sauver);
    hbox2->addWidget(quit);

    QObject::connect(visualiser,SIGNAL(clicked()),this,SLOT(voir()));
    QObject::connect(ajouter,SIGNAL(clicked()),this, SLOT(ajout()));
    QObject::connect(modifier,SIGNAL(clicked()),this, SLOT(modif()));
    QObject::connect(fil,SIGNAL(clicked()),this,SLOT(filir()));
    QObject::connect(ajfil,SIGNAL(clicked()),this,SLOT(ajfilir()));
    QObject::connect(supprimer,SIGNAL(clicked()),this, SLOT(suppr()));
    QObject::connect(quit,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(sauver, SIGNAL(clicked()),this,SLOT(save()));

    update();
}

/*!
 * \brief Affiche la fenêtre visualiserFormation.
 */
void menuFormation::voir()
{
    visualiserFormation* fenetre=new visualiserFormation(m,uvman,m->trouverForm(select->currentText()));
    fenetre->show();
}

/*!
 * \brief Méthode de mise à jour des champs de la fenêtre menuFormation.
 */
void menuFormation::update()
{
    select->clear();
    for(QMap<QString,formation*>::iterator it=m->getQmapIteratorFormbegin();it!=m->getQmapIteratorFormend();it++)
    {
        select->addItem(it.key());
    }
}

/*!
 * \brief Affiche la fenêtre ajoutFormation.
 */
void menuFormation::ajout()
{
    ajoutFormation* fenetre=new ajoutFormation(m, this);
    fenetre->show();
}

/*!
 * \brief Affiche la fenêtre modifFormation.
 *
 * Ce slot affiche la fenêtre permettant de modifier une formation.
 * Cependant elle vérifie préalablement si il existe un étudiant inscrit à cette formation, et dans ce cas, la modification
 * est interdite pour garantir l'intégrité des données. Il faut d'abord supprimer tous les étudiants avant de pouvoir modifier
 * ou supprimer la formation.
 */
void menuFormation::modif()
{
    try{
    DossierManager& dman=DossierManager::getInstance();
    for(iterateur<Dossier> it=dman.getIterateurDos();!it.isDone();it.next())
    {
        if(it.courant()->getFormation()==select->currentText())
        {
            throw UTProfilerException("L'étudiant "+it.courant()->getPrenom()+" "+it.courant()->getNom()+" est inscrit à la formation "+it.courant()->getFormation()+", vous ne pouvez pas la modifier !");
        }
    }
    modifFormation* fenetre=new modifFormation(m,this,m->trouverForm(select->currentText()));
    fenetre->show();
    }
    catch(UTProfilerException& e) {QMessageBox::warning(this,"Erreur",e.getInfo());}
}

/*!
 * \brief Affiche la fenêtre menuFiliere.
 */
void menuFormation::filir()
{
    menuFiliere* f=new menuFiliere();
    f->show();
}
/*!
 * \brief Affiche la fenêtre GestionFiliereFormation.
 */
void menuFormation::ajfilir()
{
    GestionFiliereFormation* f=new GestionFiliereFormation(m->trouverForm(select->currentText()));
    f->show();
}
/*!
 * \brief Supprime la formation sélectionnée.
 *
 * Cette méthode affiche un message demandant confirmation avant de supprimer la formation.
 */
void menuFormation::suppr()
{
    if(QMessageBox::information(this,"Suppression","Voulez-vous supprimer la formation "+select->currentText()+" ?",QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Ok)
    {
        m->supprimerFormation(select->currentText());
        QMessageBox::information(this,"Suppression","Formation supprimée !",QMessageBox::Ok);
        this->update();
    }
}
/*!
 * \brief Déclenche la sauvegarde du cursusManager.
 */
void menuFormation::save()
{
    m->sauverCursus();
}

// ///////////////////////////////////////////////////////////////////
/// \brief Constructeur de la fenêtre ajout formation
/// \param m pointeur vers le cursusManager
/// \param p pointeur vers la fenêtre parente menuFormation
///
ajoutFormation::ajoutFormation(cursusManager* m, menuFormation* p) {

    this->setWindowTitle(QString("Ajout d'une formation"));

    man=m;
    parent=p;
    mainbox=new QVBoxLayout(this);
    hbox1=new QHBoxLayout(this);
    hbox2=new QHBoxLayout(this);
    hbox3=new QHBoxLayout(this);
    hbox4=new QHBoxLayout(this);
    lbl1=new QLabel("Nom de la formation :",this);
    lbl2=new QLabel("Nombre de semestres :",this);
    lbl3=new QLabel("Nombre de crédits :",this);
    lblcs=new QLabel("Nombre de crédits CS requis: ",this);
    lbltm=new QLabel("Nombre de crédits TM requis: ",this);
    lbltsh=new QLabel("Nombre de crédits TSH requis: ",this);
    nom=new QLineEdit(this);
    valider=new QPushButton("Valider",this);
    valider->setDefault(true);
    credits=new QSpinBox(this);
    credits->setRange(100,400);
    credits->setSingleStep(10);
    creditscs=new QSpinBox(this);
    creditscs->setRange(0,200);
    creditstm=new QSpinBox(this);
    creditstm->setRange(0,200);
    creditstsh=new QSpinBox(this);
    creditstsh->setRange(0,200);
    semstr=new QSpinBox(this);
    semstr->setRange(4,6);

    hbox1->addWidget(lbl1);
    hbox1->addWidget(nom);
    hbox2->addWidget(lbl2);
    hbox2->addWidget(semstr);
    hbox2->addWidget(lbl3);
    hbox2->addWidget(credits);
    hbox3->addWidget(lblcs);
    hbox3->addWidget(creditscs);
    hbox3->addWidget(lbltm);
    hbox3->addWidget(creditstm);
    hbox3->addWidget(lbltsh);
    hbox3->addWidget(creditstsh);
    hbox4->addWidget(valider);
    mainbox->addLayout(hbox1);
    mainbox->addLayout(hbox2);
    mainbox->addLayout(hbox3);
    mainbox->addLayout(hbox4);
    this->setLayout(mainbox);

    QObject::connect(valider, SIGNAL(clicked()),this,SLOT(ajout()));
}
/*!
 * \brief Ajoute une formation avec les information entrées.
 */
void ajoutFormation::ajout()
{
    man->ajouterFormation(nom->text(),credits->value(), semstr->value(),creditscs->value(),creditstm->value(),creditstsh->value());
    QMessageBox::information(this,"Ajout d'une formation", "Formation ajoutée !",QMessageBox::Ok);
    parent->update();
    this->close();
}
/*!
 * \brief Constructeur de la fenêtre de modification d'une formation.
 * \param m pointeur vers le cursusManager
 * \param p pointeur vers la fenêtre parente menuFormation
 * \param f pointeur vers la formation concernée par la modification
 */
modifFormation::modifFormation(cursusManager* m, menuFormation *p, formation* f)
{
    this->setWindowTitle(QString("Ajout d'une formation"));
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
    lblcs=new QLabel("Nombre de crédits CS requis: ",this);
    lbltm=new QLabel("Nombre de crédits TM requis: ",this);
    lbltsh=new QLabel("Nombre de crédits TSH requis: ",this);
    hbox4=new QHBoxLayout(this);
    nom=new QLineEdit(this);
    nom->setText(f->getNom());
    valider=new QPushButton("Valider",this);
    valider->setDefault(true);
    credits=new QSpinBox(this);
    credits->setRange(100,400);
    credits->setSingleStep(10);
    credits->setValue(f->getNbCred());
    creditscs=new QSpinBox(this);
    creditscs->setRange(0,200);
    creditscs->setValue(f->getCrRequis(CS));
    creditstm=new QSpinBox(this);
    creditstm->setRange(0,200);
    creditstm->setValue(f->getCrRequis(TM));
    creditstsh=new QSpinBox(this);
    creditstsh->setRange(0,200);
    creditstsh->setValue(f->getCrRequis(TSH));
    semstr=new QSpinBox(this);
    semstr->setRange(4,6);
    semstr->setValue(f->getNbSem());

    hbox1->addWidget(lbl1);
    hbox1->addWidget(nom);
    hbox2->addWidget(lbl2);
    hbox2->addWidget(semstr);
    hbox2->addWidget(lbl3);
    hbox2->addWidget(credits);
    hbox3->addWidget(lblcs);
    hbox3->addWidget(creditscs);
    hbox3->addWidget(lbltm);
    hbox3->addWidget(creditstm);
    hbox3->addWidget(lbltsh);
    hbox3->addWidget(creditstsh);
    hbox4->addWidget(valider);
    mainbox->addLayout(hbox1);
    mainbox->addLayout(hbox2);
    mainbox->addLayout(hbox3);
    mainbox->addLayout(hbox4);
    this->setLayout(mainbox);

    QObject::connect(valider, SIGNAL(clicked()),this,SLOT(modif()));
}
/*!
 * \brief Applique la modification d'une formation avec les paramètres sélectionnés.
 */
void modifFormation::modif()
{
    man->modifFormation(form->getNom(),nom->text(),credits->value(), semstr->value(),creditscs->value(),creditstm->value(),creditstsh->value());
    QMessageBox::information(this,"Modification","Modification effectuée",QMessageBox::Ok);
    parent->update();
    this->close();
}
/*!
 * \brief Constructeur de la fenêtre de visualisation d'une formation
 * \param cmanager pointeur vers le cursusManager
 * \param umanager pointeur vers l'UVManager
 * \param f pointeur vers la formation concernée
 */
visualiserFormation::visualiserFormation(cursusManager* cmanager, UVManager* umanager, formation* f)
{
    this->setWindowTitle(f->getNom());
    cman=cmanager;
    uman=umanager;
    objet=f;
    mainbox=new QHBoxLayout(this);
    vbox1=new QVBoxLayout(this);
    vbox2=new QVBoxLayout(this);
    hbox1=new QHBoxLayout(this);
    hbox2=new QHBoxLayout(this);
    hbox3=new QHBoxLayout(this);
    vbox3=new QVBoxLayout(this);
    form=new QLabel(objet->getNom(),this);
    cred=new QLabel("Nombre de crédits à valider : "+QString::number(objet->getNbCred()),this);
    semstr=new QLabel("Nombre de semestres : "+QString::number(objet->getNbSem()),this);
    ccs=new QLabel("Nombre de crédits CS à valider : "+QString::number(objet->getCrRequis(CS)),this);
    ctm=new QLabel("Nombre de crédits TM à valider : "+QString::number(objet->getCrRequis(TM)),this);
    ctsh=new QLabel("Nombre de crédits TSH à valider : "+QString::number(objet->getCrRequis(TSH)),this);
    retour=new QPushButton("Retour",this);
    modif=new QPushButton("Modifier les UVs",this);
    lbluvs=new QLabel("UVs appartenant à la formation:",this);
    suppr=new QPushButton("Supprimer",this);
    supprUV=new QComboBox(this);
    uvs=new QTextEdit(this);
    uvs->setReadOnly(true);
    uvs->setFixedHeight(300);
    update();

    hbox1->addWidget(form);
    hbox2->addWidget(cred);
    hbox2->addWidget(semstr);
    hbox3->addWidget(retour);
    hbox3->addWidget(modif);
    vbox1->addLayout(hbox1);
    vbox1->addLayout(hbox2);
    vbox1->addLayout(vbox3);
    vbox1->addLayout(hbox3);
    vbox2->addWidget(lbluvs);
    vbox2->addWidget(uvs);
    vbox2->addWidget(supprUV);
    vbox2->addWidget(suppr);
    vbox3->addWidget(ccs);
    vbox3->addWidget(ctm);
    vbox3->addWidget(ctsh);
    mainbox->addLayout(vbox1);
    mainbox->addLayout(vbox2);
    this->setLayout(mainbox);

    QObject::connect(retour, SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(modif,SIGNAL(clicked()),this,SLOT(moduvs()));
    QObject::connect(suppr,SIGNAL(clicked()),this,SLOT(supprimer()));
}
/*!
 * \brief Affiche la fenêtre de modification des UVs appartenant à la formation sélectionnée
 */
void visualiserFormation::moduvs()
{
    selectUVsFormation* fenetre=new selectUVsFormation(cman,uman,objet,this);
    fenetre->show();
}
/*!
 * \brief Mise à jour des champs de la fenêtre visualiserFormation en fonction des opérations effectuées.
 */
void visualiserFormation::update()
{
    supprUV->clear();
    uvs->clear();
    QString txt="";
    for(QMap<QString,UV*>::iterator it=objet->getQmapIteratorUVbegin();it!=objet->getQmapIteratorUVend(); it++)
    {
        if(objet->estObligatoire(it.key()))
        {
            txt+=it.key()+"*\n";
            supprUV->addItem(it.key()+"*");
        }
        else
        {
            txt+=it.key()+"\n";
            supprUV->addItem(it.key());
        }
    }
    uvs->setText(txt);
}
/*!
 * \brief Exécute la désinscription d'une UV d'une formation.
 */
void visualiserFormation::supprimer()
{
    objet->supprimer_UV(supprUV->currentText());
    this->update();
}

/*!
 * \brief constructeur de la fenêtre permettant de sélectionner des UVs appartenant à une formation
 * \param cm pointeur vers le cursusManager
 * \param um pointeur vers l'UVManager
 * \param f pointeur vers la formation concernée
 * \param p pointeur vers la fenêtre parente visualiserFormation
 */
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
    required=new QCheckBox("Rendre cette UV obligatoire",this);

    retour=new QPushButton("Retour",this);
    ajouter=new QPushButton("Ajouter",this);
    mainbox->addWidget(label1);
    mainbox->addWidget(choix);
    mainbox->addWidget(required);
    mainbox->addWidget(ajouter);
    mainbox->addWidget(retour);
    this->setLayout(mainbox);

    QObject::connect(retour,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(ajouter,SIGNAL(clicked()),this,SLOT(ajouterUV()));

    update();
}
/*!
 * \brief Ajoute une UV àla formation sélectionnée.
 */
void selectUVsFormation::ajouterUV()
{
    objet->ajouter_UV(&uman->getUV(choix->currentText()));
    if(required->isChecked()) objet->ajt_UV_obligatoire(choix->currentText());
    QMessageBox::information(this,"Ajout d'une UV","UV "+choix->currentText()+" ajoutée à la formation "+objet->getNom(),QMessageBox::Ok);
    parent->update();
    this->update();
}
/*!
 * \brief Mise à jour des champs de la fenêtre selectUVsFormation
 */
void selectUVsFormation::update()
{
    choix->clear();
    required->setChecked(false);
    for(iterateur<UV>& it=uman->getIterateurForm();!it.isDone();it.next())
    {
        if(objet->trouverUV(it.courant()->getCode())==0) choix->addItem(it.courant()->getCode());
    }
}

// ///////////////////////////////////////////////////////////////////
/// \brief Constructeur de la fenêtre permettant de gérer les inscriptions de filières dans les formations.
/// \param f pointeur vers la formation dont on souhaite gérer les filières.
///
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
/*!
 * \brief Ajoute une filière à la formation.
 */
void GestionFiliereFormation::ajouterFiliere()
{
    cman.inscrFilForm(objet,ajt->currentText());
    QMessageBox::information(this,"Ajout d'une filière","La filière "+ajt->currentText()+" a été ajoutée à la formation "+objet->getNom());
    this->update();
}
/*!
 * \brief Mets à jour les champs de la fenêtre
 */
void GestionFiliereFormation::update()
{
    ajt->clear();
    suppr->clear();
    lbl3->clear();
    QString txt="";
    for(QMap<QString,filiere*>::iterator it=cman.getQmapIteratorFilBegin();it!=cman.getQmapIteratorFilEnd();it++)
    {
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
    lbl3->setText("Filières déjà incluses dans la formation:\n"+txt);
}
/*!
 * \brief Retire une filière de la formation
 */
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

/*!
 * \brief Fenêtre de gestion du menu des filières.
 */
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
/*!
 * \brief Affiche la fenêtre de gestion de filières.
 */
void menuFiliere::voir()
{
    cursusManager& m=cursusManager::getInstance();
    visualiserFiliere* f=new visualiserFiliere(m.trouverFil(select->currentText()));
    f->show();
}
/*!
 * \brief Met à jour les champs de le fenêtre menuFiliere
 */
void menuFiliere::update()
{
    select->clear();
    for(QMap<QString,filiere*>::iterator it=m->getQmapIteratorFilBegin();it!=m->getQmapIteratorFilEnd();it++)
    {
        select->addItem(it.key());
    }
}
/*!
 * \brief Affiche la fenêtre de création d'une nouvelle filière.
 */
void menuFiliere::ajout()
{
    ajoutFiliere* fenetre=new ajoutFiliere(this);
    fenetre->show();
}
/*!
 * \brief Affiche la fenêtre de modification d'une filière.
 */
void menuFiliere::modif()
{
    cursusManager& m=cursusManager::getInstance();
    modifFiliere* f=new modifFiliere(this,m.trouverFil(select->currentText()));
    f->show();
}
/*!
 * \brief Supprime une formation
 */
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
    m->sauverCursus();
}
/*!
 * \brief Constructreur de la fenêtre de création d'une nouvelle filière
 * \param p fenêtre parente
 */
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
/*!
 * \brief Exécute l'ajout d'une nouvelle filière
 */
void ajoutFiliere::ajout()
{
    cursusManager& m=cursusManager::getInstance();
    m.ajouterFiliere(nom->text(),credits->value());
    QMessageBox::information(this,"Ajout d'une filière", "Filière ajoutée !",QMessageBox::Ok);
    parent->update();
    this->close();
}
/*!
 * \brief Constructeur de la fenêtre permetatnt de visualiser une formation
 * \param f Pointeur vers la formation concernée
 */
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
/*!
 * \brief Ouvre la fenêtre de gestion UVs de la filière en cours.
 */
void visualiserFiliere::moduvs()
{
    selectUVsFiliere* f=new selectUVsFiliere(objet,this);
    f->show();
}
/*!
 * \brief Mise à jour des champs de la fenêtre
 */
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
/*!
 * \brief Exécute le retrait d'une UV d'une filière.
 */
void visualiserFiliere::supprimer()
{
    objet->supprimer_UV(supprUV->currentText());
    this->update();
}
/*!
 * \brief Constructeur de la fenêtre de modification d'une formation
 * \param p fenêtre parente
 * \param f filière concernée
 */
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
/*!
 * \brief Exécute la modification de la filière.
 */
void modifFiliere::modif()
{
    cursusManager& man=cursusManager::getInstance();
    man.modifFiliere(fil->getNom(),nom->text(),credits->value());
    QMessageBox::information(this,"Modification","Modification effectuée",QMessageBox::Ok);
    parent->update();
    this->close();
}
/*!
 * \brief Constructeur de la fenêtre selectUVsFiliere
 * \param f pointeur vers la filière concernée
 * \param p pointeur vers la fenêtre parente
 */
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
/*!
 * \brief Exécute l'ajout
 */
void selectUVsFiliere::ajouterUV()
{
    objet->ajouter_UV(&uman.getUV(choix->currentText()));
    QMessageBox::information(this,"Ajout d'une UV","UV "+choix->currentText()+" ajoutée à la filiere "+objet->getNom(),QMessageBox::Ok);
    parent->update();
    this->update();
}
/*!
 * \brief Mise à jour des champs
 */
void selectUVsFiliere::update()
{
    choix->clear();
    for(iterateur<UV>& it=uman.getIterateurForm();!it.isDone();it.next())
    {
        if(objet->trouverUV(it.courant()->getCode())==0) choix->addItem(it.courant()->getCode());
    }
}
