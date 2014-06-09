#include "completion.h"
#include "cursus.h"
#include "dossier.h"

#include <QXmlStreamWriter>
#include <QFile>
#include <QDir>

void souhaits::Ajt_exigence(const QString& code)
{
    exigences.insert(code);
}
void souhaits::Ajt_preference(const QString& code)
{
    preferences.insert(code);
}
void souhaits::Ajt_rejet(const QString& code)
{
    rejets.insert(code);
}
void souhaits::Suppr_exigence(const QString& code)
{
    exigences.remove(code);
}
void souhaits::Suppr_prefernce(const QString& code)
{
    preferences.remove(code);
}
void souhaits::Suppr_rejet(const QString& code)
{
    rejets.remove(code);
}


void ChoixAppliSemestre::ajoutUV(UV* uv) {propositionUV.insert(uv->getCode(),uv);}
void ChoixAppliSemestre::supprimerUV(UV* uv) {propositionUV.erase(propositionUV.find(uv->getCode()));}
void ChoixAppli::ajouter_proposition(ChoixAppliSemestre* prop) {

if (nbSemestre==nbMaxSemestre) {
    nbMaxSemestre+=5;
    ChoixAppliSemestre** tab=new ChoixAppliSemestre*[nbMaxSemestre];
    for (unsigned int i=0; i<nbSemestre; i++) tab[i]=listePropositions[i];
    ChoixAppliSemestre** old = listePropositions;
    listePropositions=tab;
    delete[] old;
}

listePropositions[nbSemestre++]=prop;

}

ChoixAppliSemestre* ChoixAppli::trouverChoix(Semestre S) {


    for (unsigned int i=0; i<nbSemestre; i++) {
        qDebug()<<"recherche";
        qDebug()<<listePropositions[i]->getSemestre().getAnnee();
        qDebug()<<S.getAnnee();
        qDebug()<<listePropositions[i]->getSemestre().getSaison();
        qDebug()<<S.getSaison();
        if ( ( listePropositions[i]->getSemestre() ) ==S)
        { qDebug()<<"trouve";
          return listePropositions[i]; }
    }

    return 0;
}

ChoixAppli * ChoixManager::trouverProposition(unsigned int id) {

    for (unsigned int i=0; i<nbPropositions; i++) {if (ensemblePropositions[i]->getIdentifiant()==id) return ensemblePropositions[i];}
    return 0;

}



ChoixManager::Handler ChoixManager::handler=Handler();

ChoixManager& ChoixManager::getInstance() {
    StrategieConcrete * s1=new StrategieConcrete;
    StrategieConcrete& s=*s1;

    if (!handler.instance) handler.instance = new ChoixManager(s); /* instance cr��e une seule fois lors de la premi�re utilisation*/
    return *handler.instance;
}

void ChoixManager::libererInstance() {
    if (handler.instance) { delete handler.instance; handler.instance=0; }
}

void ChoixManager::ajouterProposition(ChoixAppli* c) {
    try{
        if (trouverProposition(c->getIdentifiant())) {
            throw UTProfilerException(QString("erreur, ChoixManager, Proposition ")+c->getIdentifiant()+QString("deja existante"));
        }else{

            if (nbPropositions==nbPropositionsMax){
                ChoixAppli** newtab=new ChoixAppli*[nbPropositionsMax+10];
                for(unsigned int i=0; i<nbPropositions; i++) newtab[i]=ensemblePropositions[i];
                nbPropositionsMax+=10;
                ChoixAppli** old=ensemblePropositions;
                ensemblePropositions=newtab;
                delete[] old;
            }

            ensemblePropositions[nbPropositions++]=c;
            qDebug()<<nbPropositions;
        }
    }
    catch(UTProfilerException& e){QMessageBox::warning(0,"Erreur",e.getInfo());}
}

ChoixAppli** ChoixManager::trouverPropositionsDossier(Dossier * d) {

    qDebug()<<"dans la recherche de la proposition";
    qDebug()<<"dossier : "<<d;
    qDebug()<<nbPropositions;

    ChoixAppli ** result=0;
    unsigned int nbResult=0;
    unsigned int nbResultMax=0;

    for (unsigned int i=0; i<nbPropositions; i++) {
        qDebug()<<ensemblePropositions[i]->getDossier();
        if (ensemblePropositions[i]->getDossier()==d)
        {
            //alors on complete le resultat
            qDebug()<<"jen ai trouve un";
            if (nbResult==nbResultMax){
                ChoixAppli** newtab=new ChoixAppli*[nbResultMax+5];
                for(unsigned int i=0; i<nbResult; i++) newtab[i]=result[i];
                nbResultMax+=5;
                ChoixAppli** old=result;
                result=newtab;
                delete[] old;
            }

            result[nbResult++]=ensemblePropositions[i];
        }
    }

   return result;

}

unsigned int ChoixManager::trouverNbPropositionsDossier(Dossier *d) {
    qDebug()<<"dans le calcul du nb de propositions";

    unsigned int nbResult=0;

    for (unsigned int i=0; i<nbPropositions; i++) {
        if (ensemblePropositions[i]->getDossier()==d) nbResult++;
    }

   return nbResult;
}


void ChoixManager::removeChoix(Dossier * d) {
    qDebug()<<"dans la suppression des choix";

    ChoixAppli** aSupprimer = trouverPropositionsDossier(d);
    unsigned int nb=trouverNbPropositionsDossier(d);

    for (unsigned int i=0; i<nb; i++) { //pour chaque choix appli à supprimer

        unsigned int j=0;
        while (ensemblePropositions[j]!=aSupprimer[i]) j++; //j represente alors l'indice du choix appli à supprimer
        ChoixAppli* tmp ;

        for (unsigned int k=j; k<nbPropositions-2; k++) {tmp=ensemblePropositions[k]; ensemblePropositions[k]=ensemblePropositions[k+1]; ensemblePropositions[k+1]=tmp;}
        delete ensemblePropositions[nbPropositions-1];
        nbPropositions--;

    }
}

