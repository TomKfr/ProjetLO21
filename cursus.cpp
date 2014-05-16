#include"cursus.h"
#include"UTProfiler.h"
#include<QDebug>
#include <QMessageBox>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFileDialog>
#include <QDir>
#include <QStringList>
#include<QMap>

cursusManager::Handler cursusManager::handler=Handler();

class visiteur;

// ///////////////////////////////////////////////////////////////////
void abstract_cursus_item::ajouter_UV(UV *newuv) {uvs.insert(newuv->getCode(),newuv);}
void abstract_cursus_item::supprimer_UV(const QString &code)
{
    if(QMessageBox::information(0,"Retrait d'une UV","Voulez vous retirer l'UV "+code+" ?",QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Ok)
    {
        uvs.erase(uvs.find(code));
    }
}

// ///////////////////////////////////////////////////////////////////


void formation::ajouter_UV(UV* uv)
{
    uvs.insert(uv->getCode(),uv);
}

void formation::supprimer_UV(const QString& code)
{
    if(QMessageBox::information(0,"Retrait d'une UV","Voulez vous retirer l'UV "+code+" de la formation "+nom+" ?",QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Ok)
    {
        uvs.erase(uvs.find(code));
    }
}

const QMap<QString,UV*>::const_iterator formation::trouverUV(const QString &code)
{
    return uvs.find(code);
}

/*iterateur<UV>& formation::getIterateurUV()
{
    iterateur<UV>* it=new iterateur<UV>(uvs,nbUV);
    return *it;
}*/

cursusManager& cursusManager::getInstance() {
    if (!handler.instance) handler.instance = new cursusManager; /* instance cr��e une seule fois lors de la premi�re utilisation*/
    return *handler.instance;
}

void cursusManager::libererInstance() {
    if (handler.instance) { delete handler.instance; handler.instance=0; }
}

formation* cursusManager::trouverForm(const QString& n)
{
    return formations.find(n).value();
}

void cursusManager::ajouterFormation(const QString& nom, unsigned int c, unsigned int s)
{
    if (formations.find(nom)!=formations.end())
    {
        throw UTProfilerException(QString("erreur, cursusManager, formation ")+nom+QString(" déja existante"));
    }
    else
    {
        formations.insert(nom,new formation(nom,c,s));
    }
}

void cursusManager::supprimerFormation(const QString &nom)
{
    formations.erase(formations.find(nom));
}

void cursusManager::sauverCursus(QWidget *parent)
{
    QString fileOut = QDir::currentPath()+ "/formations.xml";
    qDebug()<<"Sauvegarde dans le fichier "<<fileOut;

    if(!fileOut.isEmpty())
    {
        QFile f(fileOut);
        if(!f.open(QIODevice::WriteOnly | QIODevice::Text)) throw UTProfilerException("Erreur ouverture fichier xml!");
        QXmlStreamWriter stream(&f);
        stream.setAutoFormatting(true);
        stream.writeStartDocument();
        stream.writeStartElement("formations");
        for(QMap<QString,formation*>::iterator form=formations.begin();form!=formations.end();form++)
        {
            stream.writeStartElement("formation");
            stream.writeTextElement("nom",form.key());
            QString cr; cr.setNum(form.value()->getNbCred());
            stream.writeTextElement("nbcred",cr);
            cr.setNum(form.value()->getNbSem());
            stream.writeTextElement("nbsem", cr);
            stream.writeStartElement("uvs");
            for(QMap<QString,UV*>::iterator it=form.value()->getQmapIteratorUVbegin();it!=form.value()->getQmapIteratorUVend(); it++)
            {
                stream.writeTextElement("uv",it.key());
            }
            stream.writeEndElement();
            stream.writeEndElement();
        }
        stream.writeEndElement();
        stream.writeEndDocument();

        f.close();
        QMessageBox::information(parent,"Sauvegarde","Formations sauvegardées", QMessageBox::Ok);
    }
}

void cursusManager::chargerCursus()
{
    QString fileOut = QDir::currentPath()+ "/formations.xml";
    qDebug()<<"Ouverture du fichier "<<fileOut;
    QFile f(fileOut);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {throw UTProfilerException("Erreur ouverture fichier cursus");}
    QXmlStreamReader xml(&f);
    while(!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartDocument) continue;
        if(token == QXmlStreamReader::StartElement) {
            if(xml.name() == "formations") continue;
            if(xml.name() == "formation") {
                QString nom;
                unsigned int nbCredits;
                unsigned int nbSem;
                QStringList list;

                xml.readNext();
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "formation")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        if(xml.name() == "nom") {
                            xml.readNext(); nom=xml.text().toString();
                        }
                        if(xml.name() == "nbcred") {
                            xml.readNext(); nbCredits=xml.text().toUInt();
                        }
                        if(xml.name() == "nbsem") {
                            xml.readNext(); nbSem=xml.text().toUInt();
                        }
                        if(xml.name() == "uvs")
                        {
                            xml.readNext();
                            while(!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="uvs"))
                            {
                                if(xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="uv")
                                {
                                    xml.readNext();
                                    list<<xml.text().toString();
                                }
                                xml.readNext();
                            }
                        }
                    }
                    xml.readNext();
                }
                ajouterFormation(nom,nbCredits,nbSem);
                if(!list.empty())
                {
                    visiteur* v=new visiteur(nom,list);
                    v->visitUVmanager();
                    this->accept(v);
                }
            }
        }
    }
    if(xml.hasError()) {
        throw UTProfilerException("Erreur lecteur fichier formations, parser xml");
    }
    xml.clear();
}

/*iterateur<formation>& cursusManager::getIterateurForm()
{
    iterateur<formation>* it=new iterateur<formation>(formations,nbFor);
    return *it;
}*/

void cursusManager::accept(visiteur *v) {v->visitCursusManager(this);}


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
    //QObject::connect(valider, SIGNAL(clicked()),parent, SLOT(update()));
}

void ajoutFormation::ajout()
{
    man->ajouterFormation(nom->text(),credits->value(), semstr->value());
    QMessageBox::information(this,"Ajout d'une formation", "Formation ajoutée !",QMessageBox::Ok);
    parent->update();
    this->close();
}
modifFormation::modifFormation(cursusManager* m, formation* f)
{
    this->setWindowTitle(QString("Ajout d'une formation"));
    this->setFixedWidth(200);
    man=m;
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

void formation::modif(const QString &n, unsigned int c, unsigned int s)
{
    nom=n;
    nbCredits=c;
    nbSemestres=s;
}

void modifFormation::modif()
{
    form->modif(nom->text(),credits->value(), semstr->value());
    QMessageBox::information(this,"Modification","Modification effectuée",QMessageBox::Ok);
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
