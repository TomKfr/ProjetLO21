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



/*!
 * \brief Récupère les dossiers sauvegardés dans le fichiers dossiers.xml et les charge en mémoire.
 */
void DossierManager::load()
{
    try{
    file=QDir::currentPath()+"/dossiers.xml";
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
                QString filiere;
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

                //pour les souhaits

                QSet<QString> exigees;
                QSet<QString> preferees;
                QSet<QString> rejetees;

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
                        if(xml.name() == "filiere") {
                            xml.readNext(); filiere=xml.text().toString();
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

                            ajouterDossier(numero,nom, prenom, formation, filiere, numSemestre);
                        }//fin if pour uv

                        if(xml.name() == "equivalences")
                        {
                            while(!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="equivalences"))
                            {
                                if(xml.name() == "equivalence") {
                                    xml.readNext();
                                    while(!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="equivalence"))
                                    {
                                        if(xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="type")
                                        {
                                            xml.readNext();
                                            type=xml.text().toString();
                                        }

                                        if(xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="credits")
                                        {
                                            xml.readNext();
                                            credits=xml.text().toUInt();
                                        }

                                        if(xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="description")
                                        {
                                            xml.readNext();
                                            description=xml.text().toString();
                                        }
                                        xml.readNext();
                                    }
                                    tab[nb]=new Equivalences(type, credits, description);
                                    nb++;
                                }
                                xml.readNext();
                            }
                        }

                        if(xml.name()=="souhaits")
                        {
                            qDebug()<<"Chargement souhaits";
                            while(!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="souhaits"))
                            {
                                if(xml.name()=="exigees")
                                {
                                    xml.readNext();
                                    while(!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="exigees"))
                                    {
                                        if(xml.name()=="uv")
                                        {
                                            xml.readNext();
                                            exigees.insert(xml.text().toString());
                                            xml.readNext();
                                        }
                                        xml.readNext();
                                    }
                                }

                                if(xml.name()=="preferees")
                                {
                                    xml.readNext();
                                    while(!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="preferees"))
                                    {
                                        if(xml.name()=="uv")
                                        {
                                            xml.readNext();
                                            preferees.insert(xml.text().toString());
                                            xml.readNext();
                                        }
                                        xml.readNext();
                                    }
                                }

                                if(xml.name()=="rejetees")
                                {
                                    xml.readNext();
                                    while(!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="rejetees"))
                                    {
                                        if(xml.name()=="uv")
                                        {
                                            xml.readNext();
                                            rejetees.insert(xml.text().toString());
                                            xml.readNext();
                                        }
                                        xml.readNext();
                                    }
                                }

                                xml.readNext();
                            }
                        }

                    }
                    xml.readNext();
                }

                Dossier* d=trouverDossier(numero);
                if(!listUV.empty())
                {
                    visiteur2* v=new visiteur2(numero,listUV,listResult);
                    v->visitUVmanager();
                    this->accept(v);
                }
                d->setNbEquivalences(nb);
                d->setEquivalences(tab);
                tab=d->getEquivalences();

                souhaits* newsouhait=new souhaits(d,exigees,preferees,rejetees);
                d->setSouhaits(newsouhait);
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
 * \brief Sauvegarde les dossiers en mémoire dans le fichier dossiers.xml
 */
void DossierManager::save(){

    file=QDir::currentPath()+"/dossiers.xml";
    try{
    QFile newfile(file);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text)) throw UTProfilerException(QString("erreur ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("dossiers");

    for(unsigned int i=0; i<nbDos; i++){
        stream.writeStartElement("dossier");

        QString n; n.setNum(tabDossiers[i]->getNumero());

        stream.writeTextElement("numero",n);
        stream.writeTextElement("nom",tabDossiers[i]->getNom());
        stream.writeTextElement("prenom",tabDossiers[i]->getPrenom());
        stream.writeTextElement("formation",tabDossiers[i]->getFormation());
        stream.writeTextElement("filiere",tabDossiers[i]->getFiliere());
        stream.writeTextElement("semestre",QString::number(tabDossiers[i]->getNumSemestre()));

        //ecriture des UV

        unsigned int j=0;
        stream.writeStartElement("uvs");
        for(QMap<QString,Note>::iterator it=tabDossiers[i]->getQmapIteratorUVbegin();it!=tabDossiers[i]->getQmapIteratorUVend(); it++)
        {
            stream.writeTextElement("uv",it.key());
            //ecriture du resultat correspondant
            stream.writeTextElement("result", Note2String(it.value()));
            j++;
        }

        stream.writeEndElement();


        //ecriture des equivalences

        unsigned int k=0;
        Equivalences** tab=tabDossiers[i]->getEquivalences();

        stream.writeStartElement("equivalences");

        while (tab[k]!=0) {
            stream.writeStartElement("equivalence");
            stream.writeTextElement("type", tab[k]->getType());
            QString n; n.setNum(tab[k]->getNbCredits());
            stream.writeTextElement("credits", n);
            stream.writeTextElement("description", tab[k]->getDescription());

            stream.writeEndElement();
            k++;
        }
        stream.writeEndElement();

        stream.writeStartElement("souhaits");
        if(tabDossiers[i]->Souhaits!=0)
        {
            stream.writeTextElement("dossier",QString::number(tabDossiers[i]->getNumero()));
            stream.writeStartElement("exigees");
            for(QSet<QString>::iterator it=tabDossiers[i]->Souhaits->exigences.begin();it!=tabDossiers[i]->Souhaits->exigences.end();it++)
            {
                stream.writeTextElement("uv",*it);
            }
            stream.writeEndElement();
            stream.writeStartElement("preferees");
            for(QSet<QString>::iterator it=tabDossiers[i]->Souhaits->preferences.begin();it!=tabDossiers[i]->Souhaits->preferences.end();it++)
            {
                stream.writeTextElement("uv",*it);
            }
            stream.writeEndElement();
            stream.writeStartElement("rejetees");
            for(QSet<QString>::iterator it=tabDossiers[i]->Souhaits->rejets.begin();it!=tabDossiers[i]->Souhaits->rejets.end();it++)
            {
                stream.writeTextElement("uv",*it);
            }
            stream.writeEndElement();
        }
        stream.writeEndElement();

        stream.writeEndElement();
    }
    stream.writeEndElement();
    stream.writeEndDocument();

    newfile.close();
    }
    catch(UTProfilerException& e){QMessageBox::warning(0,"Erreur",e.getInfo());}
}
