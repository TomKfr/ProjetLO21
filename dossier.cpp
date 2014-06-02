#include "UTProfiler.h"
#include "dossier.h"
#include "visiteur2.h"
#include <sstream>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>
#include <QFileDialog>


void DossierManager::ajouterDossier(unsigned int n, const QString& name, const QString& firstname, const QString& form, unsigned int nb){
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

        tabDossiers[nbDos]=new Dossier(n, name, firstname, form ,nb);
        nbDos++;
    }

}



void DossierManager::removeDossier(Dossier* dsup){

    unsigned int i=0;
    while (tabDossiers[i]!=dsup) i++;
    Dossier* tmp ;
    for (unsigned int j=i; j<nbDos-2; j++) {tmp=tabDossiers[j]; tabDossiers[j]=tabDossiers[j+1]; tabDossiers[j+1]=tmp;}
    delete tabDossiers[nbDos-1];
    nbDos--;
    }


void Dossier::ajouterUV(UV* uv) {
   /* if (nbUV==nbMaxUV){
        UV** newtab=new UV*[nbMaxUV+5];
        for(unsigned int i=0; i<nbUV; i++) newtab[i]=listeUV[i];
        nbMaxUV+=5;
        UV** old=listeUV;
        listeUV=newtab;
        delete[] old;
    }
    listeUV[nbUV++]=uv;*/
    listeUV.insert(uv->getCode(),uv);
}

void Dossier::supprimerUV(UV* uv) {
/*unsigned int i=0;
while (listeUV[i]!=uv) i++;
int limit=nbUV;

limit-=2;

UV* tmp ;
QString tmp2;

for (int j=i; j<limit; j++) {tmp=listeUV[j]; listeUV[j]=listeUV[j+1]; listeUV[j+1]=tmp;}
for (int j=i; j<limit; j++) {tmp2=listeResultats[j]; listeResultats[j]=listeResultats[j+1]; listeResultats[j+1]=tmp2;}

listeUV[nbUV-1]=0;//pour pas effacer l'uv si on fait un delete
nbUV--;
nbResultats--;*/


    if(QMessageBox::information(0,"Retrait d'une UV","Voulez vous retirer l'UV du dossier ?",QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Ok)
    {
        listeUV.erase(listeUV.find(uv->getCode()));
    }

}

const QMap<QString,UV*>::const_iterator Dossier::trouverUV(const QString &code)
{
    return listeUV.find(code);
}

Dossier* DossierManager::trouverDossier(unsigned int n)const{
    qDebug()<<nbDos;
    for(unsigned int i=0; i<nbDos; i++)
        if (n==tabDossiers[i]->getNumero()) return tabDossiers[i];
    return 0;
}


DossierManager::~DossierManager(){
    qDebug() << "Destructeur DossiersManager";
    for(unsigned int i=0; i<nbDos; i++) delete tabDossiers[i];
    delete[] tabDossiers;
}

DossierManager::Handler DossierManager::handler=Handler();

DossierManager& DossierManager::getInstance() {
    if (!handler.instance) handler.instance = new DossierManager; /* instance cr��e une seule fois lors de la premi�re utilisation*/
    return *handler.instance;
}

void DossierManager::libererInstance() {
    if (handler.instance) { delete handler.instance; handler.instance=0; }
}

/*
iterateur<UV>& Dossier::getIterateurUV()
{
    iterateur<UV>* it=new iterateur<UV>(listeUV,nbUV);
    return *it;
}*/

void DossierManager::accept(visiteur2* v) {
    v->visitDossierManager(this);
}


void Dossier::acceptCompletion(visiteurCompletion* v) {
    v->visitDossierManager(this);
}
iterateur<Dossier>& DossierManager::getIterateurDos()
{
    iterateur<Dossier>* it=new iterateur<Dossier>(tabDossiers,nbDos);
    return *it;
}

void Dossier::ajouterResultat(const QString & res){

     qDebug()<<"ajouter resultat";

     qDebug()<<nbResultats;
     qDebug()<<nbMaxResultats;

     //inversion quelque part


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

         qDebug()<<"ici";
        listeResultats[nbResultats++]=res;

}


