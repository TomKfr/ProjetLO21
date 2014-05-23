#include"cursus.h"
#include"visiteur.h"
#include"UTProfiler.h"
#include<QDebug>
#include <QMessageBox>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFileDialog>
#include <QDir>
#include <QStringList>
#include<QMap>

cursusManager::Handler cursusManager::handler=Handler();

class visiteur;

// ///////////////////////////////////////////////////////////////////
void abstract_cursus_item::ajouter_UV(UV *newuv) {uvs.insert(newuv->getCode(),newuv);}
void abstract_cursus_item::supprimer_UV(const QString &code)
{
    if(QMessageBox::information(0,"Retrait d'une UV","Voulez vous retirer l'UV "+code+" ?",QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Ok)
    {
        uvs.remove(code);
    }
}
const QMap<QString,UV*>::const_iterator abstract_cursus_item::trouverUV(const QString &code){return uvs.constFind(code);}
// ///////////////////////////////////////////////////////////////////

void formation::supprimer_UV(const QString& code)
{
    if(QMessageBox::information(0,"Retrait d'une UV","Voulez vous retirer l'UV "+code+" de la formation "+nom+" ?",QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Ok)
    {
        uvs.remove(code);
    }
}

// ///////////////////////////////////////////////////////////////////

void filiere::supprimer_UV(const QString &code)
{
    if(QMessageBox::information(0,"Retrait d'une UV","Voulez vous retirer l'UV "+code+" de la filiere "+nom+" ?",QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Ok)
    {
        uvs.remove(code);
    }
}

// ///////////////////////////////////////////////////////////////////



cursusManager& cursusManager::getInstance() {
    if (!handler.instance) handler.instance = new cursusManager; /* instance cr��e une seule fois lors de la premi�re utilisation*/
    return *handler.instance;
}

void cursusManager::libererInstance() {
    if (handler.instance) { delete handler.instance; handler.instance=0; }
}

void cursusManager::ajouterFormation(const QString& nom, unsigned int c, unsigned int s)
{
    if (formations.find(nom)!=formations.end())
    {
        throw UTProfilerException(QString("erreur, cursusManager, formation ")+nom+QString(" déja existante"));
    }
    else
    {
        formations.insert(nom,new formation(nom,c,s));
    }
}

void cursusManager::ajouterFiliere(const QString &nom, unsigned int c)
{
    if(filieres.find(nom)!=filieres.end())
    {
        throw UTProfilerException(QString("erreur, cursusManager, filière ")+nom+QString(" déja existante"));
    }
    else
    {
        filieres.insert(nom,new filiere(nom,c));
    }
}

void cursusManager::supprimerFormation(const QString &nom)
{
    formations.erase(formations.find(nom));
}
void cursusManager::supprimerFiliere(const QString &nom)
{
    filieres.erase(filieres.find(nom));
}

void cursusManager::modifFiliere(const QString &oldkey, const QString &newname, unsigned int c)
{
    if(filieres.find(newname)!=filieres.end()) throw UTProfilerException(QString("erreur, cursusManager, filière ")+newname+QString(" déja existante"));
    else
    {
        QMap<QString,UV*>* list=new QMap<QString,UV*>(trouverFil(oldkey)->uvs);
        supprimerFiliere(oldkey);
        ajouterFiliere(newname,c);
        filiere* newfil=trouverFil(newname);
        newfil->uvs=*list;
        delete list;
    }
}
void cursusManager::modifFormation(const QString &oldkey, const QString &newname, unsigned int c, unsigned int s)
{
    if (formations.find(newname)!=formations.end()) throw UTProfilerException(QString("erreur, cursusManager, formation ")+newname+QString(" déja existante"));
    else
    {
        QMap<QString,UV*>* list=new QMap<QString,UV*>(trouverForm(oldkey)->uvs);
        QSet<QString>* list2=new QSet<QString>(trouverForm(oldkey)->filieresAssoc);
        supprimerFormation(oldkey);
        ajouterFormation(newname,c,s);
        formation* newform=trouverForm(newname);
        newform->uvs=*list;
        delete list;
        newform->filieresAssoc=*list2;
        delete list2;
    }
}

void cursusManager::inscrFilForm(formation *form, const QString &fil)
{
    form->filieresAssoc.insert(fil);
}
void cursusManager::supprFilForm(formation *form, const QString &fil)
{
    form->filieresAssoc.remove(fil);
}
bool cursusManager::trouverFilForm(formation *form, const QString &fil)
{
    return form->filieresAssoc.contains(fil);
}

void cursusManager::sauverCursus(QWidget *parent)
{
    QString fileOut = QDir::currentPath()+ "/formations.xml";
    qDebug()<<"Sauvegarde dans le fichier "<<fileOut;

    if(!fileOut.isEmpty())
    {
        QFile f(fileOut);
        if(!f.open(QIODevice::WriteOnly | QIODevice::Text)) throw UTProfilerException("Erreur ouverture fichier xml!");
        QXmlStreamWriter stream(&f);
        stream.setAutoFormatting(true);
        stream.writeStartDocument();
        stream.writeStartElement("formations");
        for(QMap<QString,formation*>::iterator form=formations.begin();form!=formations.end();form++)
        {
            stream.writeStartElement("formation");
            stream.writeTextElement("nom",form.key());
            QString cr; cr.setNum(form.value()->getNbCred());
            stream.writeTextElement("nbcred",cr);
            cr.setNum(form.value()->getNbSem());
            stream.writeTextElement("nbsem", cr);
            stream.writeStartElement("uvs");
            for(QMap<QString,UV*>::iterator it=form.value()->getQmapIteratorUVbegin();it!=form.value()->getQmapIteratorUVend(); it++)
            {
                stream.writeTextElement("uv",it.key());
            }
            stream.writeEndElement();
            stream.writeStartElement("filieres");
            for(QSet<QString>::iterator it=form.value()->filieresAssoc.begin();it!=form.value()->filieresAssoc.end();it++)
            {
                stream.writeTextElement("filiere",*it);
            }
            stream.writeEndElement();
            stream.writeEndElement();
        }
        stream.writeEndElement();
        stream.writeEndDocument();
        f.close();
    }

    // ////////////////// Ecriture des filieres
    fileOut = QDir::currentPath()+ "/filieres.xml";
    qDebug()<<"Sauvegarde dans le fichier "<<fileOut;

    if(!fileOut.isEmpty())
    {
        QFile f(fileOut);
        if(!f.open(QIODevice::WriteOnly | QIODevice::Text)) throw UTProfilerException("Erreur ouverture fichier xml!");
        QXmlStreamWriter stream(&f);
        stream.setAutoFormatting(true);
        stream.writeStartDocument();
        stream.writeStartElement("filieres");
        for(QMap<QString,filiere*>::iterator fil=filieres.begin();fil!=filieres.end();fil++)
        {
            stream.writeStartElement("filiere");
            stream.writeTextElement("nom",fil.key());
            QString cr; cr.setNum(fil.value()->getNbCred());
            stream.writeTextElement("nbcred",cr);
            stream.writeStartElement("uvs");
            for(QMap<QString,UV*>::iterator it=fil.value()->getQmapIteratorUVbegin();it!=fil.value()->getQmapIteratorUVend(); it++)
            {
                stream.writeTextElement("uv",it.key());
            }
            stream.writeEndElement();
            stream.writeEndElement();
        }
        stream.writeEndElement();
        stream.writeEndDocument();
        f.close();
    }
    QMessageBox::information(parent,"Sauvegarde","Cursus sauvegardés", QMessageBox::Ok);
}

void cursusManager::chargerCursus()
{
    // nécessaire de lire les filières d'abord pour pouvoir ajouter les formations !
    QString fileOut = QDir::currentPath()+ "/filieres.xml";
    qDebug()<<"Ouverture du fichier "<<fileOut;
    QFile f(fileOut);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {throw UTProfilerException("Erreur ouverture fichier filieres");}
    QXmlStreamReader xml(&f);
    while(!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartDocument) continue;
        if(token == QXmlStreamReader::StartElement) {
            if(xml.name() == "filieres") continue;
            if(xml.name() == "filiere") {
                QString nom;
                unsigned int nbCredits;
                QStringList list;

                xml.readNext();
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "filiere")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        if(xml.name() == "nom") {
                            xml.readNext(); nom=xml.text().toString();
                        }
                        if(xml.name() == "nbcred") {
                            xml.readNext(); nbCredits=xml.text().toUInt();
                        }
                        if(xml.name() == "uvs")
                        {
                            xml.readNext();
                            while(!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="uvs"))
                            {
                                if(xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="uv")
                                {
                                    xml.readNext();
                                    list<<xml.text().toString();
                                }
                                xml.readNext();
                            }
                        }
                    }
                    xml.readNext();
                }
                ajouterFiliere(nom,nbCredits);
                if(!list.empty())
                {
                    visiteur* v=new visiteur(nom,list);
                    v->visitUVmanager();
                    this->accept(v,"fil");
                }
            }
        }
    }
    if(xml.hasError()) {
        throw UTProfilerException("Erreur lecteur fichier filieres, parser xml");
    }
    xml.clear();
    // /////////////////////// lectures des formations
    fileOut = QDir::currentPath()+ "/formations.xml";
    qDebug()<<"Ouverture du fichier "<<fileOut;
    f.setFileName(fileOut);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {throw UTProfilerException("Erreur ouverture fichier cursus");}
    xml.setDevice(&f);
    while(!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartDocument) continue;
        if(token == QXmlStreamReader::StartElement) {
            if(xml.name() == "formations") continue;
            if(xml.name() == "formation") {
                QString nom;
                unsigned int nbCredits;
                unsigned int nbSem;
                QStringList list;
                QStringList list2;

                xml.readNext();
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "formation")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        if(xml.name() == "nom") {
                            xml.readNext(); nom=xml.text().toString();
                        }
                        if(xml.name() == "nbcred") {
                            xml.readNext(); nbCredits=xml.text().toUInt();
                        }
                        if(xml.name() == "nbsem") {
                            xml.readNext(); nbSem=xml.text().toUInt();
                        }
                        if(xml.name() == "uvs")
                        {
                            xml.readNext();
                            while(!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="uvs"))
                            {
                                if(xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="uv")
                                {
                                    xml.readNext();
                                    list<<xml.text().toString();
                                }
                                xml.readNext();
                            }
                        }
                        if(xml.name() == "filieres")
                        {
                            xml.readNext();
                            while(!(xml.tokenType()==QXmlStreamReader::EndElement && xml.name()=="filieres"))
                            {
                                if(xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="filiere")
                                {
                                    xml.readNext();
                                    list2<<xml.text().toString();
                                }
                                xml.readNext();
                            }
                        }
                    }
                    xml.readNext();
                }
                ajouterFormation(nom,nbCredits,nbSem);
                if(!list.empty())
                {
                    visiteur* v=new visiteur(nom,list);
                    v->visitUVmanager();
                    this->accept(v,"form");
                }
                formation* newform=trouverForm(nom);
                int taille=list2.size();
                for(int x=0;x<taille;x++)
                {
                    inscrFilForm(newform,list2.first());
                    list2.removeFirst();
                }
            }
        }
    }
    if(xml.hasError()) {
        throw UTProfilerException("Erreur lecteur fichier formations, parser xml");
    }
    xml.clear();
}

/*iterateur<formation>& cursusManager::getIterateurForm()
{
    iterateur<formation>* it=new iterateur<formation>(formations,nbFor);
    return *it;
}*/

void cursusManager::accept(visiteur *v,QString type){v->visitCursusManager(this,type);}

