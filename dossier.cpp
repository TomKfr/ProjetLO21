#include "UTProfiler.h"
#include "dossier.h"
#include "visiteur2.h"
#include <sstream>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>
#include <QFileDialog>

/*!
 * \brief Crée un nouveau dossier
 * \param n numero du dossier
 * \param name nom de l'étudiant
 * \param firstname prénom de l'étudiant
 * \param form formation
 * \param nb numéro du semestre
 */
void DossierManager::ajouterDossier(unsigned int n, const QString& name, const QString& firstname, const QString& form, unsigned int nb){
    try{
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

    catch(UTProfilerException& e){QMessageBox::warning(0,"Erreur",e.getInfo());}

}

/*!
 * \brief suppime un dossier
 * \param dsup pointeur vers le dossier à supprimer
 */
void DossierManager::removeDossier(Dossier* dsup){
    qDebug()<<"remove dossier";

    unsigned int i=0;
    while (tabDossiers[i]!=dsup) i++;
    Dossier* tmp ;
    for (unsigned int j=i; j<nbDos-2; j++) {tmp=tabDossiers[j]; tabDossiers[j]=tabDossiers[j+1]; tabDossiers[j+1]=tmp;}
    delete tabDossiers[nbDos-1];
    nbDos--;

    //il faut aussi supprimer les choix correspondant

    ChoixManager& cm=ChoixManager::getInstance();
    cm.removeChoix(dsup);
    cm.save_completion();
  }

/*!
 * \brief Ajoute une UV réalisée au dossier
 * \param code code de l'uv
 * \param n résultat obtenu
 */
void Dossier::ajouterUV(const QString& code, Note n) {
    listeUV.insert(code,n);
}
/*!
 * \brief retire une uv réalisée du dossier
 * \param uv pointeur vers l'uv à retirer
 */
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
/*!
 * \brief Vérifie si l'UV passée en paramètre est validée
 * \param code code de l'uv
 * \return true si l'uv est validée, false sinon.
 */
bool Dossier::estValidee(const QString &code)
{
    if(listeUV.contains(code))
    {
        QMap<QString,Note>::const_iterator it=listeUV.constFind(code);
        if(it.value()>String2Note("F") && it.value()!=String2Note("ABS")) return true;
        //on part du principe que les uvs en cours seront validees
    }
    else return false;
}
/*!
 * \brief recherche une uv dans le dossier
 * \param code code de l'uv à rechercher
 * \return un const_iterateur sur l'uv recherchée.
 */
const QMap<QString,Note>::const_iterator Dossier::trouverUV(const QString &code)
{
    return listeUV.find(code);
}
/*!
 * \brief rehcerche un dossier dans ceux connus du DossierManager
 * \param n numéro du dossier recherché
 * \return  un pointeur sur le dossier recherché s'il existe, 0 sinon.
 */
Dossier* DossierManager::trouverDossier(unsigned int n)const{
    qDebug()<<nbDos;
    for(unsigned int i=0; i<nbDos; i++)
        if (n==tabDossiers[i]->getNumero()) return tabDossiers[i];
    return 0;
}

/*!
 * \brief Destructeur du DossierManager
 */
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
/*!
 * \brief Exécute la méthode visit du visiteur
 * \param v pointeur vers le visiteur
 */
void DossierManager::accept(visiteur2* v) {
    v->visitDossierManager(this);
}

/*!
 * \brief Exécute la méthode visit du visiteur
 * \param v pointeur vers le visiteur
 */
void Dossier::acceptCompletion(visiteurCompletion* v) {
    v->visitDossierManager(this);
}
/*!
 * \brief Renvoie un itérateur permettant de parcourir les dossiers
 * \return un iterateur
 */
iterateur<Dossier>& DossierManager::getIterateurDos()
{
    iterateur<Dossier>* it=new iterateur<Dossier>(tabDossiers,nbDos);
    return *it;
}
/*!
 * \brief Modifie le résultat enregistré pour une UV
 * \param code code de l'uv
 * \param n résultat à enregistrer
 */
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






