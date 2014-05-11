#ifndef DOSSIER_H
#define DOSSIER_H

#include <iostream>
#include "UTProfiler.h"
#include "cursusGUI.h"
#include <QString>
#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QComboBox>
#include <QDebug>

//Ceci est la dernière version !

class Dossier {

    unsigned int numero;
    QString nom;
    QString prenom;
    QString F;
    UV** listeUV;

public :

    Dossier(unsigned int num, const QString& n, const QString& p, const QString& f, UV** liste=0);
    unsigned int getNumero() const {return numero;}
    const QString& getNom() const {return nom;}
    const QString& getPrenom() const {return prenom;}
    const QString& getFormation() const {return F;}
    UV** getlisteUV() const {return listeUV;}
    void setNumero(unsigned int n) { numero=n; }
    void setNom(const QString& n) { nom=n; }
    void setPrenom(const QString& n) { prenom=n; }
    void setFormation(const QString& f) { F=f; }
    void setListeUV(UV** l) { listeUV=l; }
    void ajouterUV(UV* nouv);

};


class DossierManager {
    Dossier** tabDossiers;
    unsigned int nbDos;
    unsigned int nbMaxDos;
    QString file;
    DossierManager():tabDossiers(0), nbDos(0), nbMaxDos(0) {}
    ~DossierManager();
    void operator=(const DossierManager&);
    DossierManager(const DossierManager&);
    friend struct Handler;
    struct Handler{
        DossierManager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; instance=0; }
    };
    static Handler handler;


public:
    void load(const QString& f);
    void save(const QString& f);
    unsigned int getnbDos() const {return nbDos;}
    unsigned int getnbMaxDos() const {return nbMaxDos;}
    Dossier* trouverDossier(unsigned int n) const;

    void ajouterDossier(unsigned int num, const QString& n, const QString& p, const QString& f, UV** tab);

    void addItem(Dossier* dos);
    void supprimerDossier(unsigned int n);
    static DossierManager& getInstance();
    static void libererInstance();

    class iterateur<Dossier>;
    iterateur<Dossier>& getIterateurForm();

};

#endif // DOSSIER_H
