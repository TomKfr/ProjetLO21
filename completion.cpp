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

void souhaits::save()
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
        stream.writeTextElement("dossier",QString::number(/*dos->getNumero()*/0));
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
}
