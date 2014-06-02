#include "completion.h"
#include "cursus.h"
#include "dossier.h"

#include <QXmlStreamWriter>
#include <QFile>
#include <QDir>

void souhaits::Ajt_exigence(const QString& code)
{
    exigences.insert(code);
}
void souhaits::Ajt_preference(const QString& code)
{
    preferences.insert(code);
}
void souhaits::Ajt_rejet(const QString& code)
{
    rejets.insert(code);
}
void souhaits::Suppr_exigence(const QString& code)
{
    exigences.remove(code);
}
void souhaits::Suppr_prefernce(const QString& code)
{
    preferences.remove(code);
}
void souhaits::Suppr_rejet(const QString& code)
{
    rejets.remove(code);
}

/*void souhaits::save() DEPLACE DANS LE SAVE DE DOSSIERS
{
    QString fileOut = QDir::currentPath()+ "/souhaits.xml";
    qDebug()<<"Sauvegarde dans le fichier "<<fileOut;
    if(!fileOut.isEmpty())
    {
        QFile f(fileOut);
        if(!f.open(QIODevice::WriteOnly | QIODevice::Text)) throw UTProfilerException("Erreur ouverture fichier xml!");
        QXmlStreamWriter stream(&f);
        stream.setAutoFormatting(true);
        stream.writeStartDocument();
        stream.writeStartElement("souhait");
        stream.writeTextElement("dossier",QString::number(dos->getNumero()0));
        stream.writeStartElement("exigees");
        for(QSet<QString>::iterator it=exigences.begin();it!=exigences.end();it++)
        {
            stream.writeTextElement("uv",*it);
        }
        stream.writeEndElement();
        stream.writeStartElement("preferees");
        for(QSet<QString>::iterator it=preferences.begin();it!=preferences.end();it++)
        {
            stream.writeTextElement("uv",*it);
        }
        stream.writeEndElement();
        stream.writeStartElement("rejetees");
        for(QSet<QString>::iterator it=rejets.begin();it!=rejets.end();it++)
        {
            stream.writeTextElement("uv",*it);
        }
        stream.writeEndElement();
        stream.writeEndElement();
        stream.writeEndDocument();
    }
}*/

void souhaits::load()
{

}

void ChoixAppliSemestre::ajoutUV(UV* uv) {propositionUV.insert(uv->getCode(),uv);}
void ChoixAppliSemestre::supprimerUV(UV* uv) {propositionUV.erase(propositionUV.find(uv->getCode()));}
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

ChoixAppliSemestre* ChoixAppli::trouverChoix(Semestre S) {
    qDebug()<<nbSemestre;

    for (unsigned int i=0; i<nbSemestre; i++) {if (listePropositions[i]->getSemestre()==S) return listePropositions[i]; }
    return 0;
}
