#include"completion.h"
#include"dossier.h"
#include"UTProfiler.h"
#include <sstream>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>
#include <QFileDialog>


/*!
 * \brief Charge les solutions proposées par l'algorihtme de completion automatique précédemment sauvegardées
 */
void ChoixManager::load_completion()
{
try{
    file=QDir::currentPath()+"/completions.xml";
    QFile f(file);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {throw UTProfilerException("Erreur ouverture fichier completions");}
    QXmlStreamReader xml(&f);
    while(!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartDocument) continue;
        if(token == QXmlStreamReader::StartElement) {
            if(xml.name() == "completions") continue;
            if(xml.name() == "completion") {
                unsigned int id;
                unsigned int numDossier;
                unsigned int credits;
                unsigned int annee;
                unsigned int nbUVs;
                unsigned int idChoixAppli;
                QString s;
                QString r;
                Saison saison;
                Reponse reponse;

                QStringList listUV;
                ChoixAppliSemestre* c;
                ChoixAppli* parent;
                Dossier * d;

                xml.readNext();

                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "completion")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {

                        if(xml.name() == "identifiant") {
                            xml.readNext(); id=xml.text().toString().toUInt();
                        }

                        if(xml.name() == "dossier") {
                            xml.readNext(); numDossier=xml.text().toString().toUInt();

                            qDebug()<<xml.name();
                            DossierManager& dm=DossierManager::getInstance();
                            d=dm.trouverDossier(numDossier);
                        }
                        if(xml.name() == "idChoixAppli") {
                            xml.readNext(); idChoixAppli=xml.text().toUInt();

                            ChoixManager& cm=ChoixManager::getInstance();
                            parent=cm.trouverProposition(idChoixAppli);
                            if (parent==0) { parent=new ChoixAppli(id,d); cm.ajouterProposition(parent);}
                        }

                        if(xml.name() == "semestre")
                        {
                             xml.readNext();
                           while(!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="semestre"))
                            {

                                qDebug()<<"dans le semestre";
                                        if(xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="saison")
                                        {
                                            xml.readNext();
                                            s=xml.text().toString();
                                            saison=StringToSaison(s);
                                        }

                                        if(xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="annee")
                                        {
                                            xml.readNext();
                                            annee=xml.text().toUInt();
                                        }


                                        xml.readNext();
                                    }
                                }

                        if(xml.name() == "credits") {
                            xml.readNext(); credits=xml.text().toString().toUInt();
                        }


                        if(xml.name() == "uvs")
                        {
                            nbUVs=0;
                            xml.readNext();
                            while(!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="uvs"))
                            {
                                if(xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="uv")
                                {
                                    nbUVs++;
                                    xml.readNext();
                                    listUV<<xml.text().toString();
                                }


                                xml.readNext();
                            }

                            Semestre s(saison, annee);
                            c=new ChoixAppliSemestre(id, d, s, parent, credits, nbUVs);
                            parent->ajouter_proposition(c);


                        }//fin if pour uv

                        if(xml.name() == "reponse") {
                            xml.readNext(); r=xml.text().toString();
                            reponse=StringToReponse(r);

                            parent->setReponse(reponse);
                            DossierManager& dm=DossierManager::getInstance();
                            d=dm.trouverDossier(numDossier);
                        }
                    }
                    xml.readNext();
                }

                if(!listUV.empty())
                {
                    visiteurCompletion* v=new visiteurCompletion(c, listUV, d);
                    v->visitUVmanager();
                    d->acceptCompletion(v);
                }
            }
        }
    }
    if(xml.hasError()) {
        throw UTProfilerException("Erreur lecteur fichier dossier, parser xml");
    }
    xml.clear();
    }
    catch(UTProfilerException& e){QMessageBox::warning(0,"Erreur",e.getInfo());}
}

/*!
 * \brief Sauvegarde dans le fichier completions.xml les solutions en mémoire.
 */
void ChoixManager::save_completion(){
    file=QDir::currentPath()+"/completions.xml";
    QFile newfile(file);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text)) throw UTProfilerException(QString("erreur ouverture fichier xml"));
     QXmlStreamWriter stream(&newfile);
     stream.setAutoFormatting(true);
     stream.writeStartDocument();
     stream.writeStartElement("completions");



for (unsigned int j=0; j<nbPropositions; j++)
{
    ChoixAppliSemestre ** ens_choix=ensemblePropositions[j]->getListePropositions();
    unsigned int limit=ensemblePropositions[j]->getNbSemestres();

     for(unsigned int i=0; i<limit; i++){
         ChoixAppliSemestre * choix=ens_choix[i];
         stream.writeStartElement("completion");

         QString n; n.setNum(choix->getId());
         stream.writeTextElement("identifiant", n);

         Dossier * dos = choix->getDossier();
         QString numDossier=QString::number(dos->getNumero());
         stream.writeTextElement("dossier", numDossier);

         ChoixAppli* parent=choix->getParent();
         stream.writeTextElement("idChoixAppli", QString::number(parent->getIdentifiant()));

         stream.writeStartElement("semestre");
         Semestre s=choix->getSemestre();

         Saison saison=s.getSaison() ;
         QString annee=QString::number(s.getAnnee());
         QString saisonString= SaisonToString(saison);
         stream.writeTextElement("saison",saisonString);
         stream.writeTextElement("annee",annee);
         stream.writeEndElement();

         QString credits=QString::number(choix->getNbCredits());
         stream.writeTextElement("credits",credits);

         //ecriture des UV

         stream.writeStartElement("uvs");
         for(QMap<QString,UV*>::iterator it=choix->getQmapIteratorUVbegin();it!=choix->getQmapIteratorUVend(); it++)
         {
             stream.writeTextElement("uv",it.key());

         }

         stream.writeEndElement();//fin uv
         stream.writeTextElement("reponse", ReponseToString(ensemblePropositions[j]->getReponse()));
          stream.writeEndElement();
         // stream.writeEndElement();
     }
}
     stream.writeEndElement();
     stream.writeEndDocument();

     newfile.close();
}


