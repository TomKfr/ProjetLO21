#include "completion.h"
#include "cursus.h"
#include "dossier.h"

#include <QXmlStreamWriter>
#include <QFile>
#include <QDir>

/*!
 * \brief Vérifie si le nombre de crédits souhaités et les UVs de la formation sont compatibles.
 * \param dos pointeur vers le dossier concerné
 * \return true si le calcul d'une solution est possible, false sinon.
 */
bool ChoixManager::verifCompletion(Dossier * dos) const { //calcule si le nb de credits souhaites et les uvs de la formation sont compatibles

    cursusManager& cm=cursusManager::getInstance();
    formation * f=cm.trouverForm(dos->getFormation());

    QMap<Categorie,unsigned int> const creditsVoulus=f->getMapCrRequis();
    QMap<QString,UV*> const uvs=f->getUVFormation();
    unsigned int totalCumulableCS=0; unsigned int totalCumulableTM=0; unsigned int totalCumulableTSH=0; unsigned int totalCumulableSP=0;

    for (QMap<QString, UV*>::const_iterator it=uvs.begin(); it!=uvs.end(); ++it) {
        if (it.value()->getCategorie()==CS) totalCumulableCS+=it.value()->getNbCredits();
        else if (it.value()->getCategorie()==TM) totalCumulableTM+=it.value()->getNbCredits();
        else if (it.value()->getCategorie()==TSH) totalCumulableTSH+=it.value()->getNbCredits();
        else if (it.value()->getCategorie()==SP) totalCumulableSP+=it.value()->getNbCredits();
    }

    for (QMap<Categorie,unsigned int>::const_iterator it=creditsVoulus.begin(); it!=creditsVoulus.end(); ++it) {
        //si on demande plus que ce qui est possible avec les uvs de la formation, alors cest impossible

        if (it.key()==CS) {
            if (it.value()>totalCumulableCS) return false; }
        else if (it.key()==TM){
            if (it.value()>totalCumulableTM) return false; }
        else if (it.key()==TSH){
            if (it.value()>totalCumulableTSH) return false; }
        else if (it.key()==SP){
            if (it.value()>totalCumulableSP) return false; }
    }

    return true; //sinon le calcul est possible
}

/*!
 * \brief ajoute une UV à la liste des UVs exigées par l'étudiant
 * \param code code de l'UV à ajouter
 */
void souhaits::Ajt_exigence(const QString& code)
{
    exigences.insert(code);
}
/*!
 * \brief ajoute une UV à la liste des UVs préférées par l'étudiant
 * \param code code de l'UV à ajouter
 */
void souhaits::Ajt_preference(const QString& code)
{
    preferences.insert(code);
}
/*!
 * \brief ajoute une UV à la liste des UVs rejetées par l'étudiant
 * \param code code de l'UV à ajouter
 */
void souhaits::Ajt_rejet(const QString& code)
{
    rejets.insert(code);
}
/*!
 * \brief retire une UV de la liste des UVs exigées par l'étudiant
 * \param code code de l'UV à retirer
 */
void souhaits::Suppr_exigence(const QString& code)
{
    exigences.remove(code);
}
/*!
 * \brief retire une UV de la liste des UVs preférées par l'étudiant
 * \param code code de l'UV à retirer
 */
void souhaits::Suppr_prefernce(const QString& code)
{
    preferences.remove(code);
}
/*!
 * \brief retire une UV de la liste des UVs rejetées par l'étudiant
 * \param code code de l'UV à retirer
 */
void souhaits::Suppr_rejet(const QString& code)
{
    rejets.remove(code);
}

/*!
 * \brief Ajoute une UV à une proposition pour un semestre
 * \param uv pointeur vers l'UV à ajouter
 */
void ChoixAppliSemestre::ajoutUV(UV* uv) {propositionUV.insert(uv->getCode(),uv); nbUV++; }
/*!
 * \brief retire une UV d'une proposition pour un semestre
 * \param uv pointeur vers l'UV à retirer
 */
void ChoixAppliSemestre::supprimerUV(UV* uv) {propositionUV.erase(propositionUV.find(uv->getCode())); nbUV--; }
/*!
 * \brief Ajoute une proposition sur un semestre à une proposition globale
 * \param prop pointeur vers la proposition à ajouter
 */
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

/*!
 * \brief Permet de trouver la/les propositions faites par l'application pour un semestre donné
 * \param S semestre pour lequel on souhaite retrouver la proposition
 * \return Une proposition sur un semestre
 */
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
/*!
 * \brief Retrouve une proposition à partir d'un identifiant donné
 * \param id identifiant de la proposition recherchée.
 * \return une proposition sur un semestre.
 */
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

/*!
 * \brief Ajoute une nouvelle proposition à celles connues par le ChoixManager
 * \param c pointeur vers la proposition à ajouter
 */
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
/*!
 * \brief Retrouve la/les propositions qui ont été faites pour un dossier donné.
 * \param d pointeur vers le dossier concerné
 * \return une proposition globale
 */
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
/*!
 * \brief Calcule le nombre de propositions existantes pour un dossier.
 * \param d pointeur vers le dossier concerné
 * \return nombre de propositions.
 */
unsigned int ChoixManager::trouverNbPropositionsDossier(Dossier *d) {
    qDebug()<<"dans le calcul du nb de propositions";

    unsigned int nbResult=0;

    for (unsigned int i=0; i<nbPropositions; i++) {
        if (ensemblePropositions[i]->getDossier()==d) nbResult++;
    }

   return nbResult;
}

/*!
 * \brief Supprime toutes les propositions existantes pour un dossier donné.
 * \param d pointeur vers le dossier concerné.
 */
void ChoixManager::removeChoix(Dossier * d) {
    qDebug()<<"dans la suppression des choix";

    ChoixAppli** aSupprimer = trouverPropositionsDossier(d); //tous les choix appli à supprimer
    unsigned int nb=trouverNbPropositionsDossier(d);//leur nombre
    qDebug()<<nb;

    for (unsigned int i=0; i<nb; i++) { //pour chaque choix appli à supprimer
        qDebug()<<"je supprime";

        unsigned int j=0;
        while (ensemblePropositions[j]!=aSupprimer[i]) j++; //j represente alors l'indice du choix appli à supprimer dans la liste du manager
        ChoixAppli* tmp ;

        for (unsigned int k=j; k<nbPropositions-1; k++) {qDebug()<<"je supprime";
            tmp=ensemblePropositions[k]; ensemblePropositions[k]=ensemblePropositions[k+1]; ensemblePropositions[k+1]=tmp;}
        qDebug()<<"avant delete";
        //removeSemestres(ensemblePropositions[nbPropositions-1]);
        delete[] ensemblePropositions[nbPropositions-1];
        nbPropositions--;
    }
}

/*void ChoixManager::removeSemestres(ChoixAppli *c) {

    ChoixAppliSemestre ** listeChoix=c->getListePropositions();

    for (unsigned int i=0; i<c->getNbSemestres(); i++) {delete listeChoix[i]; }
    c->setNbSemestres(0);

}*/

