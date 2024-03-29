/*!
 *  \file UTprofiler.h
 *  \brief Fichier développé lors des scéances de TD.
 */

#ifndef UT_PROFILER_h
#define UT_PROFILER_h

#include "iterateur.h"
#include <QString>
#include <QTextStream>
#include <QMessageBox>

using namespace std;
class formation;
class UTProfilerException;

class visiteur;
enum Categorie {
 CS, TM,
   TSH, SP
};

QTextStream& operator<<(QTextStream& f, const Categorie& s);
Categorie StringToCategorie(const QString& s);
QString CategorieToString(Categorie c);
QTextStream& operator>>(QTextStream& f, Categorie& cat);

enum Note { A, B, C, D, E, F, FX, RES, ABS, /* en cours */ EC  };
QString Note2String(Note n);
Note String2Note(const QString& n);
enum Saison { Automne, Printemps };
Saison StringToSaison(const QString& s);
QString SaisonToString(Saison c);
inline QTextStream& operator<<(QTextStream& f, const Saison& s) { if (s==Automne) f<<"A"; else f<<"P"; return f;}
/*!
 * \brief Classes permettant de gérer les Semestres comme des objets.
 */
class Semestre {
    Saison saison;
    unsigned int annee;
public:
    Semestre(Saison s=Automne, unsigned int a=0):saison(s),annee(a){}
    Saison getSaison() const { return saison; }
    unsigned int getAnnee() const { return annee; }
    void setSaison(Saison s) { saison=s; }
    void setAnnee(unsigned int a) { annee=a; }
    bool operator<(const Semestre& b) const;
    bool operator==(const Semestre& b) const;
    void operator++() ;

};

inline QTextStream& operator<<(QTextStream& f, const Semestre& s) { return f<<s.getSaison()<<s.getAnnee()%100; }
/*!
 * \brief Un objet de type \"UV\" contient tous les détails relatifs à une UV.
 */
class UV {
    QString code;
    QString titre;
    unsigned int nbCredits;
    Categorie categorie;
    bool automne;
    bool printemps;
    UV(const UV& u);
    UV& operator=(const UV& u);
    UV(const QString& c, const QString& t, unsigned int nbc, Categorie cat, bool a, bool p):
      code(c),titre(t),nbCredits(nbc),categorie(cat),automne(a),printemps(p){}
    friend class UVManager;
public:
    QString getCode() const { return code; }
    QString getTitre() const { return titre; }
    unsigned int getNbCredits() const { return nbCredits; }
    Categorie getCategorie() const { return categorie; }
    bool ouvertureAutomne() const { return automne; }
    bool ouverturePrintemps() const { return printemps; }
    void setCode(const QString& c) { code=c; }
    void setTitre(const QString& t) { titre=t; }
    void setNbCredits(unsigned int n) { nbCredits=n; }
    void setCategorie(Categorie c) { categorie=c; }
    void setOuvertureAutomne(bool b) { automne=b; }
    void setOuverturePrintemps(bool b) { printemps=b; }
};

QTextStream& operator<<(QTextStream& f, const UV& uv);

/*!
 * \brief Singleton gérant les UVs.
 */
class UVManager {
private:
    UV** uvs;
    unsigned int nbUV;
    unsigned int nbMaxUV;
    void addItem(UV* uv);
    void removeItem(UV* uv);
    bool modification;
    UVManager(const UVManager& um);
    UVManager& operator=(const UVManager& um);
    UVManager();
    ~UVManager();
    QString file;
    friend struct Handler;
    struct Handler{
        UVManager* instance;
        Handler():instance(0){}
        ~Handler(){ if (instance) delete instance; instance=0; }
    };
    static Handler handler;

public:

    void load();
    void save();
    static UVManager& getInstance();
    static void libererInstance();
    UV* ajouterUV(const QString& c, const QString& t, unsigned int nbc, Categorie cat, bool a, bool p);
    void supprimerUV(const QString& c);
    const UV& getUV(const QString& code) const;
    UV& getUV(const QString& code);
    UV* trouverUV(const QString& c) const;
    void accept(visiteur* v);

    class iterateur<UV>;
    iterateur<UV>& getIterateurForm()
    {
        iterateur<UV>* it=new iterateur<UV>(uvs,nbUV);
        return *it;
    }
};

#endif
