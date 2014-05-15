#include "UTProfiler.h"
#include"dossier.h"
#include"visiteur2.h"
#include <sstream>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>
#include <QFileDialog>


void DossierManager::ajouterDossier(unsigned int n, const QString& name, const QString& firstname, const QString& form){
    if (trouverDossier(n)) {
        throw UTProfilerException(QString("erreur, DossierManager, Dossier ")+n+QString("d�ja existant"));
    }else{

        if (nbDos==nbMaxDos){
            Dossier** newtab=new Dossier*[nbMaxDos+10];
            for(unsigned int i=0; i<nbDos; i++) newtab[i]=tabDossiers[i];
            nbMaxDos+=10;
            Dossier** old=tabDossiers;
            tabDossiers=newtab;
            delete[] old;
        }

        tabDossiers[nbDos]=new Dossier(n, name, firstname, form);
        nbDos++;
       //DOSSIER BIEN AJOUTE


    }

}

void DossierManager::removeDossier(Dossier* dsup){

    unsigned int i=0;
    while (tabDossiers[i]!=dsup) i++;
    qDebug()<<"remove dossier";
    qDebug()<<"numero de dossier a supprimer : "<<i;
    Dossier* tmp ;
    for (unsigned int j=i; j<nbDos-2; j++) {tmp=tabDossiers[j]; tabDossiers[j]=tabDossiers[j+1]; tabDossiers[j+1]=tmp;}
    delete tabDossiers[nbDos-1];
    nbDos--;

    }


void Dossier::ajouterUV(UV* uv) {
qDebug()<<"ajouterUV";
    if (nbUV==nbMaxUV){
        UV** newtab=new UV*[nbMaxUV+5];
        for(unsigned int i=0; i<nbUV; i++) newtab[i]=listeUV[i];
        nbMaxUV+=5;
        UV** old=listeUV;
        listeUV=newtab;
        delete[] old;
    }
    listeUV[nbUV++]=uv;

}



Dossier* DossierManager::trouverDossier(unsigned int n)const{
    for(unsigned int i=0; i<nbDos; i++)
        if (n==tabDossiers[i]->getNumero()) return tabDossiers[i];
    return 0;
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
                QStringList listUV;
                QStringList listResult;


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
                        if(xml.name() == "uvs")
                        {
                            unsigned int nbUVs=0;
                            xml.readNext();
                            while(!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="uvs"))
                            {
                                if(xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="uv")
                                {
                                    nbUVs++;
                                    xml.readNext();
                                    listUV<<xml.text().toString();
                                }

                                if(xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="result")
                                {
                                    xml.readNext();
                                    listResult<<xml.text().toString();
                                }

                                xml.readNext();
                            }
                        }
                    }
                    xml.readNext();
                }
                ajouterDossier(numero,nom, prenom, formation);//ON FAIT LES TYPES SIMPLES A CE NIVEAU
                //PUIS ON GERE LES LISTES
                if(!listUV.empty())
                {
                    visiteur2* v=new visiteur2(numero,listUV, listResult);
                    v->visitUVmanager();
                    this->accept(v);
                }
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
         qDebug()<<"dans le save avant la liste";

         //ecriture des UV

         QString * listeRes=tabDossiers[i]->getlisteResultats();
         unsigned int j=0;
         qDebug()<<listeRes[0];

         stream.writeStartElement("uvs");
         for(iterateur<UV>& it=tabDossiers[i]->getIterateurUV(); !it.isDone(); it.next())
         {
             qDebug()<<"ecriture de l'uv: "<<it.courant()->getCode(); //CHAINE VIDE
             stream.writeTextElement("uv",it.courant()->getCode());
             //ecriture du resultat correspondant
             stream.writeTextElement("result",listeRes[j]);
             j++;

         }
         stream.writeEndElement();
         stream.writeEndElement();
     }
     stream.writeEndElement();
     stream.writeEndDocument();

     newfile.close();
}

DossierManager::~DossierManager(){
    qDebug() << "Destructeur DossiersManager";
    //if (file!="") save(file);
    for(unsigned int i=0; i<nbDos; i++) delete tabDossiers[i];
    delete[] tabDossiers;
}

DossierManager::Handler DossierManager::handler=Handler();

DossierManager& DossierManager::getInstance() {
    if (!handler.instance) handler.instance = new DossierManager; /* instance cr��e une seule fois lors de la premi�re utilisation*/
    return *handler.instance;
} //FAIRE UN TEMPLATE POUR CES FONCTIONS

void DossierManager::libererInstance() {
    if (handler.instance) { delete handler.instance; handler.instance=0; }
}


iterateur<UV>& Dossier::getIterateurUV()
{
    qDebug()<<"creation de literateur";
    qDebug()<<"nbuv : "<<nbUV;
    iterateur<UV>* it=new iterateur<UV>(listeUV,nbUV);
    return *it;
}

void DossierManager::accept(visiteur2* v) {
    v->visitDossierManager(this);
}

iterateur<Dossier>& DossierManager::getIterateurDos()
{
    iterateur<Dossier>* it=new iterateur<Dossier>(tabDossiers,nbDos);
    return *it;
}
//coucou
void Dossier::ajouterResultat(const QString & res){

    qDebug()<<"ajouterResultat";
        if (nbResultats==nbMaxResultats){
            qDebug()<<"1";
            QString * newtab=new QString[nbMaxResultats+5];
            qDebug()<<"2";
            for(unsigned int i=0; i<nbResultats; i++) newtab[i]=listeResultats[i];
            nbMaxResultats+=5;
            qDebug()<<"3";
            QString* old=listeResultats;
            qDebug()<<"4";
            listeResultats=newtab;
            qDebug()<<"5";
            //delete[] old;
             qDebug()<<"6";
        }
         qDebug()<<"avant ecriture res";
        listeResultats[nbResultats++]=res;

        qDebug()<<"fin de ajouter resultat";

}
