#include "completionGUI.h"
#include "UTProfiler.h"
#include "completion.h"

#include <QMessageBox>
#include<QDir>



MenuSouhaits::MenuSouhaits(souhaits *sht)
{
    this->setWindowTitle("Gérer les souhaits");
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

void MenuSouhaits::update()
{
    UVManager& uman=UVManager::getInstance();
    choix1->clear();
    choix2->clear();
    choix3->clear();
    choix4->clear();
    QString list1;
    QString list2;
    QString list3;
    for(iterateur<UV>& it=uman.getIterateurForm();!it.isDone();it.next())
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
                    choix1->addItem(it.courant()->getCode());
                }
            }
        }

        listexigees->setText(list1);
        listpreferees->setText(list2);
        listrejetees->setText(list3);
    }
}

void MenuSouhaits::ajUV()
{
    if(exigeebutton->isChecked()) objet->Ajt_exigence(choix1->currentText());
    if(prefereebutton->isChecked()) objet->Ajt_preference(choix1->currentText());
    if(rejeteebutton->isChecked()) objet->Ajt_rejet(choix1->currentText());
    update();
}
void MenuSouhaits::suprexigee()
{
    objet->Suppr_exigence(choix2->currentText());
    update();
}
void MenuSouhaits::suprpref()
{
    objet->Suppr_prefernce(choix3->currentText());
    update();
}
void MenuSouhaits::suprrejet()
{
     objet->Suppr_rejet(choix4->currentText());
     update();
}
void MenuSouhaits::fermer()
{
    DossierManager& dman=DossierManager::getInstance();
    dman.save();
    this->close();
}

//commenté car pb d'inclusion empechant la compilation

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

void MenuCompletion::fin() {
    ChoixManager& cm=ChoixManager::getInstance();
    cm.load_completion();
    this->close();}

void MenuCompletion::consulter_historique() {

    Historique * fenetre = new Historique();
    fenetre->show();
}

Proposition::Proposition(Dossier * dossier) : d(dossier) {

    this->setWindowTitle(QString("Propositions semestre par semestre jusqu'à la fin de vos études"));


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

    update();

    this->setLayout(couche);

    QObject::connect(afficher,SIGNAL(clicked()),this,SLOT(afficher_proposition()));
    QObject::connect(terminer,SIGNAL(clicked()),this,SLOT(enregistrer_reponse()));


}

void Proposition::enregistrer_reponse() { //a completer

}

void Proposition::afficher_proposition() {
    //Recuperer le semestre
    qDebug()<<"afficher proposition1";
    Semestre s(Printemps, 2014);
    qDebug()<<"afficher proposition2";
    Saison  s2=StringToSaison(saison_concernee->currentText());
    qDebug()<<"afficher proposition3";// OK
    s.setSaison(s2);
    bool ok;
    const QString& n1=annee_concernee->currentText();
    unsigned int n2=n1.toInt(&ok);
    s.setAnnee(n2);

    qDebug()<<"coucou"; // OK

    ChoixAppliSemestre * choix = c->trouverChoix(s); //fonctionne pas->normal
    qDebug()<<choix;
    //puis faire appel à la fenetre daffichage
    AfficherProposition * fenetre = new AfficherProposition(choix);
    fenetre->show();

}

AfficherProposition::AfficherProposition(ChoixAppliSemestre *choix) : c(choix) {

    blabla = new QLabel("Proposition pour le semestre  : ", this);
    credits = new QLabel ("Cette proposition vous rapporte " , this);
    uvs = new QLabel("", this);

    //iterateur
    terminer= new QPushButton("Retour", this);

    coucheH1=new QHBoxLayout(this);
    coucheH1->addWidget(blabla);

    coucheH2=new QHBoxLayout(this);
    coucheH2->addWidget(credits);

    coucheH3=new QHBoxLayout(this);
    coucheH3->addWidget(uvs);

    couche=new QVBoxLayout(this);
    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);
    couche->addLayout(coucheH4);

    this->setLayout(couche);


    QObject::connect(terminer,SIGNAL(clicked()),this,SLOT(fin()));


}

void AfficherProposition::fin() {this->close();}

Historique::Historique() {}

void MenuCompletion::saisir_souhaits() {
    MenuSouhaits* fenetre=new MenuSouhaits(dos->getSouhaits());
    fenetre->show();
}

void MenuCompletion::saisir_previsions() {

    /*MenuPrevisions * fenetre= new MenuPrevisions(dos->getPrevisions());
    fenetre->show();*/
}

void MenuCompletion::lancer_completion() {
    Proposition * fenetre=new Proposition(dos);
    fenetre->show();
}
