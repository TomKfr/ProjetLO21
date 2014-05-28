#include"dossier.h"
#include"dossierGUI2.h"
#include"UTProfiler.h"
#include "visiteur2.h"
#include <sstream>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>
#include <QFileDialog>



void DossierManager::load(/*const QString& fichier*/)
{
    file=QDir::currentPath()+"/dossiers.xml";
    qDebug()<<"Chargement Dossiers!";
    QFile f(file);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {throw UTProfilerException("Erreur ouverture fichier cursus");}
    QXmlStreamReader xml(&f);
    while(!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartDocument) continue;
        if(token == QXmlStreamReader::StartElement) {
            if(xml.name() == "dossiers") continue;
            if(xml.name() == "dossier") {
                unsigned int numero;
                QString nom;
                QString prenom;
                QString formation;
                unsigned int numSemestre;
                QStringList listUV;
                QStringList listResult;

                //pour les equivalences :

                unsigned int credits= 6;
                QString description="lala";//valeur pour test du update : fonctionne
                QString type="Semestre" ;
                unsigned int nb=0;
                Equivalences ** tab=new Equivalences*[5];
                for (unsigned int j=0; j<5; j++) tab[j]=0;


                xml.readNext();
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "dossier")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        if(xml.name() == "numero") {
                            xml.readNext(); numero=xml.text().toString().toUInt();
                        }
                        if(xml.name() == "nom") {
                            xml.readNext(); nom=xml.text().toString();
                        }
                        if(xml.name() == "prenom") {
                            xml.readNext(); prenom=xml.text().toString();
                        }
                        if(xml.name() == "formation") {
                            xml.readNext(); formation=xml.text().toString();
                        }
                        if(xml.name() == "semestre") {
                            xml.readNext(); numSemestre=xml.text().toUInt();
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

                                if(xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="result")
                                {
                                    xml.readNext();
                                    listResult<<xml.text().toString();
                                }

                                xml.readNext();
                            }

                            ajouterDossier(numero,nom, prenom, formation, numSemestre);
                        }//fin if pour uv



                        qDebug()<<listUV;
                        qDebug()<<listResult;
                        if(!listUV.empty())
                        {
                            visiteur2* v=new visiteur2(numero,listUV,listResult);
                            v->visitUVmanager();
                            qDebug()<<"visit uv manager : done";
                            this->accept(v);
                            qDebug()<<"accept : done";
                        }


    /*                    if(xml.name() == "equivalences") {
                            qDebug()<<"j'ai repere une equivalence mec";
                            xml.readNext();

                            while(!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="equivalences"))
                               { //xml.readNext();
                                qDebug()<<xml.name();//OK affiche bien une seule fois

                                 if(xml.name() == "equivalence") {
                                     xml.readNext();

                                while(!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="equivalence"))
                                   {
                                     qDebug()<<"une equivalence";
                                     //xml.readNext();
                                     //qDebug()<<xml.name();
                                     if(xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="type")
                                     {
                                        xml.readNext(); type=xml.text().toString();
                                        qDebug()<<xml.name();
                                     }

                                     if(xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="credits")
                                     {
                                        xml.readNext(); credits=xml.text().toString().toInt();
                                        qDebug()<<xml.name();
                                     }

                                     if(xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="description")
                                     {
                                        xml.readNext(); description=xml.text().toString();
                                        qDebug()<<xml.name();
                                     }


                                    tab[nb]=new Equivalences(type, credits, description);
                                    nb++;
                                    qDebug()<<"remplissage du tablo  :type : "<<type;

                            }}

                        }}*/

                    }
                    xml.readNext();
                }

                Dossier* d=trouverDossier(numero);
                qDebug()<<"dans le load : nb equi"<<nb;
                /*d->setNbEquivalences(nb);
                d->setEquivalences(tab);
                tab=d->getEquivalences();
                qDebug()<<tab[0]->getDescription();*/


                //ON FAIT LES TYPES SIMPLES A CE NIVEAU
                //PUIS ON GERE LES LISTES

            }
        }
    }
    if(xml.hasError()) {
        throw UTProfilerException("Erreur lecteur fichier dossier, parser xml");
    }
    xml.clear();
    qDebug()<<"Chargement Dossiers termine!";
}

void DossierManager::save(){

    qDebug() << "Save Dossier";
    file=QDir::currentPath()+"/dossiers.xml";
    QFile newfile(file);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text)) throw UTProfilerException(QString("erreur ouverture fichier xml"));
    qDebug()<<"point1";
     QXmlStreamWriter stream(&newfile);
     stream.setAutoFormatting(true);
     stream.writeStartDocument();
     stream.writeStartElement("dossiers");
     qDebug()<<"point2";
     for(unsigned int i=0; i<nbDos; i++){
         stream.writeStartElement("dossier");
         /*stream.writeAttribute("automne", (uvs[i]->ouvertureAutomne())?"true":"false");
         stream.writeAttribute("printemps", (uvs[i]->ouverturePrintemps())?"true":"false");*/
         QString n; n.setNum(tabDossiers[i]->getNumero());
         qDebug()<<"point3";
         //QString n2; n2.setNum(tabDossiers[i]->getNumSemestre());
         stream.writeTextElement("numero",n);
         stream.writeTextElement("nom",tabDossiers[i]->getNom());
         stream.writeTextElement("prenom",tabDossiers[i]->getPrenom());
         stream.writeTextElement("formation",tabDossiers[i]->getFormation());
         qDebug()<<"point4";
         stream.writeTextElement("semestre",QString::number(tabDossiers[i]->getNumSemestre()));
         qDebug()<<"point5";

         //ecriture des UV

         QString * listeRes=tabDossiers[i]->getlisteResultats();
         qDebug()<<"point6";
         unsigned int j=0;
         //qDebug()<<listeRes[0];
         qDebug()<<"point7";
         stream.writeStartElement("uvs");
         for(QMap<QString,UV*>::iterator it=tabDossiers[i]->getQmapIteratorUVbegin();it!=tabDossiers[i]->getQmapIteratorUVend(); it++)
         {
             stream.writeTextElement("uv",it.key());
             //ecriture du resultat correspondant
             stream.writeTextElement("result",listeRes[j]);
             j++;
         }

         stream.writeEndElement();

         /*for(iterateur<UV>& it=tabDossiers[i]->getIterateurUV(); !it.isDone(); it.next())
         {
             qDebug()<<"ecriture de l'uv: "<<it.courant()->getCode(); //CHAINE VIDE
             stream.writeTextElement("uv",it.courant()->getCode());
             //ecriture du resultat correspondant
             stream.writeTextElement("result",listeRes[j]);
             j++;

         }*/

         //ecriture des equivalences
         /*
         qDebug()<<"dans le save avant les equivalences";
         i=0;
         Equivalences** tab=tabDossiers[i]->getEquivalences();

         qDebug()<<"1";

         stream.writeStartElement("equivalences");

         qDebug()<<"avant while";
         qDebug()<<tab[i];

         while (tab[i]!=0) {
         stream.writeStartElement("equivalence");
         stream.writeTextElement("type", tab[i]->getType());
          qDebug()<<"2";
         QString n; n.setNum(tab[i]->getNbCredits());
         stream.writeTextElement("credits", n);
         stream.writeTextElement("description", tab[i]->getDescription());
          qDebug()<<"2";

         stream.writeEndElement();
         stream.writeEndElement();
         i++;

         }

          qDebug()<<"3";

          qDebug()<<"4";*/
     }
     stream.writeEndElement();
     stream.writeEndDocument();

     newfile.close();
}
