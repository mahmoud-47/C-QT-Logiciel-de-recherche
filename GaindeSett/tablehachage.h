#ifndef TABLEHACHAGE_H
#define TABLEHACHAGE_H

#include<QString>
#include <QDebug>

struct Company{
    QString nom;
    QString industrie;
    QString secteur;
    QString lien;
    QString vocation;
    QString description;
    Company* next;
};

typedef Company* pCompany;
#define Max 1500

class TableHachage{
    private:
        static pCompany companies[Max];
        static int nbElements;
        static int actualHash;

    public:
        static std::vector<Company> addsComps;
        static std::vector<QString> delsComps;

        TableHachage();

        //Fonctions de hachage
        int fonctionHachageSommeASCII(QString);
        int fonctionHachagedjb2Hash(QString);
        int bernstein(QString);
        int fonctionSansHachage(QString);

        //Fonctions demandees
        bool inserer( QString, QString,QString,QString, QString,QString);
        pCompany get(QString);
        void suppression(QString);
        pCompany rechercherElement(QString);
        bool contient(QString);
        int size();
        bool estVide();
        void afficher();

        //Fonctions QT
        int (TableHachage:: *fonctionhachage[4])(QString nom)={
            fonctionSansHachage,
            fonctionHachageSommeASCII,
            fonctionHachagedjb2Hash,
            bernstein
        };
        int functionHash(QString);
        void setActuelhash(int);
        int getActuelhash();
        void viderTable();
        int nbOQP();
        void updateToDb();
        int getNbIterationsRecherche(QString);

        ~TableHachage();

};

#endif // TABLEHACHAGE_H
