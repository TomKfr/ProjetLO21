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
    QStringList list;
    QMap<QString,UV*> listuvs;
    int taille;

public:
    visiteur(const QString& n, const QStringList& l): nom(n), list(l), taille(list.length()) {}
    void visitUVmanager();
    void visitCursusManager(cursusManager* cman, QString c);
};


#endif // VISITEUR_H
