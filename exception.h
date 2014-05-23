#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QString>

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
