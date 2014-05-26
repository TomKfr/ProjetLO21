#include "uvGUI.h"
#include "UTProfiler.h"
#include "cursus.h"
#include<QDebug>

Debut::Debut() {
    qDebug()<<"coucou1";

    this->setWindowTitle(QString("Operation choisie sur les UVs ?"));

    ajouter=new QPushButton("Ajouter une UV", this);
    modifier=new QPushButton("Afficher/Modifier des informations sur une UV", this);
    sup=new QPushButton("Supprimer une UV", this);
    terminer=new QPushButton("Opérations sur les UVs terminées", this);

    coucheH=new QHBoxLayout;
    coucheH->addWidget(sup);
    coucheH->addWidget(ajouter);
    coucheH->addWidget(modifier);
    coucheH->addWidget(terminer);

    coucheV=new QVBoxLayout;
    coucheV->addLayout(coucheH);
    setLayout(coucheV);

    QObject::connect(ajouter, SIGNAL(clicked()), this, SLOT(ajout()));
    QObject::connect(sup, SIGNAL(clicked()), this, SLOT(suppression()));
    QObject::connect(modifier, SIGNAL(clicked()), this, SLOT(modif()));
    QObject::connect(terminer, SIGNAL(clicked()), this, SLOT(fin()));

    qDebug()<<"coucou";

}

void Debut::suppression() { //lancement de la fenetre de suppression pour rentrer le code

    UVManager& m=UVManager::getInstance();
    try {
        m.load();
    }
    catch (UTProfilerException e) {qDebug()<<e.getInfo();}

    UVSuppression * fenetre = new UVSuppression(m);
    fenetre->show();
}
void Debut::fin() {
    this->close();
}

void Debut::modif() {

    UVManager& m=UVManager::getInstance();
    try {
        m.load();
    }
    catch (UTProfilerException e) {qDebug()<<e.getInfo();}

    UVModif * fenetre = new UVModif(m);
    fenetre->show();

}

UVModif::UVModif(UVManager& uvm) : M(uvm) {

    codeLabel=new QLabel("code", this);
    code= new QLineEdit("", this);
    submit=new QPushButton("Modifier cette UV", this);

    coucheH=new QHBoxLayout;
    coucheH->addWidget(codeLabel);
    coucheH->addWidget(code);
    coucheH->addWidget(submit);

    coucheV=new QVBoxLayout;
    coucheV->addLayout(coucheH);
    setLayout(coucheV);

    QObject::connect(submit, SIGNAL(clicked()), this, SLOT(modifUV()));
}


void UVModif::modifUV()
{
    bool found=false;
    UVManager& m=UVManager::getInstance();
    cursusManager& cman=cursusManager::getInstance();

    for(QMap<QString,formation*>::iterator it=cman.getQmapIteratorFormbegin();it!=cman.getQmapIteratorFormend();it++)
    {
        if(it.value()->trouverUV(code->text())!=0)
        {
            QMessageBox::warning(this,"Erreur","L'UV que vous souhaitez modifier est inscrite dans la formation "+it.value()->getNom()+".\nRetirez la avant de la modifier.");
            found=true;
        }
        if(found) break;
    }
    if(!found)
    {
        for(QMap<QString,filiere*>::iterator it2=cman.getQmapIteratorFilBegin();it2!=cman.getQmapIteratorFilEnd();it2++)
        {
            if(it2.value()->trouverUV(code->text())!=0)
            {
                QMessageBox::warning(this,"Erreur","L'UV que vous souhaitez modifier est inscrite dans la filiere "+it2.value()->getNom()+".\nRetirez la avant de la modifier.");
                found=true;
            }
            if(found) break;
        }
    }
    if(!found)
    {
        UVEditeur * fenetre= new UVEditeur(m.getUV(code->text()), m);
        fenetre->show();
    }
}


void Debut::ajout() {

    UVManager& m=UVManager::getInstance();
    try {
        m.load();
    }
    catch (UTProfilerException e) {qDebug()<<e.getInfo();}

    UVAjout * fenetre= new UVAjout(m);
    fenetre->show();
}


UVEditeur::UVEditeur(UV& uvToEdit, UVManager& uvm, QWidget* parent) : QWidget(parent), uv(uvToEdit), M(uvm) {

    this->setWindowTitle(QString("Edition de l'UV")+uv.getCode());
    codeLabel=new QLabel("code", this);
    titreLabel=new QLabel("titre", this);
    creditsLabel=new QLabel("credits", this);
    categorieLabel=new QLabel("categorie", this);
    ouvertureLabel=new QLabel("ouverture", this);

    code= new QLineEdit(uv.getCode(), this);
    titre=new QTextEdit(uv.getTitre(), this);
    credits=new QSpinBox(this);
    credits->setRange(1,8);
    credits->setValue(uv.getNbCredits());

    categorie=new QComboBox(this);
    categorie->addItem("CS");
    categorie->addItem("TM");
    categorie->addItem("SP");
    categorie->addItem("TSH");
    categorie->setCurrentIndex(int(uv.getCategorie()));

    automne=new QCheckBox("automne", this);
    automne->setChecked(uv.ouvertureAutomne());

    printemps=new QCheckBox("printemps", this);
    printemps->setChecked(uv.ouvertureAutomne());

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

   QObject::connect(sauver, SIGNAL(clicked()), this, SLOT(sauverUV()));
   QObject::connect(annuler,SIGNAL(clicked()),this,SLOT(close()));
}


void UVEditeur::sauverUV()
{
    uv.setCode(code->text());  //modification du texte avec ce qu'à rentré l'utilisateur dans la QlineEdit
    uv.setTitre(titre->toPlainText());
    uv.setNbCredits(credits->value());//on utilise des methodes accesseurs des classes QXXXX pour mettre les bonnes valeurs dans uv via les methodes set de uv
    uv.setCategorie(Categorie(categorie->currentIndex()));
    uv.setOuverturePrintemps(printemps->isChecked());
    uv.setOuvertureAutomne(automne->isChecked());
    QMessageBox::information(this, "sauvegarde", "UV sauvegardee");
}


/*void UVEditeur::activerSauver(QString s){
    sauver->setEnabled(true); //une modification entraine une activation du bouton sauver
}*/

UVSuppression::UVSuppression(UVManager& uvm) : M(uvm) {

    codeLabel=new QLabel("code", this);
    code2= new QLineEdit("", this);
    submit=new QPushButton("Supprimer cette UV", this);

    coucheH=new QHBoxLayout;
    coucheH->addWidget(codeLabel);
    coucheH->addWidget(code2);
    coucheH->addWidget(submit);

    coucheV=new QVBoxLayout;
    coucheV->addLayout(coucheH);
    setLayout(coucheV);

    QObject::connect(submit, SIGNAL(clicked()), this, SLOT(supprUV()));

}

void UVSuppression::supprUV() {

    QMessageBox::information(this, "sauvegarde", "exec de suppression");

    try {

    M.supprimerUV(code2->text()); } //il faut indiquer de quel UVManager il s'agit

    catch (UTProfilerException e) {qDebug()<<code2->text()<<e.getInfo();}

    QMessageBox::information(this, "sauvegarde", "UV supprimee");
}



UVAjout::UVAjout(UVManager& uvm) : M(uvm) {

    this->setWindowTitle(QString("Ajout d'une UV"));

    codeLabel=new QLabel("code", this);
    titreLabel=new QLabel("titre", this);
    creditsLabel=new QLabel("credits", this);
    categorieLabel=new QLabel("categorie", this);
    ouvertureLabel=new QLabel("ouverture", this);

    code= new QLineEdit("", this);
    titre=new QTextEdit("", this);
    credits=new QSpinBox(this);
    credits->setRange(1,8);
    credits->setValue(1);

    categorie=new QComboBox(this);
    categorie->addItem("CS");
    categorie->addItem("TM");
    categorie->addItem("SP");
    categorie->addItem("TSH");
    categorie->setCurrentIndex(0);

    automne=new QCheckBox("automne", this);
    //automne->setChecked(true);

    printemps=new QCheckBox("printemps", this);
    //printemps->setChecked(uv.ouvertureAutomne());

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

   QObject::connect(sauver, SIGNAL(clicked()), this, SLOT(slot_ajoutUV()));

   //pour que ça sactive que si modif :
   //QObject::connect(code, SIGNAL(textEdited(QString)), this, SLOT(activerSauverUV(QString)));
}

void UVAjout::slot_ajoutUV() {

    M.ajouterUV(code->text(), titre->toPlainText(), credits->value(), Categorie(categorie->currentIndex()), automne->isChecked(), printemps->isChecked());
    //void ajouterUV(const QString& c, const QString& t, unsigned int nbc, Categorie cat, bool a, bool p);
    QMessageBox::information(this, "sauvegarde", "UV sauvegardee");
}


