#ifndef CURSUS_H
#define CURSUS_H

#include <iostream>
#include <QString>
#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QComboBox>
#include <QDebug>
#include <QStringList>
#include <QMap>

class UV;
class UVManager;
class visiteur;

class abstract_cursus_item
{
    friend class cursusManager;
protected:
    QString nom;
    unsigned int nbCredits;
    QMap<QString,UV*> uvs;

    abstract_cursus_item(const QString& n, unsigned int c): nom(n), nbCredits(c) {}
    virtual ~abstract_cursus_item() {}

public:
    void ajouter_UV(UV*);
    virtual void supprimer_UV(const QString& code);
    QString getNom() const {return nom;}
    unsigned int getNbCred() const {return nbCredits;}
    const QMap<QString,UV*>::const_iterator trouverUV(const QString& code);
    QMap<QString,UV*>::iterator getQmapIteratorUVbegin() {return uvs.begin();}
    QMap<QString,UV*>::iterator getQmapIteratorUVend() {return uvs.end();}
};

class filiere : public abstract_cursus_item
{
    friend class cursusManager;

    filiere(const QString& n, unsigned int c) : abstract_cursus_item(n,c) {}
    ~filiere() {}

public:
    void supprimer_UV(const QString &code);
};

class formation : public abstract_cursus_item
{
    friend class cursusManager;

    unsigned int nbSemestres; //Le nombre de semestres (théoriques) de la formation
    QSet<QString> filieresAssoc;// liste des filières associées à cett formation.
    formation(const QString& n, unsigned int c, unsigned int s): abstract_cursus_item(n,c), nbSemestres(s) {}
    ~formation() {}

public:
    void supprimer_UV(const QString &code);
    unsigned int getNbSem() const {return nbSemestres;}
};

class cursusManager // gestionnaire des cursus
{
    QMap<QString,formation*> formations;
    QMap<QString,filiere*> filieres;

public:
    cursusManager() {this->chargerCursus();}
    ~cursusManager() {qDebug()<<"Destruction cursusManager";}

    friend struct Handler;
    struct Handler{
        cursusManager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; instance=0; }
    };
    static Handler handler;

    formation* trouverForm(const QString &n) {return formations.find(n).value();}
    filiere* trouverFil(const QString& n) {return filieres.find(n).value();}
    void ajouterFiliere(const QString& nom, unsigned int c);
    void chargerCursus();
    void ajouterFormation(const QString& nom, unsigned int c, unsigned int s);
    void supprimerFormation(const QString& nom);
    void supprimerFiliere(const QString& nom);
    void modifFiliere(const QString& oldkey, const QString& newname, unsigned int c);
    void modifFormation(const QString& oldkey, const QString& newname, unsigned int c, unsigned int s);
    void sauverCursus(QWidget* parent);
    void accept(visiteur* v, QString type);
    void inscrFilForm(formation* form, const QString& fil);
    void supprFilForm(formation* form, const QString& fil);
    bool trouverFilForm(formation* form, const QString& fil);

    QMap<QString,formation*>::iterator getQmapIteratorFormbegin() {return formations.begin();}
    QMap<QString,formation*>::iterator getQmapIteratorFormend() {return formations.end();}
    QMap<QString,filiere*>::iterator getQmapIteratorFilBegin() {return filieres.begin();}
    QMap<QString,filiere*>::iterator getQmapIteratorFilEnd() {return filieres.end();}

    static cursusManager& getInstance();
    static void libererInstance();

    /*class iterateur<formation>;
    iterateur<formation>& getIterateurForm();*/
};

#endif // CURSUS_H
