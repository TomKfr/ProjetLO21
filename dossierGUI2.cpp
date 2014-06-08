#include"dossierGUI2.h"
#include"cursus.h"
#include"UTProfiler.h"
#include"dossier.h"
#include<QDebug>
#include<sstream>

/*!
 * \brief Constructeur de la fenêtre de création d'un dossier.
 * \param dm pointeur vers le DossierManager
 * \param p pointeur vers la fenêtre parente
 * \param d pointeur vers le dossier
 */
DossierAjout::DossierAjout(DossierManager& dm, MenuDossier* p, Dossier* d) : dos(d), nbUV(0), nbMaxUV(0), M(dm), parent(p) {
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
    quitter=new QPushButton("4 - Quitter",this);

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
    couche->addWidget(quitter);

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
    QObject::connect(sauver,SIGNAL(clicked()),this,SLOT(disable()));
    QObject::connect(quitter,SIGNAL(clicked()),this,SLOT(close()));
}

/*!
 * \brief Slot exécutant l'ajout du nouveau dossier.
 */
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

/*!
 * \brief Affiche la fenêtre d'ajout d'UVs au dossier.
 */
void DossierAjout::slot_selectUV() {
    bool ok;
    unsigned int n=num->text().toInt(&ok);
    Dossier* d=M.trouverDossier(n);

    AjoutUV* fenetre= new AjoutUV(d, this);
    fenetre->show();
}
void DossierAjout::disable(){sauver->setDisabled(true);}
// PAUSE!!!!!
/*!
 * \brief constructeur de la fenêtre d'ajout d'une UV dans un dossier
 * \param d dossier concerné
 * \param dossier fenêtre parente
 */
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

/*!
 * \brief Exécute l'ajout de l'UV
 */
void AjoutUV::ajout_UVDossier() //Le slot ajout_UVDossier est appelé à chaque appui sur le bouton submit
{
    qDebug()<<"uv ajoutee";
    UVManager& m=UVManager::getInstance();
    UV* nouvelleUV=m.trouverUV(Liste->currentText());
    QString res=Result->currentText();
    dos->ajouterUV(Liste->currentText(),String2Note(Result->currentText()));
    QMessageBox::information(this,"Ajout UV","UV "+nouvelleUV->getCode()+" ajoutée au dossier n°"+QString::number(dos->getNumero()));

}

/*!
 * \brief Mise à jour des champs de la fenêtre
 */
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

/*!
 * \brief Mise à jour des champs de la fenêtre
 */
void AjoutUV::update()
{
    Liste->clear();
    UVManager& m=UVManager::getInstance();
    for(iterateur<UV>& it=m.getIterateurForm();!it.isDone();it.next())
    {
        Liste->addItem(it.courant()->getCode());
    }
}

/*!
 * \brief Ferme la fenêtre
 */
void AjoutUV::end_listeUV() {
    this->close();
}
//MODIF
/*!
 * \brief constructeur de la fenêtre ModifierDossier
 * \param dm pointeur vers le dossierManager
 * \param d pointeur vers le dossier concerné
 * \param md pointeur vers la fenêtre parente
 */
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
    numsem->setValue(d->getNumSemestre());

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
}

/*!
 * \brief Ouvre la fenêtre de modifivation de la formation du dossier
 */
void ModifierDossier::slot_modifFormation() {

    ModifFormation * fenetre= new ModifFormation(dos);
    fenetre->show();
}
/*!
 * \brief Valide la modification de la formation du dossier
 */
void ModifFormation::enregistrer_formation() {
      dossier->setFormation(f->currentText());
      QMessageBox::information(this, "sauvegarde", "Formation enregistree");
      this->close();
}
/*!
 * \brief Constructeur de la fenêtre de modification de la formation
 * \param d Dossier concerné par la formation
 */
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
/*!
 * \brief Mise à jour des champs de la fenêtre
 */
void ModifFormation::update() {

        f->clear();
        cursusManager& m=cursusManager::getInstance();
        for(QMap<QString,formation*>::iterator it=m.getQmapIteratorFormbegin();it!=m.getQmapIteratorFormend();it++)
        {
            f->addItem(it.key());
        }
}
/*!
 * \brief exécute la modification du Dossier
 */
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

/*!
 * \brief constructeur de la fenêtre de modification
 * \param d dossier concerné
 */
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
    resultats->setDisabled(true);
    update();

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
    QObject::connect(uvs,SIGNAL(currentTextChanged(QString)),this,SLOT(affResult()));

}
/*!
 * \brief Mise à jour des champs de la fenêtre
 */
void ModifUV::update() {
    uvs->clear();
    resultats->clear();
    for(QMap<QString,Note>::iterator it=dos->getQmapIteratorUVbegin(); it!=dos->getQmapIteratorUVend();++it)
    {
        uvs->addItem(it.key());
        resultats->addItem(Note2String(it.value()));
    }
}
/*!
 * \brief Ouvre la fenêtre de modification du résultat d'une UV
 */
void ModifUV::modifierResult() {

    ModifResult* fenetre= new ModifResult(dos, this);
    fenetre->show();
}
/*!
 * \brief Affiche le résultat correspondant à l'UV affichée dans la combobox uvs.
 *
 * Ce slot est appelé lors d'une modification de la combobox uvs. Ainsi,
 * lorsque l'on change l'uv affichée, le résultat correspondant s'affiche
 * automatiquement sur la combobox resultats.
 */
void ModifUV::affResult()
{
    QMap<QString,Note>::const_iterator it=dos->trouverUV(uvs->currentText());
    resultats->setCurrentText(Note2String(it.value()));
}

/*!
 * \brief constructeur de la fenêtre de modification du résultat associé à une UV
 * \param d dossier concerné
 * \param mu fenêtre parente
 */
ModifResult::ModifResult(Dossier * d, ModifUV* mu) : dos(d), modifuv(mu) {
    explication=new QLabel("UVs actuelles du dossier et resultat associe :", this);

    uvs=new QComboBox(this);
    resultats=new QComboBox(this);
    valider=new QPushButton("Valider", this);
    retour=new QPushButton("Retour", this);

    coucheH1=new QHBoxLayout;
    coucheH0= new QHBoxLayout;
    coucheH2= new QHBoxLayout;

    update();

    coucheH0->addWidget(explication);
    coucheH0->addWidget(uvs);
    coucheH0->addWidget(resultats);
    coucheH1->addWidget(valider);
    coucheH2->addWidget(retour);

    couche=new QVBoxLayout;
    couche->addLayout(coucheH0);
    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    setLayout(couche);

    QObject::connect(valider, SIGNAL(clicked()), this, SLOT(enregistrer()));
    QObject::connect(retour, SIGNAL(clicked()), this, SLOT(fin2()));
    QObject::connect(uvs,SIGNAL(currentTextChanged(QString)),this,SLOT(affResult()));

}
/*!
 * \brief Ferme la fenêtre
 */
void ModifResult::fin2() {this->close();}
/*!
 * \brief exécute les modifications apportées aux résultats
 */
void ModifResult::enregistrer() {
    dos->setResultat(uvs->currentText(),String2Note(resultats->currentText()));
    modifuv->update();
    QMessageBox::information(this, "sauvegarde", " Resultat enregistre");
}
/*!
 * \brief Mets à jour les champs de la fenêtre
 */
void ModifResult::update() {

    qDebug()<<"dans modifresult";
    uvs->clear();
    resultats->clear();
    resultats->addItem("A");
    resultats->addItem("B");
    resultats->addItem("C");
    resultats->addItem("D");
    resultats->addItem("E");
    resultats->addItem("F");
    resultats->addItem("FX");
    resultats->addItem("EC");

    for(QMap<QString,Note>::iterator it=dos->getQmapIteratorUVbegin(); it!=dos->getQmapIteratorUVend();++it)
    {
        uvs->addItem(it.key());
    }
    affResult();
}
/*!
 * \brief Affiche le résultat correspondant à l'UV affichée dans la combobox uvs.
 *
 * Ce slot est appelé lors d'une modification de la combobox uvs. Ainsi,
 * lorsque l'on change l'uv affichée, le résultat correspondant s'affiche
 * automatiquement sur la combobox resultats.
 */
void ModifResult::affResult()
{
    QMap<QString,Note>::const_iterator it=dos->trouverUV(uvs->currentText());
    resultats->setCurrentText(Note2String(it.value()));
}
/*!
 * \brief Ouvre la fenêtre de modification des uvs associées au dossier.
 */
void ModifierDossier::slot_modifUV(){
    ModifUV * fenetre= new ModifUV(dos);
    fenetre->show();
}
/*!
 * \brief Ouvre la fenêtre de suppression d'une UV du dossier
 */
void ModifUV::supprimerUV() {
    SuppressionUV * fenetre= new SuppressionUV(dos);
    fenetre->show();
}
/*!
 * \brief Ouvre la fenêtre d'ajout d'une UV au Dossier
 */
void ModifUV::ajouterUV() {
    AjoutUV * fenetre= new AjoutUV(dos);
    fenetre->show();
}
/*!
 * \brief Fermeture de la fenêtre
 */
void ModifUV::finUV() {
    this->close();
}
/*!
 * \brief Constructeur de la fenêtre de suppression d'une UV.
 * \param d dossier concerné
 */
SuppressionUV::SuppressionUV(Dossier* d) : dos(d)
{
    liste=new QComboBox;
    update();
    supprimer=new QPushButton("Supprimer cette UV de mon dossier", this);
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

}
/*!
 * \brief Ferme la fenêtre
 */
void SuppressionUV::finSuppression(){

    this->close();
}
/*!
 * \brief exécute la suppression d'une UV du dossier
 */
void SuppressionUV::suppression_une_uv(){

    const QString& uv=liste->currentText();
    UVManager& uvm=UVManager::getInstance();
    UV* u=uvm.trouverUV(uv);

    dos->supprimerUV(u);
}
/*!
 * \brief Mise à jour des champs de la fenêtre
 */
void SuppressionUV::update() {

    qDebug()<<"dans suppr update";
    liste->clear();

    for(QMap<QString,Note>::iterator it=dos->getQmapIteratorUVbegin(); it!=dos->getQmapIteratorUVend();++it)
    {
        liste->addItem(it.key());
    }

}
/*!
 * \brief constructeur de la fenêtre d'ajout d'équivalences au dossier
 * \param d dossier concerné
 * \param m fenêtre parente
 */
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
/*!
 * \brief Ouvre la fenêtre d'ajout des équivalences au dossier.
 */
void DossierAjout::select_equivalences(){
    AjoutEquivalences* fenetre = new AjoutEquivalences(dos);
    qDebug()<<"dos dans dossier ajout"<<dos;
    fenetre->show();
}
/*!
 * \brief exécute l'ajout d'une équivalence au dossier.
 */
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
/*!
 * \brief constructeur de la fenêtre de modification des équivalences
 * \param dos dossier concerné
 */
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
    QObject::connect(quitter, SIGNAL(clicked()), this, SLOT(slot_quitter()));
}
/*!
 * \brief Mise à jour des champs de la fenêtre
 */
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
/*!
 * \brief Ouvre la fenêtre de modification des équivalences
 */
void ModifierDossier::slot_modifEquivalences() {

    ModifEquivalences* fenetre= new ModifEquivalences(dos);
    fenetre->show();

}
/*!
 * \brief Ouvre la fenêtre d'ajout d'une nouvelle équivalence.
 */
void ModifEquivalences::slot_ajouter() {

    AjoutEquivalences* fenetre = new AjoutEquivalences(dossier, this);
    fenetre->show();
}
/*!
 * \brief constructeur de la fenêtre de modification d'une équivalence.
 * \param d pointeur vers le dossier concerné
 * \param e pointeur vers l'objet equivalences concerné
 * \param m pointeur vers la fenêtre parente
 */
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
/*!
 * \brief exécute la modification de l'équivalence sélectionnée
 */
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
    //unsigned int nb=dossier->getNbEquivalences();
    unsigned int i=0;

    while (tab[i]->getDescription()!=choix->currentText()) {i++;}

    EquivalenceEditeur * fenetre= new EquivalenceEditeur(dossier, tab[i], this);
    fenetre->show();
}

void ModifEquivalences::slot_quitter() {this->close();}
/*!
 * \brief supprime l'équivalence sélectionnée
 */
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




