#ifndef VISITEUR_H
#define VISITEUR_H

#include <QString>
#include <QStringList>
#include <QMap>

class formation;
class UV;
class UVManager;
class cursusManager;

class visiteur
{
    QString nom;
    QMap<QString,bool> list;
    QStringList listfil;
    QMap<QString,UV*> listuvs;
    int taille;

public:
    visiteur(const QString& n, const QMap<QString,bool>& l): nom(n), list(l), taille(list.count()) {}
    void visitUVmanager();
    void visitCursusManager(cursusManager* cman, QString c);
};


#endif // VISITEUR_H
