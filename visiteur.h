/*!
 *  \file visiteur.h
 *  \brief Fichier contenant la déclaration du premier visiteur.
 */

#ifndef VISITEUR_H
#define VISITEUR_H

#include <QString>
#include <QStringList>
#include <QMap>

class formation;
class UV;
class UVManager;
class cursusManager;

/*!
 * \brief Classe implémentant le design pattern visiteur.
 *
 * Un objet visiteur est capable de visiter les classes
 * UVManager et cursusManager afin d'inscrire une liste
 * d'UVs et une liste de filières dans une formation,
 * à partir de n'importe quelle classe.
 */
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
