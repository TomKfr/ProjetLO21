#include"completion.h"
#include"dossier.h"
#include"UTProfiler.h"
#include <sstream>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>
#include <QFileDialog>



void ChoixManager::load_completion()
{
try{
    file=QDir::currentPath()+"/completions.xml";
    qDebug()<<"Chargement Completions!";
    QFile f(file);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {throw UTProfilerException("Erreur ouverture fichier completions");}
    QXmlStreamReader xml(&f);
    while(!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartDocument) continue;
        if(token == QXmlStreamReader::StartElement) {
            if(xml.name() == "completions") continue;
            qDebug()<<"completions1";
            if(xml.name() == "completion") {
                qDebug()<<"completions2";
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
                        qDebug()<<"completions6";

                        if(xml.name() == "identifiant") {
                            qDebug()<<"je pecho un identifiant";
                            xml.readNext(); id=xml.text().toString().toUInt();
                        }

                        if(xml.name() == "dossier") {
                            qDebug()<<"dossier";
                            xml.readNext(); numDossier=xml.text().toString().toUInt();

                            qDebug()<<xml.name();
                            DossierManager& dm=DossierManager::getInstance();
                            d=dm.trouverDossier(numDossier);
                        }
                        if(xml.name() == "idChoixAppli") {
                            qDebug()<<"idChoixAppli";
                            xml.readNext(); idChoixAppli=xml.text().toUInt();

                            ChoixManager& cm=ChoixManager::getInstance();
                            parent=cm.trouverProposition(id);
                            if (parent==0) { parent=new ChoixAppli(id,d); cm.ajouterProposition(parent);
                                qDebug()<<"dans le manager : nb choix appli"<<cm.getNbPropositions();}
                            qDebug()<<xml.name();
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
                                            qDebug()<<"saison :"<<saison;
                                        }

                                        if(xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="annee")
                                        {
                                            qDebug()<<"annee";
                                            xml.readNext();
                                            annee=xml.text().toUInt();
                                            qDebug()<<annee;
                                        }


                                        xml.readNext();
                                    }
                                }

                        qDebug()<<"completions7";
                        qDebug()<<xml.name();

                        if(xml.name() == "credits") {
                            qDebug()<<"completions8";
                            xml.readNext(); credits=xml.text().toString().toUInt();
                        }


                        if(xml.name() == "uvs")
                        {
                            qDebug()<<"les uvs";
                            nbUVs=0;
                            xml.readNext();
                            while(!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="uvs"))
                            {
                                if(xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="uv")
                                {
                                    qDebug()<<"une uv";
                                    nbUVs++;
                                    xml.readNext();
                                    listUV<<xml.text().toString();
                                }


                                xml.readNext();
                            }

                            Semestre s(saison, annee);
                            qDebug()<<s.getAnnee();
                            qDebug()<<s.getSaison();


                            c=new ChoixAppliSemestre(id, d, s, parent, credits, nbUVs);
                            parent->ajouter_proposition(c);
                            qDebug()<<"dans le choix appli combien de semestres "<<parent->getNbSemestres();


                        }//fin if pour uv

                        if(xml.name() == "reponse") {
                            qDebug()<<"reponse";
                            xml.readNext(); r=xml.text().toString();
                            qDebug()<<r;
                            reponse=StringToReponse(r);

                            parent->setReponse(reponse);
                            qDebug()<<parent->getReponse();
                            DossierManager& dm=DossierManager::getInstance();
                            d=dm.trouverDossier(numDossier);
                        }




                    }
                    xml.readNext();
                }
                qDebug()<<listUV;

                if(!listUV.empty())
                {
                    visiteurCompletion* v=new visiteurCompletion(c, listUV, d);
                    v->visitUVmanager();
                    qDebug()<<"visit uv manager : done";
                    d->acceptCompletion(v);
                    qDebug()<<"accept : done";
                }

            }
        }
    }
    if(xml.hasError()) {
        throw UTProfilerException("Erreur lecteur fichier dossier, parser xml");
    }
    xml.clear();
    qDebug()<<"Chargement Completions termine!";
    }
    catch(UTProfilerException& e){QMessageBox::warning(0,"Erreur",e.getInfo());}
}


void ChoixManager::save_completion(){
    qDebug() << "Save Completions";
    file=QDir::currentPath()+"/completions.xml";
    QFile newfile(file);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text)) throw UTProfilerException(QString("erreur ouverture fichier xml"));
    qDebug()<<"point1";
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
         qDebug()<<"ecriture d'une proposition sur un semestre' "<<i;
         stream.writeStartElement("completion");

         qDebug()<<"point3";

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
         qDebug()<<"point4";


         //ecriture des UV

         stream.writeStartElement("uvs");
         for(QMap<QString,UV*>::iterator it=choix->getQmapIteratorUVbegin();it!=choix->getQmapIteratorUVend(); it++)
         {
             stream.writeTextElement("uv",it.key());

         }

         stream.writeEndElement();//fin uv
         stream.writeTextElement("reponse", ReponseToString(ensemblePropositions[j]->getReponse()));


          qDebug()<<"3";
          stream.writeEndElement();
          stream.writeEndElement();
          qDebug()<<"4";
     }
}
     stream.writeEndElement();
     stream.writeEndDocument();

     newfile.close();
}


