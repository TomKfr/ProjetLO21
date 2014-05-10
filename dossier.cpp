#include "UTProfiler.h"
#include"dossier.h"
#include <sstream>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>
#include <QFileDialog>

DossierManager::Handler DossierManager::handler=Handler();

void supprimerDossier(unsigned int n) {
/*à faire*/

}

DossierManager& DossierManager::getInstance() {
    if (!handler.instance) handler.instance = new DossierManager; /* instance cr��e une seule fois lors de la premi�re utilisation*/
    return *handler.instance;
} //FAIRE UN TEMPLATE POUR CES FONCTIONS

void DossierManager::libererInstance() {
    if (handler.instance) { delete handler.instance; handler.instance=0; }
}

void DossierManager::addItem(Dossier* dos){
    if (nbDos==nbMaxDos){
        Dossier** newtab=new Dossier*[nbMaxDos+10];
        for(unsigned int i=0; i<nbDos; i++) newtab[i]=tabDossiers[i];
        nbMaxDos+=10;
        Dossier** old=tabDossiers;
        tabDossiers=newtab;
        delete[] old;
    }
    tabDossiers[nbDos++]=dos;
}

void DossierManager::ajouterDossier(unsigned int n, const QString& name, const QString& firstname, const QString& form, UV** tablo){
    if (trouverDossier(n)) {
        throw UTProfilerException(QString("erreur, DossierManager, Dossier ")+n+QString("d�ja existant"));
    }else{
        Dossier* newDossier=new Dossier(n, name, firstname, form, tablo);
        addItem(newDossier);

    }
}

Dossier* DossierManager::trouverDossier(unsigned int n)const{
    for(unsigned int i=0; i<nbDos; i++)
        if (n==tabDossiers[i]->getNumero()) return tabDossiers[i];
    return 0;
}

Dossier::Dossier(unsigned int num, const QString& n, const QString& p, const QString& f, UV** liste) {

    DossierManager& D=DossierManager::getInstance();

    if (D.trouverDossier(num)!=0) throw UTProfilerException("Numero de dossier deja existant\n Ressayer \n");
    else {
        this->numero=num;
        this->nom=n;
        this->prenom=p;
        this->F=f;
        this->listeUV=liste;
    }
}



void DossierManager::load(const QString& fichier)
{
        file=fichier;
    qDebug()<<"Chargement Dossiers!";
    QFile f(fichier);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {throw UTProfilerException("Erreur ouverture fichier cursus");}
    QXmlStreamReader xml(&f);
    while(!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartDocument) continue;
        if(token == QXmlStreamReader::StartElement) {
            if(xml.name() == "dossiers") continue;
            if(xml.name() == "dossier") {
                unsigned int numero;
                QString nom;
                QString prenom;
                QString formation;


                xml.readNext();
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "dossier")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        if(xml.name() == "numero") {
                            xml.readNext(); numero=xml.text().toString().toUInt();
                        }
                        if(xml.name() == "nom") {
                            xml.readNext(); nom=xml.text().toString();
                        }
                        if(xml.name() == "prenom") {
                            xml.readNext(); prenom=xml.text().toString();
                        }
                        if(xml.name() == "formation") {
                            xml.readNext(); formation=xml.text().toString();
                        }
                    }
                    xml.readNext();
                }
                ajouterDossier(numero,nom, prenom, formation, 0);
            }
        }
    }
    if(xml.hasError()) {
        throw UTProfilerException("Erreur lecteur fichier dossier, parser xml");
    }
    xml.clear();
    qDebug()<<"Chargement Dossiers termine!";
}

void DossierManager::save(const QString& f){
    qDebug() << "Save Dossier";
    file=f;
    QFile newfile( file);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text)) throw UTProfilerException(QString("erreur ouverture fichier xml"));
     QXmlStreamWriter stream(&newfile);
     stream.setAutoFormatting(true);
     stream.writeStartDocument();
     stream.writeStartElement("dossiers");
     for(unsigned int i=0; i<nbDos; i++){
         stream.writeStartElement("dossier");
         /*stream.writeAttribute("automne", (uvs[i]->ouvertureAutomne())?"true":"false");
         stream.writeAttribute("printemps", (uvs[i]->ouverturePrintemps())?"true":"false");*/
         QString n; n.setNum(tabDossiers[i]->getNumero());
         stream.writeTextElement("numero",n);
         stream.writeTextElement("nom",tabDossiers[i]->getNom());
         stream.writeTextElement("prenom",tabDossiers[i]->getPrenom());
         stream.writeTextElement("formation",tabDossiers[i]->getFormation());
         //stream.writeTextElement("liste",tabDossiers[i]->getlisteUV());
         //QString cr; cr.setNum(uvs[i]->getNbCredits());

         stream.writeEndElement();
     }
     stream.writeEndElement();
     stream.writeEndDocument();

     newfile.close();

}

DossierManager::~DossierManager(){
    qDebug() << "Destructeur DossiersManager";
    if (file!="") save(file);
    for(unsigned int i=0; i<nbDos; i++) delete tabDossiers[i];
    delete[] tabDossiers;
}

