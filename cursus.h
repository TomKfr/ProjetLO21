/// \file cursus.h
/// \brief Fichier contenant les déclarations de classes de l'architecture
/// concernant le cursus (formations, filières, manager ...)

#ifndef CURSUS_H
#define CURSUS_H

#include "UTProfiler.h"
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

class visiteur;

/**
 * @brief Superclasse dont héritent les classes formation et filière qui factorise les attributs et méthodes communs aux deux sous classes.
 */
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
    QMap<QString,UV*> getUVFormation() const {return uvs; }
    /**
     * @brief Fonction d'ajout d'une UV
     * @param newuv UV à ajouter
     */
    void ajouter_UV(UV* newuv);
    /**
     * @brief supprimer_UV
     * @param code Code de l'UV à supprimer
     */
    virtual void supprimer_UV(const QString& code);
    /**
     * @brief Permet de récupérer le nom de l'objet
     * @return Nom de l'objet (string)
     */
    QString getNom() const {return nom;}
    /**
     * @brief Permet de récupérer la valeur de l'attribut credits
     * @return Nombre de crédits
     */
    unsigned int getNbCred() const {return nbCredits;}
    /**
     * @brief Permet de retrouver une UV appartenant à l'objet
     * @param code Code de l'UV à retrouver
     * @return Pointeur sur l'UV recherchée si elle existe, 0 sinon.
     */
    UV *trouverUV(const QString& code);
    /**
     * @brief Permet de récupérer un itérateur pointant sur le début de la liste d'UVs
     * @return Itérateur pointant sur le début de la liste d'UVs
     */
    QMap<QString,UV*>::iterator getQmapIteratorUVbegin() {return uvs.begin();}
    /**
     * @brief Permet de récupérer un itérateur pointant sur la fin de la liste d'UVs
     * @return Itérateur pointant sur la fin de la liste d'UVs
     */
    QMap<QString,UV*>::iterator getQmapIteratorUVend() {return uvs.end();}
};

/**
 * @brief Classe qui hérite de abstract_cursus_item et qui y ajoute les attributs et méthodes spécifiques aux filières.
 */
class filiere : public abstract_cursus_item
{
    friend class cursusManager;

    filiere(const QString& n, unsigned int c) : abstract_cursus_item(n,c) {}
    ~filiere() {}

public:
    void supprimer_UV(const QString &code);
};

/**
 * @brief Classe qui hérite de abstract_cursus_item et qui y ajoute les attributs et méthodes spécifiques aux formations.
 */
class formation : public abstract_cursus_item
{
    friend class cursusManager;

    unsigned int nbSemestres; //Le nombre de semestres (théoriques) de la formation
    QSet<QString> filieresAssoc;// liste des filières associées à cett formation.
    QMap<Categorie,unsigned int> credits_requis;
    QSet<QString> UVs_obligatoires;
    formation(const QString& n, unsigned int c, unsigned int s): abstract_cursus_item(n,c), nbSemestres(s) {}
    ~formation() {}

public:
    void supprimer_UV(const QString &code);
    unsigned int getNbSem() const {return nbSemestres;}
    unsigned int getCrRequis(Categorie cat) const;
    QMap<Categorie,unsigned int> getMapCrRequis() const {return credits_requis; }
    /**
     * @brief Fixe le nombre de crédits requis pour valider la formation dans une certaine catégorie
     * @param cat Catégorie concernée
     * @param nb Nombre de crédits requis dans la catégorie cat pour valider la formation
     */
    void setNbCrRequis(Categorie cat, unsigned int nb);
    QMap<Categorie,unsigned int>::iterator getCrRequisBegin() {return credits_requis.begin();}
    QMap<Categorie,unsigned int>::iterator getCrRequisEnd() {return credits_requis.end();}
    QSet<QString>::iterator getFilBegin() {return filieresAssoc.begin();}
    QSet<QString>::iterator getFilEnd() {return filieresAssoc.end();}
    /**
     * @brief Ajoute une UV obligatoire dans la formation
     * @param code Code de l'UV à ajouter
     */
    void ajt_UV_obligatoire(const QString& code);
    /**
     * @brief Supprime une UV de la liste des UVs obligatoires de la formation
     * @param code Code de l'UV à supprimer
     */
    void suppr_UV_obligatoire(const QString& code);
    /**
     * @brief Vérifie si l'UV passée en paramètre est obligatoire dans la formation
     * @param code Code de l'UV
     * @return "true" si l'UV est obligatoire, "false" sinon.
     */
    bool estObligatoire(const QString& code) const;
    const QSet<QString> & getUVsObligatoires() const {return UVs_obligatoires;}
};

/**
 * @brief Singleton gestionnaire des objets \a formation et \a filiere.
 */
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
    /**
     * @brief Recherche une formation dans la liste des formations existantes.
     * @param n Nom de la formation à rechercher
     * @return Un pointeur vers la formation recherchée si elle existe, 0 sinon.
     */
    formation* trouverForm(const QString &n);
    /**
     * @brief Recherche une filière dans la liste des filières existantes.
     * @param n Nom de la filière à rechercher
     * @return Un pointeur vers la filière recherchée si elle existe, 0 sinon.
     */
    filiere* trouverFil(const QString& n) {return filieres.find(n).value();}
    /**
     * @brief Crée et ajoute une nouevlle filière dans la liste des filières.
     * @param nom Nom de la filière à créer
     * @param c Nombre de crédits requis pour valider la nouvelle filière
     */
    void ajouterFiliere(const QString& nom, unsigned int c);
    /**
     * @brief Charge les filières et les formations contenues dans les fichiers .xml.
     */
    void chargerCursus();
    /**
     * @brief Crée et ajoute une nouvelle formation à la liste des formation existantes
     * @param nom Nom de la formation à créer
     * @param c Nombre de crédits requis pour valider la formation
     * @param s Nombre de semestres (normalement) nécessaires pour terminer la formation
     * @param ccs Nombre de crédits requis dans la catégorie CS pour valider la formation
     * @param ctm Nombre de crédits requis dans la catégorie TM pour valider la formation
     * @param ctsh Nombre de crédits requis dans la catégorie TSH pour valider la formation
     */
    formation* ajouterFormation(const QString& nom, unsigned int c, unsigned int s, unsigned int ccs, unsigned int ctm, unsigned int ctsh,  unsigned int csp);
    /**
     * @brief Retire une formation de la liste des formations et détruit l'objet correspondant.
     * @param nom Nom de la formation à supprimer.
     */
    void supprimerFormation(const QString& nom);
    /**
     * @brief Retire une filière de la liste des filières et détruit l'objet correspondant.
     * @param nom Nom de la filière à supprimer
     */
    void supprimerFiliere(const QString& nom);
    /**
     * @brief Modifie une filière existante
     * @param oldkey Ancien nom de la filière
     * @param newname nouveau nom de la filière
     * @param c Nouveau nombre de crédits requis
     */
    void modifFiliere(const QString& oldkey, const QString& newname, unsigned int c);
    /**
     * @brief Modifie une formation existante
     * @param oldkey Ancien nom de la formation
     * @param newname Nouveau nom de la formation
     * @param c Nouveau nombre de crédits requis
     * @param s Nouveau nombre de semestres nécessaires
     * @param ccs Nouveau nombre de crédits requis dans la catégorie CS
     * @param ctm Nouveau nombre de crédits requis dans la catégorie TM
     * @param ctsh Nouveau nombre de crédits requis dans la catégorie TSH
     */
    void modifFormation(const QString& oldkey, const QString& newname, unsigned int c, unsigned int s, unsigned int ccs, unsigned int ctm, unsigned int ctsh, unsigned int csp);
    /**
     * @brief Sauvegarde des filière et des formations dans les fichiers .xml
     */
    void sauverCursus();
    /**
     * @brief Accepte un objet visiteur
     * @param v Pointeur vers le visiteur concerné
     * @param type Permet de sélectionner le travail sur les formations ou les filières
     */
    void accept(visiteur* v, QString type);
    /**
     * @brief Inscrit une filière dans une formation
     * @param form pointeur sur la formation concernée
     * @param fil Nom de la filière à inscrire
     */
    void inscrFilForm(formation* form, const QString& fil);
    /**
     * @brief Retire une filière d'une formation
     * @param form Pointeur sur la formation concernée
     * @param fil Nom de la filière à retirer
     */
    void supprFilForm(formation* form, const QString& fil);
    /**
     * @brief Recherche une filière dans une formation
     * @param form Pointeur sur la formation concernée
     * @param fil Nom de la filière recherchée
     * @return "true" si la filière est inscrite dans la formation, "false" sinon
     */
    bool trouverFilForm(formation* form, const QString& fil);

    QMap<QString,formation*>::iterator getQmapIteratorFormbegin() {return formations.begin();}
    QMap<QString,formation*>::iterator getQmapIteratorFormend() {return formations.end();}
    QMap<QString,filiere*>::iterator getQmapIteratorFilBegin() {return filieres.begin();}
    QMap<QString,filiere*>::iterator getQmapIteratorFilEnd() {return filieres.end();}

    static cursusManager& getInstance();
    static void libererInstance();
};

#endif // CURSUS_H
