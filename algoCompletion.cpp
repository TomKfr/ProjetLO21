#include "completion.h"
#include "cursus.h"
#include "dossier.h"
#include<QSet>


/*!
 * \brief Algorithme de complétion automatique, génère une propsition pour le dossier en cours.
 * \param cm référence vers le ChoixManager
 * \param d pointeur vers le dossier concerné
 * \return une proposition de fin de cursus sous forme d'un objet ChoixAppli.
 */
ChoixAppli* StrategieConcrete::algoCompletion(ChoixManager& cm, Dossier * d) const {
    qDebug()<<"DANS LE CALCUL DE COMPLETION";
    UVManager& uvm=UVManager::getInstance();
    cursusManager& curMan=cursusManager::getInstance();
    ChoixAppli * propositionFinale;
    Semestre semestre = cm.getSemestreActuel();

    qDebug()<<semestre.getAnnee();
    qDebug()<<semestre.getSaison();

    cm.setCreationLastProposition(0);
    bool first=0;
    bool stage=0;

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

    formation* f=curMan.trouverForm(d->getFormation());
    if (f==0) throw UTProfilerException("Rentrez une formation dans ce dossier !!");

    unsigned int nbCreditsRequisCS;
    unsigned int nbCreditsRequisTM;
    unsigned int nbCreditsRequisTSH;
    unsigned int nbCreditsRequisSP; //les memes pour toutes les branches

    for (typename QMap<Categorie,unsigned int>::iterator it=f->getCrRequisBegin(); it!=f->getCrRequisEnd(); ++it)
    {
        if (it.key()==CS) nbCreditsRequisCS=it.value();
        else if (it.key()==TM) nbCreditsRequisTM=it.value();
        else if (it.key()==TSH) nbCreditsRequisTSH=it.value();
        else if (it.key()==SP) nbCreditsRequisSP=it.value();
    }
    qDebug()<<nbCreditsRequisCS;
    qDebug()<<nbCreditsRequisTM;
    qDebug()<<nbCreditsRequisTSH;
    qDebug()<<nbCreditsRequisSP;

    qDebug()<<nbTotalCreditsCS;
    qDebug()<<nbTotalCreditsTM;
    qDebug()<<nbTotalCreditsTSH;
    qDebug()<<nbTotalCreditsSP;


    int nbRestantsCreditsCS=nbCreditsRequisCS-nbTotalCreditsCS;
    int nbRestantsCreditsTM=nbCreditsRequisTM-nbTotalCreditsTM;
    int nbRestantsCreditsTSH=nbCreditsRequisTSH-nbTotalCreditsTSH;
    int nbRestantsCreditsSP=nbCreditsRequisSP-nbTotalCreditsSP;

    qDebug()<<"credits restants :";
    qDebug()<<nbRestantsCreditsCS;
    qDebug()<<nbRestantsCreditsTM;
    qDebug()<<nbRestantsCreditsTSH;
    qDebug()<<nbRestantsCreditsSP;

    qDebug()<<"avant while";

while(nbRestantsCreditsCS>0 || nbRestantsCreditsTM >0 || nbRestantsCreditsTSH>0 || nbRestantsCreditsSP >0) {
        //ALORS LETUDIANT NA PAS FINI SES ETUDES : ON VA GENERER UN CHOIX DE LAPPLICATION POUR UN SEMESTRE
        cm.setCreationLastProposition(1);

        qDebug()<<"Calcul d'une propositionSemestre";
        stage=0; //indique qu'on ne cherche plus d'uv car il y a deja un stage
        if (first==0) {
            unsigned int id = cm.getNbPropositions();
            qDebug()<<"identifiant :"<<id;
            propositionFinale=new ChoixAppli(++id, d);
            qDebug()<<"crée ici";
            first=1; //on ne créé l'ensemble de propositions de semestre 1 seule fois par calcul de completion
            cm.ajouterProposition(propositionFinale);
            qDebug()<<"ajouter proposition effectuee";
            cm.setLastProposition(propositionFinale);
            qDebug()<<"proposition finale creee";
        }
        //la premiere fois on créé cet ensemble de semestres proposés en mémoire

        unsigned int id2=cm.getNbChoixSemestre();
        qDebug()<<"avant creation de proposition semestre, ";
        ++semestre;
        ChoixAppliSemestre * propositionSemestre = new ChoixAppliSemestre(++id2, d, semestre, propositionFinale);
        qDebug()<<"proposition semestre creee";
        qDebug()<<propositionFinale;
        qDebug()<<propositionSemestre; // OK


        propositionFinale->ajouter_proposition(propositionSemestre);
        qDebug()<<"MAJ choix appli";
        qDebug()<<propositionFinale->getNbSemestres(); // OK

        unsigned int nbCSSemestre=0; //pas plus de 4 cs par semestre
        unsigned int nbTMSemestre=0; //pas plus de 4 tm par semestre
        unsigned int nbTSHSemestre=0; //pas plus de 4 tsh par semestre
        unsigned int nbSPSemestre=0; //pas plus de 1 stage par semestre

        int nbRestantsCreditsObligatoiresCS=0;
        int nbRestantsCreditsObligatoiresTM=0;
        int nbRestantsCreditsObligatoiresTSH=0;
        int nbRestantsCreditsObligatoiresSP=0;

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
            qDebug()<<"une uv obligatoire";
            UV* uv=uvm.trouverUV(*it); //pointeur vers l'uv en elle meme
            qDebug()<<uv->getCode();

            QMap<QString,Note> listeUV=d->getListeUV();

            const QMap<QString,Note>::const_iterator uvDossier = d->trouverUV(uv->getCode());

            if (uvDossier==listeUV.end() || (uvDossier!=listeUV.end() && !(d->estValidee(uv->getCode())))) {
                //alors letudiant n'a pas fait cette uv obligatoire ou il a echoue
                qDebug()<<"UV non faite";
                unsigned int nb=uv->getNbCredits();
                if (uv->getCategorie()==CS) {qDebug()<<"une cs obligatoire"; CS_obligatoires_restantes.insert(*it); nbRestantsCreditsObligatoiresCS+=nb;}
                else if (uv->getCategorie()==TM) {qDebug()<<"une tm obligatoire";TM_obligatoires_restantes.insert(*it); nbRestantsCreditsObligatoiresTM+=nb;}
                else if (uv->getCategorie()==TSH) {TSH_obligatoires_restantes.insert(*it); nbRestantsCreditsObligatoiresTSH+=nb;}
                else if (uv->getCategorie()==SP)  {SP_obligatoires_restants.insert(*it); nbRestantsCreditsObligatoiresSP+=nb;}
                }
         }

        qDebug()<<"liste obligatoires remplies";

        //OK

        //les uvs non obligatoires de la formation restantes
        QSet<QString> CS_formation;
        QSet<QString> TM_formation;
        QSet<QString> TSH_formation;
        QSet<QString> SP_formation;

        QSet<QString>::const_iterator it2;

        qDebug()<<"avant liste2";

        QMap<QString,UV*> uvFormation=f->getUVFormation();
        qDebug()<<uvFormation;
        qDebug()<<uvFormation.begin().key();//OK

        for ( QMap<QString,UV*>::const_iterator it3=uvFormation.begin(); it3!=uvFormation.end(); ++it3)
        {
            qDebug()<<"encore une uv!";
            UV* uv=uvm.trouverUV(it3.key()); //pointeur vers l'uv en elle meme
            qDebug()<< it3.key(); qDebug()<<uv ;
            QString code=uv->getCode();
            const QMap<QString,Note>::const_iterator uvDossier = d->trouverUV(uv->getCode());
            //renvoie un it pointant sur l'uv dans la liste d'uv du dossier

            if (uvDossier==(d->getListeUV()).end() || (uvDossier!=(d->getListeUV()).end() && !(d->estValidee(uv->getCode())))) {
                //alors letudiant n'a pas fait cette uv ou il a echoue
                unsigned int nb=uv->getNbCredits();
                if (uv->getCategorie()==CS) {
                    it2=find(CS_obligatoires_restantes.begin(), CS_obligatoires_restantes.end(), it3.key());
                    if (it2!=CS_obligatoires_restantes.end()) break;
                    CS_formation.insert(code); nbRestantsCreditsObligatoiresCS+=nb;}

                else if (uv->getCategorie()==TM) {
                    it2=find(TM_obligatoires_restantes.begin(), TM_obligatoires_restantes.end(), it3.key());
                    if (it2!=TM_obligatoires_restantes.end()) break;
                    TM_formation.insert(code);
                    nbRestantsCreditsObligatoiresTM+=nb;}
                else if (uv->getCategorie()==TSH) {
                    it2=find(TSH_obligatoires_restantes.begin(), TSH_obligatoires_restantes.end(), it3.key());
                    if (it2!=TSH_obligatoires_restantes.end()) break;
                    TSH_formation.insert(code);
                    nbRestantsCreditsObligatoiresTSH+=nb;}
                else if (uv->getCategorie()==SP)  {it2=find(SP_obligatoires_restants.begin(), SP_obligatoires_restants.end(), it3.key());
                    if (it2!=SP_obligatoires_restants.end()) break;
                    SP_formation.insert(code);
                    nbRestantsCreditsObligatoiresSP+=nb;}
                }
         }

        qDebug()<<"autres listes remplies";



while (( (nbRestantsCreditsObligatoiresCS>0 && !(CS_obligatoires_restantes.empty()) ) ||  ( nbRestantsCreditsObligatoiresTM>0 && !(TM_obligatoires_restantes.empty()))
         || ( nbRestantsCreditsObligatoiresTSH>0 && !(TSH_obligatoires_restantes.empty())) ||
         ( nbRestantsCreditsObligatoiresSP>0 && !(SP_obligatoires_restants.empty())) ) && nbUV<=7 && nbCredits<=35 && stage==0) {
            //ON AJOUTE LES UVS OBLIGATOIRES UNE PAR UNE
    qDebug()<<"je demarre l'affectation des uvs obligatoires";
    qDebug()<<nbRestantsCreditsObligatoiresCS;
    qDebug()<<nbRestantsCreditsObligatoiresTM;
    qDebug()<<nbRestantsCreditsObligatoiresTSH;
    qDebug()<<nbRestantsCreditsObligatoiresSP;
    QSet<QString>::iterator it;
    QString code_ajout;
    UV* uv_ajout;

    qDebug()<<"avant la serie de if";

    if (nbRestantsCreditsObligatoiresSP>0 && nbSPSemestre <1 && !(SP_obligatoires_restants.empty())) {
        //alors on ajoute un stage
       code_ajout=*(SP_obligatoires_restants.begin());
       uv_ajout= uvm.trouverUV(code_ajout);

       if(code_ajout=="TN05" && d->getNumSemestre()<2 ) break; //TN05 impossible : trop tôt
       else if(code_ajout=="TN09" && (d->getNumSemestre()>3 || d->getNumSemestre()<2 )) break; //TN09 impossible
       else if(code_ajout=="TN10" && d->getNumSemestre()<4 ) break; //TN10 impossible : trop tôt

       propositionSemestre->ajoutUV(uv_ajout);

       nbUV++;
       nbCredits+=uv_ajout->getNbCredits();
       nbRestantsCreditsObligatoiresSP-=uv_ajout->getNbCredits();
       nbRestantsCreditsSP-=uv_ajout->getNbCredits();
       it=find(SP_obligatoires_restants.begin(), SP_obligatoires_restants.end(), code_ajout);
       SP_obligatoires_restants.erase(it);//on met à jour la liste des uv obligatoires
       if (code_ajout=="TN09" || code_ajout=="TN10") {propositionSemestre->setStage(1); stage=1;}
       //retour au while
        }

    else if (nbRestantsCreditsObligatoiresCS>0 && nbCSSemestre <4 && !(CS_obligatoires_restantes.empty())) {
        //alors on ajoute une CS
       qDebug()<<"jajoute une cs";
       code_ajout=*(CS_obligatoires_restantes.begin());
       qDebug()<<code_ajout;
       uv_ajout= uvm.trouverUV(code_ajout);
       qDebug()<<"adresse de l'uv "<<uv_ajout;

       propositionSemestre->ajoutUV(uv_ajout);
       qDebug()<<"proposition semestre completee" ;

       nbUV++;
       nbCredits+=uv_ajout->getNbCredits();
       nbRestantsCreditsObligatoiresCS-=uv_ajout->getNbCredits();
       nbRestantsCreditsCS-=uv_ajout->getNbCredits();
       it=find(CS_obligatoires_restantes.begin(), CS_obligatoires_restantes.end(), code_ajout);
       CS_obligatoires_restantes.erase(it);//on met à jour la liste des uv obligatoires
       qDebug()<<"termine ici";
       qDebug()<<"je vais quelque part";
       //retour au while
        }

    else if (nbRestantsCreditsObligatoiresTM>0 && nbTMSemestre <4 && !(TM_obligatoires_restantes.empty())) {
        //alors on ajoute une TM
       qDebug()<<"jajoute une tm obligatoire car je nai que ces credits : "<<nbRestantsCreditsObligatoiresTM;
       code_ajout=*(TM_obligatoires_restantes.begin());
       uv_ajout= uvm.trouverUV(code_ajout);
       qDebug()<<code_ajout;

       propositionSemestre->ajoutUV(uv_ajout);
       qDebug()<<"uv ajoutee";
       qDebug()<<propositionSemestre->getNbUV();

       nbUV++;
       nbCredits+=uv_ajout->getNbCredits();
       nbRestantsCreditsObligatoiresTM-=uv_ajout->getNbCredits();
       nbRestantsCreditsTM-=uv_ajout->getNbCredits();
       it=find(TM_obligatoires_restantes.begin(), TM_obligatoires_restantes.end(), code_ajout);
       TM_obligatoires_restantes.erase(it);
       qDebug()<<"termine pour les tm";
       qDebug()<<"je retourne au while car je suis gentil";
        //retour au while
        }

    else if (nbRestantsCreditsObligatoiresTSH>0 && nbTSHSemestre <4 && !(TSH_obligatoires_restantes.empty())) {
        //alors on ajoute une TSH
       code_ajout=*(TSH_obligatoires_restantes.begin());
       uv_ajout= uvm.trouverUV(code_ajout);

       propositionSemestre->ajoutUV(uv_ajout);

       nbUV++;
       nbCredits+=uv_ajout->getNbCredits();
       nbRestantsCreditsObligatoiresTSH-=uv_ajout->getNbCredits();
       nbRestantsCreditsTSH-=uv_ajout->getNbCredits();
       it=find(TSH_obligatoires_restantes.begin(), TSH_obligatoires_restantes.end(), code_ajout);
       TSH_obligatoires_restantes.erase(it);
        //retour au while
        }

}//fin while uvs obligatoires, sans tenir compte des souhaits


souhaits* souhaitsDossier = d->getSouhaits();
QSet<QString> copie_exigences = souhaitsDossier->getExigences();
QSet<QString> copie_preferences = souhaitsDossier->getPreferences();
QSet<QString> copie_rejets = souhaitsDossier->getRejets();

qDebug()<<"affectation des uvs obligatoires terminees";
qDebug()<<nbRestantsCreditsCS;
qDebug()<<nbRestantsCreditsTM;
qDebug()<<nbRestantsCreditsTSH;
qDebug()<<nbRestantsCreditsSP;

while ((nbRestantsCreditsCS>0 || nbRestantsCreditsTM>0 || nbRestantsCreditsTSH>0 || nbRestantsCreditsSP>0) && nbUV<=7 && nbCredits<=35 && stage==0) {
//on ne modifie plus le bool stage pour les stages car les stages d'un semestre sont dans la categorie obligatoire deja exploree
//ON AJOUTE LES UVS EN TENANT COMPTE DES SOUHAITS dans un premier temps

    UV* uv_ajout;
    QSet<QString>::const_iterator itRejets;
    QSet<QString>::iterator itAjoute;
    QString code_ajout;

    //qDebug()<<"while des uvs non obligatoires";

    if (!(copie_exigences.empty()))
         {
        QSet<QString>::const_iterator it=copie_exigences.begin();

        uv_ajout= uvm.trouverUV(*it);

        itRejets=find(copie_rejets.begin(), copie_rejets.end(), uv_ajout->getCode());

        if (itRejets==copie_rejets.end()) {
            //alors cette uv ne fait pas partie des rejets et on peut continuer

              if (uv_ajout->getCategorie()==SP && nbRestantsCreditsSP>0 && nbSPSemestre <1) {
                   //alors on ajoute un stage souhaité, par ex un TN07
                  code_ajout=*it;
                  uv_ajout= uvm.trouverUV(code_ajout);

                  propositionSemestre->ajoutUV(uv_ajout);

                  nbUV++;
                  nbCredits+=uv_ajout->getNbCredits();
                  nbRestantsCreditsSP-=uv_ajout->getNbCredits();
                  itAjoute=find(copie_exigences.begin(), copie_exigences.end(), *it);
                  copie_exigences.erase(itAjoute);//on met à jour la liste des uv
                   //retour au while
                   }

            else if (uv_ajout->getCategorie()==CS && nbRestantsCreditsCS>0 && nbCSSemestre <4) {
                //alors on ajoute une CS
               code_ajout=*it;
               uv_ajout= uvm.trouverUV(code_ajout);

               propositionSemestre->ajoutUV(uv_ajout);

               nbUV++;
               nbCredits+=uv_ajout->getNbCredits();
               nbRestantsCreditsCS-=uv_ajout->getNbCredits();
               itAjoute=find(copie_exigences.begin(), copie_exigences.end(), *it);
               copie_exigences.erase(itAjoute);//on met à jour la liste des uv
                //retour au while
                }
            else if (uv_ajout->getCategorie()==TM && nbRestantsCreditsTM>0 && nbTMSemestre <4) {
                //alors on ajoute une TM
               code_ajout=*it;
               uv_ajout= uvm.trouverUV(code_ajout);

               propositionSemestre->ajoutUV(uv_ajout);

               nbUV++;
               nbCredits+=uv_ajout->getNbCredits();
               itAjoute=find(copie_exigences.begin(), copie_exigences.end(), *it);
               copie_exigences.erase(itAjoute);//on met à jour la liste des uv
                //retour au while
                }

            else if (uv_ajout->getCategorie()==TSH && nbRestantsCreditsTSH>0 && nbTSHSemestre <4) {
                //alors on ajoute une CS
               code_ajout=*it;
               uv_ajout= uvm.trouverUV(code_ajout);

               propositionSemestre->ajoutUV(uv_ajout);

               nbUV++;
               nbCredits+=uv_ajout->getNbCredits();
               itAjoute=find(copie_exigences.begin(), copie_exigences.end(), *it);
               copie_exigences.erase(itAjoute);//on met à jour la liste des uv
                //retour au while
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

             if (uv_ajout->getCategorie()==SP && nbRestantsCreditsSP>0 && nbSPSemestre <4) {
                   //alors on ajoute un stage
                  code_ajout=*it;
                  uv_ajout= uvm.trouverUV(code_ajout);

                  propositionSemestre->ajoutUV(uv_ajout);

                  nbUV++;
                  nbCredits+=uv_ajout->getNbCredits();
                  nbRestantsCreditsSP-=uv_ajout->getNbCredits();
                  itAjoute=find(copie_preferences.begin(), copie_preferences.end(), *it);
                  copie_preferences.erase(itAjoute);//on met à jour la liste des uv
                 //retour au while
                   }

            else if (uv_ajout->getCategorie()==CS && nbRestantsCreditsCS>0 && nbCSSemestre <4) {
                //alors on ajoute une CS
               code_ajout=*it;
               uv_ajout= uvm.trouverUV(code_ajout);

               propositionSemestre->ajoutUV(uv_ajout);

               nbUV++;
               nbCredits+=uv_ajout->getNbCredits();
               nbRestantsCreditsCS-=uv_ajout->getNbCredits();
               itAjoute=find(copie_preferences.begin(), copie_preferences.end(), *it);
               copie_preferences.erase(itAjoute);//on met à jour la liste des uv
                //retour au while
                }
            else if (uv_ajout->getCategorie()==TM && nbRestantsCreditsTM>0 && nbTMSemestre <4) {
                //alors on ajoute une TM
               code_ajout=*it;
               uv_ajout= uvm.trouverUV(code_ajout);

               propositionSemestre->ajoutUV(uv_ajout);

               nbUV++;
               nbCredits+=uv_ajout->getNbCredits();
               itAjoute=find(copie_preferences.begin(), copie_preferences.end(), *it);
               copie_preferences.erase(itAjoute);//on met à jour la liste des uv
                //retour au while
                }

           else if (uv_ajout->getCategorie()==TSH && nbRestantsCreditsTSH>0 && nbTSHSemestre <4) {
                //alors on ajoute une CS
               code_ajout=*it;
               uv_ajout= uvm.trouverUV(code_ajout);

               propositionSemestre->ajoutUV(uv_ajout);

               nbUV++;
               nbCredits+=uv_ajout->getNbCredits();
               itAjoute=find(copie_preferences.begin(), copie_preferences.end(), *it);
               copie_preferences.erase(itAjoute);//on met à jour la liste des uv
                //retour au while
                }
        }

   } // fin if not in rejets pour les preferences

//ensuite on prend les uvs restantes quelconques

       if (nbRestantsCreditsSP>0 && nbSPSemestre <1 && !(SP_formation.empty())) {
           //alors on ajoute un stage
          code_ajout=*(SP_formation.begin());
          uv_ajout= uvm.trouverUV(code_ajout);

          propositionSemestre->ajoutUV(uv_ajout);

          nbUV++;
          nbCredits+=uv_ajout->getNbCredits();
          nbRestantsCreditsSP-=uv_ajout->getNbCredits();
          itAjoute=find(SP_formation.begin(), SP_formation.end(), code_ajout);
          SP_formation.erase(itAjoute);//on met à jour la liste des uv obligatoires
           //retour au while
           }


       else if (nbRestantsCreditsCS>0 && nbCSSemestre <4 && !(CS_formation.empty())) {
            //alors on ajoute une CS
           code_ajout=*(CS_formation.begin());
           uv_ajout= uvm.trouverUV(code_ajout);

           propositionSemestre->ajoutUV(uv_ajout);

           nbUV++;
           nbCredits+=uv_ajout->getNbCredits();
           nbRestantsCreditsCS-=uv_ajout->getNbCredits();
           itAjoute=find(CS_formation.begin(), CS_formation.end(), code_ajout);
           CS_formation.erase(itAjoute);//on met à jour la liste des uv obligatoires
            //retour au while
            }
        else if (nbRestantsCreditsTM>0 && nbTMSemestre <4 && !(TM_formation.empty())) {
            //alors on ajoute une TM
           code_ajout=*(TM_formation.begin());
           uv_ajout= uvm.trouverUV(code_ajout);

           propositionSemestre->ajoutUV(uv_ajout);

           nbUV++;
           nbCredits+=uv_ajout->getNbCredits();
           nbRestantsCreditsTM-=uv_ajout->getNbCredits();
           itAjoute=find(TM_formation.begin(), TM_formation.end(), code_ajout);
           TM_formation.erase(itAjoute);//on met à jour la liste des uv obligatoires
            //retour au while

            }

        else if (nbRestantsCreditsTSH>0 && nbTSHSemestre <4 && !(TSH_formation.empty())) {
            //alors on ajoute une TSH
           code_ajout=*(TSH_formation.begin());
           uv_ajout= uvm.trouverUV(code_ajout);

           propositionSemestre->ajoutUV(uv_ajout);

           nbUV++;
           nbCredits+=uv_ajout->getNbCredits();
           nbRestantsCreditsTSH-=uv_ajout->getNbCredits();
           itAjoute=find(TSH_formation.begin(), TSH_formation.end(), code_ajout);
           TSH_formation.erase(itAjoute);//on met à jour la liste des uv obligatoires
            //retour au while

            }


}//fin while des autres Uvs


qDebug()<<"fin du travail pour ce semestre";

//la liste des uvs proposees est alors complete
propositionSemestre->setNbCredits(nbCredits);
propositionSemestre->setNbUVs(nbUV);


//avant le retour à la boucle pour un semestre suivant : mise à jour du choix en cours de remplissage
souhaitsDossier->setExigences(copie_exigences);
souhaitsDossier->setPreferences(copie_preferences);

}//fin while general

qDebug()<<"fin de l'algo";

}//fin fonction

