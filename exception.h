/// \file exception.h
/// \brief Fichier contenant la déclaration de la classe permeattant de gérer les exceptions dans l'application.

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QString>

/*!
 * \brief Classe de d'objets exception.
 *
 * Cette classe permet de gérer les éxception rencontrées lors de l'exécution.
 */
class UTProfilerException{
public:
    UTProfilerException(const QString& message, const QString &f="na", unsigned int l=0):
        info(message),file(f),line(l){}
    QString getInfo() const { return info; }
#ifndef NDEBUG
    // retourne le fichier dans lequel cettte exception a �t� lev�e.
    QString getFile() const { return file; }
    // retourne la ligne du fichier � laquelle cette exception a �t� lev�e.
    unsigned int getLine() const { return line; }
#endif
private:
    QString info;
    QString file;
    unsigned int line;

};

#endif // EXCEPTION_H
