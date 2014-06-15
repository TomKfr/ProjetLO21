#include "completionGUI.h"
#include "UTProfiler.h"
#include "completion.h"
#include "cursus.h"

#include <QMessageBox>
#include<QDir>

Reponse StringToReponse(const QString& r){
    try{
        if (r=="Valider") {return Valider; }
        else if (r=="Refuser") {return Refuser; }
        else if (r=="Retarder") {return Retarder; }
        else if(r=="Avancer") { return Avancer; }
            throw UTProfilerException(QString("erreur, StringToSaison, saison ")+r+" inexistante");
        }

    catch(UTProfilerException& e){QMessageBox::warning(0,"Erreur",e.getInfo());}

}

QString ReponseToString(Reponse c){
    try{
        switch(c){
        case Valider: return "Valider";
        case Refuser: return "Refuser";
        case Retarder: return "Retarder";
        case Avancer: return "Avancer";
        default: throw UTProfilerException("erreur, reponse non traitee",__FILE__,__LINE__);
        }
    }
    catch(UTProfilerException& e){QMessageBox::warning(0,"Erreur",e.getInfo());}
    return "";
}
/*!
 * \brief Fenêtre de gestion des souhaits
 * \param d pointeur vers le dossier concerné
 * \param sht pointeur vers l'objet souhaits du dossier (vaut 0 si non créé)
 */
MenuSouhaits::MenuSouhaits(Dossier *d, souhaits *sht)
{
    this->setWindowTitle("Gérer les souhaits");
    dos=d;
    objet=sht;

    mainbox=new QVBoxLayout(this);
    hbox1=new QHBoxLayout(this);
    hbox2=new QHBoxLayout(this);
    hbox3=new QHBoxLayout(this);
    hbox4=new QHBoxLayout(this);
    vbox1=new QVBoxLayout(this);
    vbox2=new QVBoxLayout(this);
    vbox3=new QVBoxLayout(this);
    vbox4=new QVBoxLayout(this);
    titre=new QLabel("Gérer les souhaits de ",this);
    lblneutre=new QLabel("UVs non associées à une liste",this);
    txtexigees=new QLabel("UVs exigees :",this);
    txtpreferees=new QLabel("UVS souhaitées :",this);
    txtrejetees=new QLabel("UVs rejetees :",this);
    listexigees=new QLabel("",this);
    listpreferees=new QLabel("",this);
    listrejetees=new QLabel("",this);
    exigeebutton=new QRadioButton("J'exige de faire cette UV",this);
    prefereebutton=new QRadioButton("J'aimerais faire cette UV",this);
    rejeteebutton=new QRadioButton("Je ne veux pas faire cette UV",this);
    valider1=new QPushButton("Ajouter",this);
    supprexigee=new QPushButton("Supprimer des exigences",this);
    supprpreferee=new QPushButton("Supprimer des préférences",this);
    supprrejetee=new QPushButton("Supprimer des rejets",this);
    sauver=new QPushButton("Sauvegarder",this);
    terminer=new QPushButton("Terminé",this);
    choix1=new QComboBox(this);
    choix2=new QComboBox(this);
    choix3=new QComboBox(this);
    choix4=new QComboBox(this);

    mainbox->addLayout(hbox1);
    mainbox->addLayout(hbox2);
    mainbox->addLayout(hbox3);
    hbox2->addLayout(vbox1);
    hbox2->addLayout(hbox4);
    hbox4->addLayout(vbox2);
    hbox4->addLayout(vbox3);
    hbox4->addLayout(vbox4);

    hbox1->addWidget(titre);
    vbox1->addWidget(lblneutre);
    vbox1->addWidget(choix1);
    vbox1->addWidget(exigeebutton);
    vbox1->addWidget(prefereebutton);
    vbox1->addWidget(rejeteebutton);
    vbox1->addWidget(valider1);

    vbox2->addWidget(txtexigees);
    vbox2->addWidget(listexigees);
    vbox2->addWidget(choix2);
    vbox2->addWidget(supprexigee);

    vbox3->addWidget(txtpreferees);
    vbox3->addWidget(listpreferees);
    vbox3->addWidget(choix3);
    vbox3->addWidget(supprpreferee);

    vbox4->addWidget(txtrejetees);
    vbox4->addWidget(listrejetees);
    vbox4->addWidget(choix4);
    vbox4->addWidget(supprrejetee);

    hbox3->addWidget(sauver);
    hbox3->addWidget(terminer);

    this->setLayout(mainbox);

    QObject::connect(valider1,SIGNAL(clicked()),this,SLOT(ajUV()));
    QObject::connect(supprexigee,SIGNAL(clicked()),this,SLOT(suprexigee()));
    QObject::connect(supprpreferee,SIGNAL(clicked()),this,SLOT(suprpref()));
    QObject::connect(supprrejetee,SIGNAL(clicked()),this,SLOT(suprrejet()));
    QObject::connect(terminer,SIGNAL(clicked()),this,SLOT(fermer()));

    update();
}
/*!
 * \brief Mise à jour des champs de la fenêtre
 */
void MenuSouhaits::update()
{
    UVManager& uman=UVManager::getInstance();
    cursusManager& cman=cursusManager::getInstance();
    QString txtform=dos->getFormation();
    formation* form=cman.trouverForm(txtform);
    choix1->clear();
    choix2->clear();
    choix3->clear();
    choix4->clear();
    QString list1;
    QString list2;
    QString list3;
    for(iterateur<UV>& it=uman.getIterateurForm();!it.isDone();it.next())
    {
        if(!(dos->estValidee(it.courant()->getCode())))
        {
            if(objet->estExigee(it.courant()->getCode()))
            {
                list1+=it.courant()->getCode()+"\n";
                choix2->addItem(it.courant()->getCode());
            }
            else
            {
                if(objet->estPreferee(it.courant()->getCode()))
                {
                    list2+=it.courant()->getCode()+"\n";
                    choix3->addItem(it.courant()->getCode());
                }
                else
                {
                    if(objet->estRejetee(it.courant()->getCode()))
                    {
                        list3+=it.courant()->getCode()+"\n";
                        choix4->addItem(it.courant()->getCode());
                    }
                    else
                    {
                        if(!form->estObligatoire(it.courant()->getCode())) choix1->addItem(it.courant()->getCode());
                    }
                }
            }
        }

        listexigees->setText(list1);
        listpreferees->setText(list2);
        listrejetees->setText(list3);
    }
}
/*!
 * \brief Ajoute une UV à la liste correspondante au radio-bouton coché.
 */
void MenuSouhaits::ajUV()
{
    if(exigeebutton->isChecked()) objet->Ajt_exigence(choix1->currentText());
    if(prefereebutton->isChecked()) objet->Ajt_preference(choix1->currentText());
    if(rejeteebutton->isChecked()) objet->Ajt_rejet(choix1->currentText());
    update();
}
/*!
 * \brief Appelle la méthode de retrait d'une UV de la liste des UVs exigées.
 */
void MenuSouhaits::suprexigee()
{
    objet->Suppr_exigence(choix2->currentText());
    update();
}
/*!
 * \brief Appelle la méthode de retrait d'une UV de la liste des UVs préférées.
 */
void MenuSouhaits::suprpref()
{
    objet->Suppr_prefernce(choix3->currentText());
    update();
}
/*!
 * \brief Appelle la méthode de retrait d'une UV de la liste des UVs rejetées.
 */
void MenuSouhaits::suprrejet()
{
     objet->Suppr_rejet(choix4->currentText());
     update();
}
/*!
 * \brief Sauvegarde le dossier et ferme la fenêtre.
 */
void MenuSouhaits::fermer()
{
    DossierManager& dman=DossierManager::getInstance();
    dman.save();
    this->close();
}

//commenté car pb d'inclusion empechant la compilation
/*!
 * \brief Affiche le menu de gestion de la complétion automatique.
 * \param d Pointeur vers le dossier sur lequel on veut travailler.
 */
MenuCompletion::MenuCompletion(Dossier* d) : dos(d) {
    this->setWindowTitle("Choix de l'operation");

    calcul=new QPushButton("Lancer le calcul d'une proposition", this);

    historique=new QPushButton("Consulter l'historique des propositions", this);
    souhaits=new QPushButton("Saisir mes souhaits d'UV", this);
    previsions=new QPushButton("Saisir mes previsions de semestre à l'etranger", this);
    terminer=new QPushButton("Retour", this);


    coucheH1=new QHBoxLayout;
    coucheH1->addWidget(calcul);
    coucheH1->addWidget(historique);

    coucheH2=new QHBoxLayout;
    coucheH2->addWidget(souhaits);

    coucheH3=new QHBoxLayout;
    coucheH3->addWidget(previsions);

    coucheH4=new QHBoxLayout;
    coucheH4->addWidget(terminer);

    couche=new QVBoxLayout;
    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);
    couche->addLayout(coucheH4);

    setLayout(couche);

    QObject::connect(historique,SIGNAL(clicked()),this,SLOT(consulter_historique()));
    QObject::connect(souhaits,SIGNAL(clicked()),this,SLOT(saisir_souhaits()));
    QObject::connect(previsions,SIGNAL(clicked()),this,SLOT(saisir_previsions()));
    QObject::connect(calcul,SIGNAL(clicked()),this,SLOT(lancer_completion()));
    QObject::connect(terminer,SIGNAL(clicked()),this,SLOT(fin()));

}
/*!
 * \brief Charge les complétions éventuellement réalisées et ferme la fenêtre.
 */
void MenuCompletion::fin() {
    ChoixManager& cm=ChoixManager::getInstance();
    cm.load_completion();
    this->close();}
/*!
 * \brief Affiche la fenêtre permettant de consulter l'historique des propositions.
 */
void MenuCompletion::consulter_historique() {
    qDebug()<<"dans le slot";
    Historique * fenetre = new Historique(dos);
    fenetre->show();
}
/*!
 * \brief Fenêtre d'affichage d'une proposition
 * \param dossier pointeur vers le dossier concerné
 */
Proposition::Proposition(Dossier * dossier) : d(dossier) {

    this->setWindowTitle(QString("Propositions jusqu'à la fin de vos études"));

    semestreLabel=new QLabel("Afficher la proposition pour le semestre : ", this);
    saison_concernee=new QComboBox(this) ;
    saison_concernee->addItem("Automne");
    saison_concernee->addItem("Printemps");

    annee_concernee=new QComboBox(this) ;
    annee_concernee->addItem("2014");
    annee_concernee->addItem("2015");
    annee_concernee->addItem("2016");
    annee_concernee->addItem("2017");
    annee_concernee->addItem("2018");


    afficher=new QPushButton("Afficher", this); //affiche pour un semestre
    terminer=new QPushButton("Enregistrer et fermer", this);
    reponseLabel=new QLabel("Votre reponse à ces propositions : ", this);
    reponse=new QComboBox(this);

    reponse->addItem("Valider");
    reponse->addItem("Refuser");
    reponse->addItem("Avancer");
    reponse->addItem("Retarder");

    coucheH1=new QHBoxLayout;
    coucheH1->addWidget(semestreLabel);
    coucheH1->addWidget(saison_concernee);
    coucheH1->addWidget(annee_concernee);
    coucheH1->addWidget(afficher);

    coucheH2=new QHBoxLayout;
    coucheH2->addWidget(reponseLabel);
    coucheH2->addWidget(reponse);

    coucheH3=new QHBoxLayout;
    coucheH3->addWidget(terminer);

    couche=new QVBoxLayout;
    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);

    this->setLayout(couche);

    QObject::connect(afficher,SIGNAL(clicked()),this,SLOT(afficher_proposition()));
    QObject::connect(terminer,SIGNAL(clicked()),this,SLOT(enregistrer_reponse()));


}
/*!
 * \brief Enregistre la réponse donnée par l'utilisateur pour la proposition en cours.
 */
void Proposition::enregistrer_reponse() {
    ChoixManager& cm=ChoixManager::getInstance();
    ChoixAppli * c = cm.getLastProposition();
    Reponse rep=StringToReponse(reponse->currentText());
    c->setReponse(rep);
    cm.save_completion();
    this->close();
}
/*!
 * \brief vérifie si une proposition a été faite pour un semestre donné
 * \param s semetre donné
 * \param c proposition globale
 * \return vrai si il existe une proposition pour le semestre passé en paramètre, faux sinon.
 */
bool Proposition::verifierValiditeSemestre(Semestre s, ChoixAppli * c){

    //s'il fait partie des semestres de choix appli concerne
    ChoixAppliSemestre ** propositionSemestre = c->getListePropositions();
    for (unsigned int i=0; i<c->getNbSemestres(); i++) {if (s==propositionSemestre[i]->getSemestre()) return 1;}
    return 0;

}
/*!
 * \brief Ouvre la fenêtre d'affichage d'une proposition
 */
void Proposition::afficher_proposition() {
    //Recuperer le semestre

    ChoixManager& c=ChoixManager::getInstance();
    Semestre s(Printemps, 2014);
    Saison  s2=StringToSaison(saison_concernee->currentText());
    s.setSaison(s2);
    bool ok;
    const QString& n1=annee_concernee->currentText();
    unsigned int n2=n1.toInt(&ok);
    s.setAnnee(n2);

    ChoixAppli * currentChoixAppli=c.getLastProposition();
    if (!verifierValiditeSemestre(s, currentChoixAppli)) QMessageBox::information(this,"Modification","Semestre lors duquel vous aurez sûrement fini vos études!",QMessageBox::Ok);

    else {
    ChoixAppliSemestre * choix = currentChoixAppli->trouverChoix(s);

    //puis faire appel à la fenetre daffichage

    AfficherProposition * fenetre = new AfficherProposition(choix);
    fenetre->show();

    }

}
/*!
 * \brief constructeur de la fenêtre d'affcihage d'une proposition
 * \param choix pointeur vers la proposition à afficher
 */
AfficherProposition::AfficherProposition(ChoixAppliSemestre *choix) : c(choix) {
    QString listeUV="UVs proposees  : ";


    for (QMap<QString,UV*>::const_iterator it=c->getQmapIteratorUVbegin(); it!=c->getQmapIteratorUVend(); ++it) {
        listeUV+=it.key()+" ; ";
    }

    QString semestre=SaisonToString(c->getSemestre().getSaison());
    semestre+=" ";
    semestre+=QString::number(c->getSemestre().getAnnee());

    blabla = new QLabel("Proposition pour le semestre : "+semestre, this);

    credits = new QLabel ("Cette proposition vous rapporte "+QString::number(c->getNbCredits())+" credits." , this);
    uvs = new QLabel(listeUV, this);

    terminer= new QPushButton("Retourner consulter un autre semestre proposé", this);

     coucheH1=new QHBoxLayout;
     coucheH1->addWidget(blabla);

     coucheH2=new QHBoxLayout;
     coucheH2->addWidget(uvs);

     coucheH3=new QHBoxLayout;
     coucheH3->addWidget(credits);

     coucheH4=new QHBoxLayout;
     coucheH4->addWidget(terminer);

     couche=new QVBoxLayout;
     couche->addLayout(coucheH1);
     couche->addLayout(coucheH2);
     couche->addLayout(coucheH3);
     couche->addLayout(coucheH4);


    this->setLayout(couche);

    QObject::connect(terminer,SIGNAL(clicked()),this,SLOT(fin()));
}

void AfficherProposition::fin() {this->close();}

/*!
 * \brief Historique::Historique
 * \param d pointeur vers le dossier.
 */
Historique::Historique(Dossier * d) : dos(d) {

intitule=new QLabel("Récapitulatif des propositions de l'application pour votre dossier : ", this);

QString texte="";


ChoixManager& cm=ChoixManager::getInstance();

ChoixAppli ** choixDossier = cm.trouverPropositionsDossier(dos);
unsigned int nb= cm.trouverNbPropositionsDossier(dos);

if (choixDossier==0) texte="Aucune proposition n'a été générée jusqu'à ce jour.";

else {

    for (unsigned int i=0; i<nb; i++)
    {
        ChoixAppliSemestre** ensemble=choixDossier[i]->getListePropositions();

        texte+="Identifiant de la proposition : "+QString::number(choixDossier[i]->getIdentifiant())+"\n";

        for (unsigned int j=0; j<choixDossier[i]->getNbSemestres(); j++) {

            QString semestre=SaisonToString(ensemble[j]->getSemestre().getSaison());
            semestre+=" ";
            semestre+=QString::number(ensemble[j]->getSemestre().getAnnee());

            texte+="\n Pour le semestre "+semestre;

            texte+="\n Les UVs proposees sont  : ";

            for (QMap<QString,UV*>::const_iterator it=ensemble[j]->getQmapIteratorUVbegin(); it!=ensemble[j]->getQmapIteratorUVend(); ++it) {
                texte+=it.key()+" ; ";

            }

            texte+="\n Credits rapportés : "+QString::number(ensemble[j]->getNbCredits())+"\n";

        }//fin for j
        QString rep = ReponseToString(choixDossier[i]->getReponse());
        texte+="\nReponse accordee à cette proposition : "+rep;
        texte+="\n \n \n";

    }//fin for i

}//fin else


contenu=new QLabel(texte, this);
retour= new QPushButton("Retour", this);

coucheH1=new QHBoxLayout;
coucheH1->addWidget(intitule);


coucheH2=new QHBoxLayout;
coucheH2->addWidget(contenu);

coucheH3=new QHBoxLayout;
coucheH3->addWidget(retour);

couche=new QVBoxLayout;
couche->addLayout(coucheH1);
couche->addLayout(coucheH2);
couche->addLayout(coucheH3);

this->setLayout(couche);

 QObject::connect(retour,SIGNAL(clicked()),this,SLOT(fin()));

}


void Historique::fin() {this->close();}

/*!
 * \brief Ouvre la fenêtre permettant à l'utilisateur de saisir ses souhaits.
 */
void MenuCompletion::saisir_souhaits() {
    MenuSouhaits* fenetre=new MenuSouhaits(dos, dos->getSouhaits());
    fenetre->show();
}
/*!
 * \brief Ouvre la fenêtre permettant à l'tilisateur de saisir un semestre prévu
 */
void MenuCompletion::saisir_previsions() {

    menuprevision * fenetre= new menuprevision(dos);
    fenetre->show();
}
/*!
 * \brief Lance l'exécution du calcul de complétion automatique
 */
void MenuCompletion::lancer_completion() {

    ChoixManager& cm=ChoixManager::getInstance();
    if (!(cm.verifCompletion(dos))) //si la formation a un nb de credits et des uvs incohérents
          QMessageBox::information(this,"Impossible","Calcul impossible étant donnée la formation ! Modifiez la formation !",QMessageBox::Ok);

    else { cm.calculCompletion(dos);

        if (cm.getCreationLastProposition()==false)  QMessageBox::information(this,"Impossible","Vous avez déjà terminé vos études : aucune proposition générée",QMessageBox::Ok);
        else {
           Proposition * fenetre=new Proposition(dos);
           fenetre->show();
          }
    }
}
/*!
 * \brief constructeur de la fenêtre de saisie d'un semestre prévu.
 * \param d pointeur vers le dossier concerné
 */
menuprevision::menuprevision(Dossier *d): dos(d)
{
    this->setWindowTitle("Saisie d'une prévision");
    mainbox=new QVBoxLayout(this);
    hbox1=new QHBoxLayout(this);
    hbox2=new QHBoxLayout(this);
    hbox3=new QHBoxLayout(this);
    vbox1=new QVBoxLayout(this);
    vbox2=new QVBoxLayout(this);
    vbox3=new QVBoxLayout(this);
    lbldest=new QLabel("Destination : ",this);
    lblcs=new QLabel("CS",this);
    lbltm=new QLabel("TM",this);
    lbltsh=new QLabel("TSH",this);
    destination=new QLineEdit(this);
    borneinfCS=new QSpinBox(this);
    borneinfCS->setRange(0,40);
    bornesupCS=new QSpinBox(this);
    bornesupCS->setRange(0,40);
    borneinfTM=new QSpinBox(this);
    borneinfTM->setRange(0,40);
    bornesupTM=new QSpinBox(this);
    bornesupTM->setRange(0,40);
    borneinfTSH=new QSpinBox(this);
    borneinfTSH->setRange(0,40);
    bornesupTSH=new QSpinBox(this);
    bornesupTSH->setRange(0,40);
    valider=new QPushButton("Valider",this);
    annuler=new QPushButton("Terminé",this);

    mainbox->addLayout(hbox1);
    mainbox->addLayout(hbox2);
    mainbox->addLayout(hbox3);
    hbox2->addLayout(vbox1);
    hbox2->addLayout(vbox2);
    hbox2->addLayout(vbox3);

    hbox1->addWidget(lbldest);
    hbox1->addWidget(destination);
    vbox1->addWidget(lblcs);
    vbox1->addWidget(bornesupCS);
    vbox1->addWidget(borneinfCS);
    vbox2->addWidget(lbltm);
    vbox2->addWidget(bornesupTM);
    vbox2->addWidget(borneinfTM);
    vbox3->addWidget(lbltsh);
    vbox3->addWidget(bornesupTSH);
    vbox3->addWidget(borneinfTSH);
    hbox3->addWidget(annuler);
    hbox3->addWidget(valider);

    update();

    QObject::connect(valider,SIGNAL(clicked()), this, SLOT(valider_prev()));
    QObject::connect(annuler,SIGNAL(clicked()),this,SLOT(close()));

    this->setLayout(mainbox);
}
/*!
 * \brief Mise à jour des champs de la fenêtre
 */
void menuprevision::update()
{
    prevision* prev=dos->getprevisions();
    if(prev)
    {
       destination->setText(prev->getdestination());
       borneinfCS->setValue(prev->getbiCS());
       borneinfTM->setValue(prev->getbiTM());
       borneinfTSH->setValue(prev->getbiTSH());
       bornesupCS->setValue(prev->getbsCS());
       bornesupTM->setValue(prev->getbsTM());
       bornesupTSH->setValue(prev->getbsTSH());
    }
}
/*!
 * \brief valide et ajoute la prévision au dossier.
 */
void menuprevision::valider_prev()
{
    dos->setprevision(new prevision(destination->text(),bornesupCS->value(),borneinfCS->value(),bornesupTM->value(),borneinfTM->value(),bornesupTSH->value(),borneinfTSH->value()));
    update();
}
