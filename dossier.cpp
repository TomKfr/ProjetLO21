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

void DossierManager::ajouterDossier(unsigned int n, const QString& name, const QString& firstname, formation* form, UV** tablo){
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


void DossierManager::load(){

    QString chemin = QFileDialog::getOpenFileName(0,"Ouvrir un fichier de formations","D:/Qt projects/LO21_Thomas_v1");
    QFile f(chemin);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {throw UTProfilerException("Erreur ouverture fichier dossiers");
     this->~DossierManager();}


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
              formation* F;
              UV** listeUV;

              xml.readNext();
              while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "dossier")) {
                  if(xml.tokenType() == QXmlStreamReader::StartElement) {
                      if(xml.name() == "numero") {
                          xml.readNext(); numero=xml.text().toUInt();
                      }
                      if(xml.name() == "nom") {
                          xml.readNext(); nom=xml.text().toString();
                      }
                      if(xml.name() == "prenom") {
                          xml.readNext(); prenom=xml.text();
                      }
                      if(xml.name() == "formation") {
                          xml.readNext(); nom=xml.text().toString();
                  }
                  xml.readNext();
              }
              ajouterDossier(numero, nom, prenom, formation);
          }
      }
  }
  if(xml.hasError()) {
      throw UTProfilerException("Erreur lecteur fichier formations, parser xml");
  }
  xml.clear();
}
}
