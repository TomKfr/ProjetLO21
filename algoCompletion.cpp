#include "completion.h"
#include "cursus.h"
#include "dossier.h"
#include<QSet>



ChoixAppli* StrategieConcrete::algoCompletion(ChoixManager& cm, Dossier * d) const {
    UVManager& uvm=UVManager::getInstance();
    cursusManager& curMan=cursusManager::getInstance();
    ChoixAppli * propositionFinale;

    bool first=1;

    //VERIFICATION QUE LETUDIANT NA PAS DEJA FINI SES ETUDES

    unsigned int nbTotalCreditsCS=0;
    unsigned int nbTotalCreditsTM=0;
    unsigned int nbTotalCreditsTSH=0;
    unsigned int nbTotalCreditsSP=0;

    for (typename QMap<QString,Note>::const_iterator it=d->getQmapIteratorUVbegin(); it!=d->getQmapIteratorUVend(); ++it) {
        if (d->estValidee(it.key())) {
                                        UV* uv_concernee = uvm.trouverUV(it.key());
                                        Categorie c=uv_concernee->getCategorie();
                                        if (c==CS) {nbTotalCreditsCS+=uv_concernee->getNbCredits(); }
                                        else if (c==TM) {nbTotalCreditsTM+=uv_concernee->getNbCredits(); }
                                        else if (c==TSH) {nbTotalCreditsTSH+=uv_concernee->getNbCredits(); }
                                        else if (c==SP) {nbTotalCreditsSP+=uv_concernee->getNbCredits();}
                                     }
    } //fin for

    qDebug()<<nbTotalCreditsCS;
    qDebug()<<nbTotalCreditsTM;
    qDebug()<<nbTotalCreditsTSH;
    qDebug()<<nbTotalCreditsSP;
    //FONCTIONNE :)

    formation* f=curMan.trouverForm(d->getFormation());
    if (f==0) throw UTProfilerException("Rentrez une formation dans ce dossier !!");

    unsigned int nbCreditsRequisCS;
    unsigned int nbCreditsRequisTM;
    unsigned int nbCreditsRequisTSH;
    unsigned int nbCreditsRequisSP;

    for (typename QMap<Categorie,unsigned int>::iterator it=f->getCrRequisBegin(); it!=f->getCrRequisEnd(); ++it)
    {
        if (it.key()==CS) nbCreditsRequisCS=it.value();
        else if (it.key()==TM) nbCreditsRequisTM=it.value();
        else if (it.key()==TSH) nbCreditsRequisTSH=it.value();
        if (it.key()==SP) nbCreditsRequisSP=it.value();
    }


    qDebug()<<nbCreditsRequisCS; qDebug()<<nbCreditsRequisTM; qDebug()<<nbCreditsRequisTSH; qDebug()<<nbCreditsRequisSP;
    //FONCTIONNE :)

    unsigned int nbRestantsCreditsCS=nbCreditsRequisCS-nbTotalCreditsCS;
    unsigned int nbRestantsCreditsTM=nbCreditsRequisTM-nbTotalCreditsTM;
    unsigned int nbRestantsCreditsTSH=nbCreditsRequisTSH-nbTotalCreditsTSH;
    unsigned int nbRestantsCreditsSP=nbCreditsRequisSP-nbTotalCreditsSP;

    while(nbRestantsCreditsCS!=0 && nbRestantsCreditsTM !=0 && nbRestantsCreditsTSH!=0 && nbRestantsCreditsSP !=0) {
        //ALORS LETUDIANT NA PAS FINI SES ETUDES : ON VA GENERER UN CHOIX DE LAPPLICATION
        if (first==1) { propositionFinale=new ChoixAppli(2154, d); /*pb de l'id à résoudre*/  first=0; }
        //la premiere fois on créé cet ensemble de semestres proposés en mémoire


        ChoixAppliSemestre * propositionSemestre = new ChoixAppliSemestre(154, d);
        /*pb arguments à résoudre plus tard*/
        propositionFinale->ajouter_proposition(propositionSemestre);

        unsigned int nbCSSemestre=0; //pas plus de 4 cs par semestre
        unsigned int nbTMSemestre=0; //pas plus de 4 tm par semestre
        unsigned int nbTSHSemestre=0; //pas plus de 4 tsh par semestre
        unsigned int nbRestantsCreditsObligatoiresCS=0;
        unsigned int nbRestantsCreditsObligatoiresTM=0;
        unsigned int nbRestantsCreditsObligatoiresTSH=0;
        unsigned int nbRestantsCreditObligatoiresSP=0;
        unsigned int nbUV=0; //<7 sur le semestre
        unsigned int nbCredits=0 ; //<35 sur le semestre

        const QSet<QString>& copie_UVsOblig=f->getUVsObligatoires();
        QSet<QString> CS_obligatoires_restantes;
        QSet<QString> TM_obligatoires_restantes;
        QSet<QString> TSH_obligatoires_restantes;
        QSet<QString> SP_obligatoires_restants;

        //construction de la liste des uvs obligatoires restantes

        for (QSet<QString>::const_iterator it=copie_UVsOblig.begin(); it!=copie_UVsOblig.end(); ++it)
        {
            UV* uv=uvm.trouverUV(*it); //pointeur vers l'uv en elle meme
            const QMap<QString,Note>::const_iterator uvDossier = d->trouverUV(uv->getCode());
            if (uvDossier==0 || (uvDossier!=0 && !(d->estValidee(uv->getCode())))) {
                //alors letudiant n'a pas fait cette uv obligatoire ou il a echoue
                unsigned int nb=uv->getNbCredits();
                if (uv->getCategorie()==CS) {CS_obligatoires_restantes.insert(*it); nbRestantsCreditsObligatoiresCS+=nb;}
                else if (uv->getCategorie()==TM) {TM_obligatoires_restantes.insert(*it); nbRestantsCreditsObligatoiresTM+=nb;}
                else if (uv->getCategorie()==TSH) {TSH_obligatoires_restantes.insert(*it); nbRestantsCreditsObligatoiresTSH+=nb;}
                else if (uv->getCategorie()==SP)  {SP_obligatoires_restants.insert(*it); nbRestantsCreditObligatoiresSP+=nb;}
                }
         }
        //les uvs non obligatoires de la formation restantes
        QSet<QString> CS_formation;
        QSet<QString> TM_formation;
        QSet<QString> TSH_formation;
        QSet<QString> SP_formation;

        QSet<QString>::const_iterator it2;


        for ( QMap<QString,UV*>::const_iterator it=f->getQmapIteratorUVbegin(); it!=f->getQmapIteratorUVend(); ++it)
        {

            UV* uv=uvm.trouverUV(it.key()); //pointeur vers l'uv en elle meme
            QString code=uv->getCode();
            const QMap<QString,Note>::const_iterator uvDossier = d->trouverUV(uv->getCode());
            //renvoie un it pointant sur l'uv dans la liste d'uv du dossier

            if (uvDossier==(d->getListeUV()).end() || (uvDossier!=(d->getListeUV()).end() && !(d->estValidee(uv->getCode())))) {
                //alors letudiant n'a pas fait cette uv ou il a echoue
                unsigned int nb=uv->getNbCredits();
                if (uv->getCategorie()==CS) {
                    it2=find(CS_obligatoires_restantes.begin(), CS_obligatoires_restantes.end(), it.key());
                    if (it2!=CS_obligatoires_restantes.end()) break;
                    CS_formation.insert(code); nbRestantsCreditsObligatoiresCS+=nb;}

                else if (uv->getCategorie()==TM) {
                    it2=find(TM_obligatoires_restantes.begin(), TM_obligatoires_restantes.end(), it.key());
                    if (it2!=TM_obligatoires_restantes.end()) break;
                    TM_formation.insert(code);
                    nbRestantsCreditsObligatoiresTM+=nb;}
                else if (uv->getCategorie()==TSH) {
                    it2=find(TSH_obligatoires_restantes.begin(), TSH_obligatoires_restantes.end(), it.key());
                    if (it2!=TSH_obligatoires_restantes.end()) break;
                    TSH_formation.insert(code);
                    nbRestantsCreditsObligatoiresTSH+=nb;}
                else if (uv->getCategorie()==SP)  {SP_formation.insert(code); nbRestantsCreditObligatoiresSP+=nb;}
                }
         }



while (nbRestantsCreditsObligatoiresCS!=0 && nbRestantsCreditsObligatoiresTM!=0 && nbRestantsCreditsObligatoiresTSH!=0 && /*nbRestantsCreditsObligatoiresSP!=0 */nbUV<=7 && nbCredits<=35) {
            //ON AJOUTE LES UVS OBLIGATOIRES UNE PAR UNE
    QSet<QString>::iterator it;
    QString code_ajout;
    UV* uv_ajout;

    if (nbRestantsCreditsObligatoiresCS!=0 && nbCSSemestre <4) {
        //alors on ajoute une CS
       code_ajout=*(CS_obligatoires_restantes.begin());
       uv_ajout= uvm.trouverUV(code_ajout);

       propositionSemestre->ajoutUV(uv_ajout);

       nbUV++;
       nbCredits+=uv_ajout->getNbCredits();
       nbRestantsCreditsObligatoiresCS-=uv_ajout->getNbCredits();
       nbRestantsCreditsCS-=uv_ajout->getNbCredits();
       it=find(CS_obligatoires_restantes.begin(), CS_obligatoires_restantes.end(), code_ajout);
       CS_obligatoires_restantes.erase(it);//on met à jour la liste des uv obligatoires
       break; //retour au while
        }
    if (nbRestantsCreditsObligatoiresTM!=0 && nbTMSemestre <4) {
        //alors on ajoute une TM
       code_ajout=*(TM_obligatoires_restantes.begin());
       uv_ajout= uvm.trouverUV(code_ajout);

       propositionSemestre->ajoutUV(uv_ajout);

       nbUV++;
       nbCredits+=uv_ajout->getNbCredits();
       nbRestantsCreditsObligatoiresTM-=uv_ajout->getNbCredits();
       nbRestantsCreditsTM-=uv_ajout->getNbCredits();
       it=find(TM_obligatoires_restantes.begin(), TM_obligatoires_restantes.end(), code_ajout);
       TM_obligatoires_restantes.erase(it);
       break; //retour au while
        }

    if (nbRestantsCreditsObligatoiresTSH!=0 && nbTMSemestre <4) {
        //alors on ajoute une TM
       code_ajout=*(TSH_obligatoires_restantes.begin());
       uv_ajout= uvm.trouverUV(code_ajout);

       propositionSemestre->ajoutUV(uv_ajout);

       nbUV++;
       nbCredits+=uv_ajout->getNbCredits();
       nbRestantsCreditsObligatoiresTSH-=uv_ajout->getNbCredits();
       nbRestantsCreditsTSH-=uv_ajout->getNbCredits();
       it=find(TM_obligatoires_restantes.begin(), TM_obligatoires_restantes.end(), code_ajout);
       TM_obligatoires_restantes.erase(it);
       break; //retour au while
        }
//GESION DES STAGES PLUS TARD car on a 1 seul stage par semestre blabla
}//fin while uvs obligatoires, sans tenir compte des souhaits


souhaits* souhaitsDossier = d->getSouhaits();
QSet<QString> copie_exigences = souhaitsDossier->getExigences();
QSet<QString> copie_preferences = souhaitsDossier->getPreferences();
QSet<QString> copie_rejets = souhaitsDossier->getRejets();

while (nbRestantsCreditsCS!=0 && nbRestantsCreditsTM!=0 && nbRestantsCreditsTSH!=0 && /*nbRestantsCreditsSP!=0 */nbUV<=7 && nbCredits<=35) {
//ON AJOUTE LES UVS EN TENANT COMPTE DES SOUHAITS dans un premier temps

    UV* uv_ajout;
    QSet<QString>::const_iterator itRejets;
    QSet<QString>::iterator itAjoute;
    QString code_ajout;

    if (!(copie_exigences.empty()))
         {
        QSet<QString>::const_iterator it=copie_exigences.begin();

        uv_ajout= uvm.trouverUV(*it);

        itRejets=find(copie_rejets.begin(), copie_rejets.end(), uv_ajout->getCode());

        if (itRejets==copie_rejets.end()) {
            //alors cette uv ne fait pas partie des rejets et on peut continuer

            if (uv_ajout->getCategorie()==CS && nbRestantsCreditsCS!=0 && nbCSSemestre <4) {
                //alors on ajoute une CS
               code_ajout=*it;
               uv_ajout= uvm.trouverUV(code_ajout);

               propositionSemestre->ajoutUV(uv_ajout);

               nbUV++;
               nbCredits+=uv_ajout->getNbCredits();
               nbRestantsCreditsCS-=uv_ajout->getNbCredits();
               itAjoute=find(copie_exigences.begin(), copie_exigences.end(), *it);
               copie_exigences.erase(itAjoute);//on met à jour la liste des uv
               break; //retour au while
                }
            if (uv_ajout->getCategorie()==TM && nbRestantsCreditsTM!=0 && nbTMSemestre <4) {
                //alors on ajoute une TM
               code_ajout=*it;
               uv_ajout= uvm.trouverUV(code_ajout);

               propositionSemestre->ajoutUV(uv_ajout);

               nbUV++;
               nbCredits+=uv_ajout->getNbCredits();
               itAjoute=find(copie_exigences.begin(), copie_exigences.end(), *it);
               copie_exigences.erase(itAjoute);//on met à jour la liste des uv
               break; //retour au while
                }

            if (uv_ajout->getCategorie()==TSH && nbRestantsCreditsTSH!=0 && nbTSHSemestre <4) {
                //alors on ajoute une CS
               code_ajout=*it;
               uv_ajout= uvm.trouverUV(code_ajout);

               propositionSemestre->ajoutUV(uv_ajout);

               nbUV++;
               nbCredits+=uv_ajout->getNbCredits();
               itAjoute=find(copie_exigences.begin(), copie_exigences.end(), *it);
               copie_exigences.erase(itAjoute);//on met à jour la liste des uv
               break; //retour au while
                }
        }
   } // fin if not in rejets pour les exigences

    if (!(copie_preferences.empty()))
         {
        QSet<QString>::const_iterator it=copie_preferences.begin();

        uv_ajout= uvm.trouverUV(*it);

        itRejets=find(copie_rejets.begin(), copie_rejets.end(), uv_ajout->getCode());

        if (itRejets==copie_rejets.end()) {
            //alors cette uv ne fait pas partie des rejets et on peut continuer

            if (uv_ajout->getCategorie()==CS && nbRestantsCreditsCS!=0 && nbCSSemestre <4) {
                //alors on ajoute une CS
               code_ajout=*it;
               uv_ajout= uvm.trouverUV(code_ajout);

               propositionSemestre->ajoutUV(uv_ajout);

               nbUV++;
               nbCredits+=uv_ajout->getNbCredits();
               nbRestantsCreditsCS-=uv_ajout->getNbCredits();
               itAjoute=find(copie_preferences.begin(), copie_preferences.end(), *it);
               copie_preferences.erase(itAjoute);//on met à jour la liste des uv
               break; //retour au while
                }
            if (uv_ajout->getCategorie()==TM && nbRestantsCreditsTM!=0 && nbTMSemestre <4) {
                //alors on ajoute une TM
               code_ajout=*it;
               uv_ajout= uvm.trouverUV(code_ajout);

               propositionSemestre->ajoutUV(uv_ajout);

               nbUV++;
               nbCredits+=uv_ajout->getNbCredits();
               itAjoute=find(copie_preferences.begin(), copie_preferences.end(), *it);
               copie_preferences.erase(itAjoute);//on met à jour la liste des uv
               break; //retour au while
                }

            if (uv_ajout->getCategorie()==TSH && nbRestantsCreditsTSH!=0 && nbTSHSemestre <4) {
                //alors on ajoute une CS
               code_ajout=*it;
               uv_ajout= uvm.trouverUV(code_ajout);

               propositionSemestre->ajoutUV(uv_ajout);

               nbUV++;
               nbCredits+=uv_ajout->getNbCredits();
               itAjoute=find(copie_preferences.begin(), copie_preferences.end(), *it);
               copie_preferences.erase(itAjoute);//on met à jour la liste des uv
               break; //retour au while
                }
        }

   } // fin if not in rejets pour les preferences

//ensuite on prend les uvs restantes quelconques

        if (nbRestantsCreditsCS!=0 && nbCSSemestre <4) {
            //alors on ajoute une CS
           code_ajout=*(CS_formation.begin());
           uv_ajout= uvm.trouverUV(code_ajout);

           propositionSemestre->ajoutUV(uv_ajout);

           nbUV++;
           nbCredits+=uv_ajout->getNbCredits();
           nbRestantsCreditsCS-=uv_ajout->getNbCredits();
           itAjoute=find(CS_formation.begin(), CS_formation.end(), code_ajout);
           CS_formation.erase(itAjoute);//on met à jour la liste des uv obligatoires
           break; //retour au while
            }
        if (nbRestantsCreditsTM!=0 && nbTMSemestre <4) {
            //alors on ajoute une TM
           code_ajout=*(TM_formation.begin());
           uv_ajout= uvm.trouverUV(code_ajout);

           propositionSemestre->ajoutUV(uv_ajout);

           nbUV++;
           nbCredits+=uv_ajout->getNbCredits();
           nbRestantsCreditsTM-=uv_ajout->getNbCredits();
           itAjoute=find(TM_formation.begin(), TM_formation.end(), code_ajout);
           TM_formation.erase(itAjoute);//on met à jour la liste des uv obligatoires
           break; //retour au while

            }

        if (nbRestantsCreditsTSH!=0 && nbTSHSemestre <4) {
            //alors on ajoute une TSH
           code_ajout=*(TSH_formation.begin());
           uv_ajout= uvm.trouverUV(code_ajout);

           propositionSemestre->ajoutUV(uv_ajout);

           nbUV++;
           nbCredits+=uv_ajout->getNbCredits();
           nbRestantsCreditsTSH-=uv_ajout->getNbCredits();
           itAjoute=find(TSH_formation.begin(), TSH_formation.end(), code_ajout);
           TSH_formation.erase(itAjoute);//on met à jour la liste des uv obligatoires
           break; //retour au while

            }


}//fin while des autres Uvs


//la liste des uvs proposees est alors complete
propositionSemestre->setNbCredits(nbCredits);
propositionSemestre->setNbUVs(nbUV);


//avant le retour à la boucle pour un semestre suivant : mise à jour du choix en cours de remplissage
souhaitsDossier->setExigences(copie_exigences);
souhaitsDossier->setPreferences(copie_preferences);

}//fin while general



}//fin fonction

