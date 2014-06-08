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
                unsigned int idChoixAppli;
                QString s;
                Saison saison;

                QStringList listUV;
                ChoixAppliSemestre* c;
                ChoixAppli* parent=0;
                Dossier * d;

                xml.readNext();

                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "completion")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        qDebug()<<"completions6";
                        qDebug()<<xml.name();

                        if(xml.name() == "identifiant") {
                            xml.readNext(); id=xml.text().toString().toUInt();
                        }

                        qDebug()<<xml.name();

                        if(xml.name() == "dossier") {
                            xml.readNext(); numDossier=xml.text().toString().toUInt();
                            qDebug()<<xml.name();
                        }
                        if(xml.name() == "idChoixAppli") {
                            xml.readNext(); idChoixAppli=xml.text().toUInt();
                            ChoixManager& cm=ChoixManager::getInstance();
                            parent=cm.trouverProposition(id);
                            qDebug()<<xml.name();
                        }

                        if(xml.name() == "semestre")
                        {
                            while(!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="semestre"))
                            {
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

                        qDebug()<<"completions7";
                        qDebug()<<xml.name();

                        if(xml.name() == "credits") {
                            qDebug()<<"completions8";
                            xml.readNext(); credits=xml.text().toString().toUInt();
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


                                xml.readNext();
                            }
                            DossierManager& dm=DossierManager::getInstance();
                            d=dm.trouverDossier(numDossier);

                            //ajouterCompletionDossier(id, annee,saison, d, credits, nbUVs);
                            Semestre s(saison, annee);

                            c=new ChoixAppliSemestre(id, d, s, credits, nbUVs, parent);

                            //cree une completion simple et gere les uvs dans la suite
                        }//fin if pour uv

                    }
                    xml.readNext();
                }
                qDebug()<<listUV;

                //Dossier * d=trouverDossier(numDossier);

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

         stream.writeStartElement("semestre");
         Semestre s=choix->getSemestre();

         Saison saison=s.getSaison() ;
         QString annee=QString::number(s.getAnnee());
         QString saisonString= SaisonToString(saison);
         stream.writeTextElement("saison",saisonString);
         stream.writeTextElement("annee",annee);
         QString credits=QString::number(choix->getNbCredits());
         stream.writeTextElement("credits",credits);
         qDebug()<<"point4";


         //ecriture des UV


         for(QMap<QString,UV*>::iterator it=choix->getQmapIteratorUVbegin();it!=choix->getQmapIteratorUVend(); it++)
         {
             stream.writeTextElement("uv",it.key());
             //ecriture du resultat correspondant
         }

         stream.writeEndElement();

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


