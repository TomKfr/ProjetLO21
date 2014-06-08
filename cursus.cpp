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
UV* abstract_cursus_item::trouverUV(const QString &code)
{
    if(uvs.contains(code))
    {
        return uvs.find(code).value();
    }
    return 0;
}
/*const QMap<QString,UV*>::const_iterator abstract_cursus_item::trouverUV(const QString &code)
{
    return uvs.constFind(code);
}*/
// ///////////////////////////////////////////////////////////////////

void formation::supprimer_UV(const QString& code)
{
    if(QMessageBox::information(0,"Retrait d'une UV","Voulez vous retirer l'UV "+code+" de la formation "+nom+" ?",QMessageBox::Ok,QMessageBox::Cancel)==QMessageBox::Ok)
    {
        uvs.remove(code);
    }
}
unsigned int formation::getCrRequis(Categorie cat) const
{
    return credits_requis.find(cat).value();
}
void formation::setNbCrRequis(Categorie cat, unsigned int nb)
{
    credits_requis.insert(cat,nb);
}
void formation::ajt_UV_obligatoire(const QString &code)
{
    UVs_obligatoires.insert(code);
}
void formation::suppr_UV_obligatoire(const QString &code)
{
    UVs_obligatoires.remove(code);
}
bool formation::estObligatoire(const QString &code) const
{
    return UVs_obligatoires.contains(code);
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

formation* cursusManager::trouverForm(const QString &n)
{
    QMap<QString,formation*>::iterator it=formations.find(n);
    if(it==formations.end()) return 0;
    else return it.value();
}

cursusManager& cursusManager::getInstance() {
    if (!handler.instance) handler.instance = new cursusManager; /* instance cr��e une seule fois lors de la premi�re utilisation*/
    return *handler.instance;
}

void cursusManager::libererInstance() {
    if (handler.instance) { delete handler.instance; handler.instance=0; }
}

formation* cursusManager::ajouterFormation(const QString& nom, unsigned int c, unsigned int s, unsigned int ccs, unsigned int ctm, unsigned int ctsh, unsigned int csp)
{
    try{
        if (formations.find(nom)!=formations.end())
        {
            throw UTProfilerException(QString("erreur, cursusManager, formation ")+nom+QString(" déja existante"));
        }
        else
        {
            formation* newform=new formation(nom,c,s);
            newform->setNbCrRequis(CS,ccs);
            newform->setNbCrRequis(TM,ctm);
            newform->setNbCrRequis(TSH,ctsh);
            newform->setNbCrRequis(SP,csp);
            formations.insert(nom,newform);
            return newform;
        }
    }
    catch(UTProfilerException& e){QMessageBox::warning(0,"Erreur",e.getInfo());}
    return 0;
}

void cursusManager::ajouterFiliere(const QString &nom, unsigned int c)
{
    try{
        if(filieres.find(nom)!=filieres.end())
        {
            throw UTProfilerException(QString("erreur, cursusManager, filière ")+nom+QString(" déja existante"));
        }
        else
        {
            filieres.insert(nom,new filiere(nom,c));
        }
    }
    catch(UTProfilerException& e){QMessageBox::warning(0,"Erreur",e.getInfo());}
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
    try{
        if(filieres.find(newname)!=filieres.end() && newname!=oldkey) throw UTProfilerException(QString("erreur, cursusManager, filière ")+newname+QString(" déja existante"));
        else
        {
            QMap<QString,UV*>* list=new QMap<QString,UV*>(trouverFil(oldkey)->uvs);
            supprimerFiliere(oldkey);
            ajouterFiliere(newname,c);
            filiere* newfil=trouverFil(newname);
            newfil->uvs=*list;
            delete list;
        }
        for(QMap<QString,formation*>::iterator it=getQmapIteratorFormbegin();it!=getQmapIteratorFormend();it++)
        {
            if(trouverFilForm(it.value(),oldkey))
            {
                it.value()->filieresAssoc.remove(oldkey);
                it.value()->filieresAssoc.insert(newname);
            }
        }
    }
    catch(UTProfilerException& e){QMessageBox::warning(0,"Erreur",e.getInfo());}
}
void cursusManager::modifFormation(const QString &oldkey, const QString &newname, unsigned int c, unsigned int s, unsigned int ccs, unsigned int ctm, unsigned int ctsh, unsigned int csp)
{
    try{
        if (formations.find(newname)!=formations.end() && newname!=oldkey) throw UTProfilerException(QString("erreur, cursusManager, formation ")+newname+QString(" déja existante"));
        else
        {
            QMap<QString,UV*>* list=new QMap<QString,UV*>(trouverForm(oldkey)->uvs);
            QSet<QString>* list2=new QSet<QString>(trouverForm(oldkey)->filieresAssoc);
            QSet<QString>* list3=new QSet<QString>(trouverForm(oldkey)->UVs_obligatoires);
            supprimerFormation(oldkey);
            ajouterFormation(newname,c,s,ccs,ctm,ctsh, csp);
            formation* newform=trouverForm(newname);
            newform->uvs=*list;
            delete list;
            newform->filieresAssoc=*list2;
            delete list2;
            newform->UVs_obligatoires=*list3;
            delete list3;
        }
    }
    catch(UTProfilerException& e) {QMessageBox::warning(0,"erreur",e.getInfo());}
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

void cursusManager::sauverCursus()
{
    QString fileOut = QDir::currentPath()+ "/formations.xml";
    qDebug()<<"Sauvegarde dans le fichier "<<fileOut;
try{
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
                stream.writeTextElement("obligatoire",form.value()->estObligatoire(it.key())?"true":"false");
            }
            stream.writeEndElement();
            stream.writeStartElement("filieres");
            for(QSet<QString>::iterator it=form.value()->filieresAssoc.begin();it!=form.value()->filieresAssoc.end();it++)
            {
                stream.writeTextElement("filiere",*it);
            }
            stream.writeEndElement();
            stream.writeStartElement("creditsrequis");
            for(QMap<Categorie,unsigned int>::iterator it=form.value()->getCrRequisBegin();it!=form.value()->getCrRequisEnd();it++)
            {
                stream.writeTextElement(CategorieToString(it.key()),QString::number(it.value()));
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
    QMessageBox::information(0,"Sauvegarde","Cursus sauvegardés", QMessageBox::Ok);
    }
    catch(UTProfilerException& e){QMessageBox::warning(0,"Erreur",e.getInfo());}
}

void cursusManager::chargerCursus()
{
    // nécessaire de lire les filières d'abord pour pouvoir ajouter les formations !
    QString fileOut = QDir::currentPath()+ "/filieres.xml";
    qDebug()<<"Ouverture du fichier "<<fileOut;
    try{
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
                QMap<QString,bool> list;

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
                                    list.insert(xml.text().toString(),false);
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
                QStringList list2;
                QString code;
                bool required;
                QMap<QString,bool> listUVs;
                QString cat;
                int nb;
                QMap<QString,int> creditsrequis;

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
                                    code=xml.text().toString();
                                    xml.readNext();
                                    xml.readNext();
                                    xml.readNext();
                                    xml.readNext();
                                    if(xml.text()=="true") required=true;
                                    else required=false;

                                    listUVs.insert(code,required);
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
                        if(xml.name() == "creditsrequis") {
                            xml.readNext();
                            xml.readNext();
                            cat=xml.name().toString();
                            xml.readNext();
                            nb=xml.text().toInt();
                            creditsrequis.insert(cat,nb);
                            xml.readNext();
                            xml.readNext();
                            xml.readNext();
                            cat=xml.name().toString();
                            xml.readNext();
                            nb=xml.text().toInt();
                            creditsrequis.insert(cat,nb);
                            xml.readNext();
                            xml.readNext();
                            xml.readNext();
                            cat=xml.name().toString();
                            xml.readNext();
                            nb=xml.text().toInt();
                            creditsrequis.insert(cat,nb);
                            xml.readNext();
                            xml.readNext();
                        }
                    }
                    xml.readNext();
                }
                ajouterFormation(nom,nbCredits,nbSem,0,0,0, 0);
                if(!listUVs.empty())
                {
                    visiteur* v=new visiteur(nom,listUVs);
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
                for(QMap<QString,int>::iterator it=creditsrequis.begin();it!=creditsrequis.end();it++)
                {
                    newform->credits_requis.insert(StringToCategorie(it.key()),it.value());
                }
            }
        }
    }
    if(xml.hasError()) {
        throw UTProfilerException("Erreur lecteur fichier formations, parser xml");
    }
    xml.clear();
    }
    catch(UTProfilerException& e){QMessageBox::warning(0,"Erreur",e.getInfo());}
}

/*iterateur<formation>& cursusManager::getIterateurForm()
{
    iterateur<formation>* it=new iterateur<formation>(formations,nbFor);
    return *it;
}*/

void cursusManager::accept(visiteur *v,QString type){v->visitCursusManager(this,type);}

