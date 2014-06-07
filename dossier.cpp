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


void Dossier::ajouterUV(const QString& code, Note n) {
    listeUV.insert(code,n);
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

bool Dossier::estValidee(const QString &code)
{
    if(listeUV.contains(code))
    {
        QMap<QString,Note>::const_iterator it=listeUV.constFind(code);
        if(it.value()>String2Note("F") && it.value()!=String2Note("ABS") && it.value()!=String2Note("EC")) return true;
    }
    else return false;
}

const QMap<QString,Note>::const_iterator Dossier::trouverUV(const QString &code)
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

void Dossier::setResultat(const QString &code, Note n)
{
    QMap<QString,Note>::iterator it=listeUV.find(code);
    it.value()=n;
}

/*void Dossier::ajouterResultat(const QString & res){ PLUS NECESSAIRE

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
            delete[] old;
            qDebug()<<"6";
        }

         qDebug()<<"ici";
        listeResultats[nbResultats++]=res;

}*/

/*void Dossier::ajt_prevision(const QString &d, unsigned int scs, unsigned int ics, unsigned int stm, unsigned int itm, unsigned int stsh, unsigned int itsh)
{
    previsions.insert(d,new prevision(d,scs,ics,stm,itm,stsh,itsh));
}
void Dossier::sup_prevision(const QString &d)
{
    previsions.remove(d);
}*/

ChoixAppli* Dossier::calculCompletion() {

unsigned int nbTotalCreditsCS;
unsigned int nbTotalTM;
unsigned int nbTotalTSH;

/*calculer ces chiffres : si le total est obtenu, ne pas générer de completion


Sinon : on ne peut qu'améliorer le dossier

la 1ere fois : on créé un choix appli et une entrée correspondante dans le total des choix appli du choix manager
unsigned int nbRestantsCreditsCS;
unsigned int nbRestantsCreditsTM;
unsigned int nbRestantsCreditsTSH; les 3 à calculer

faire une copie des map pour les souhaits pour les modifier ensuite : as tu dailleurs verifie que les uvs des souhaits
ne devaient pas etre les uvs deja faites ? je ne crois pas et il faudrait le faire du coup.

NB : pour les UVs du dossier qui sont en cours, on part du principe qu'elles seront validees à la fin
du semestre en cours.

créer 3 listes d'uvs obligatoires pas encore faites par l'étudiants
puis :

si nbRestantsCreditsCS !=0 et nbCS <= 3 pécho la 1ere CS dans les UVs obligatoires non faites ; s'il les a toutes déjà faites, on parcourt la map des souhaitsCS favoris si elle est pas vide;
si elle est vide, souhaits du dessous
decrementer nbRestantsCreditsCS ; recommencer.
virer l'uv de la map des souhaits associee

pareil pour TM
pareil pour les tsh (on tient pas compte des colonne/lignes fuck fuck)
avec les contraintes sur le nb de tm, tsh, le nb total d'uv, le nb total de credits.


augmenter le total dans chaque categorie
generer un ChoixAppliSemestre, lui meme ajouté dans le choix appli du semestre correspondant

*/


}

