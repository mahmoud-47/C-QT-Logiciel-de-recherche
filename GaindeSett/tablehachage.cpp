#include "TableHachage.h"
#include "base.h"
#include "databaseheader.h"
#include <QDebug>
#include<QStandardPaths>

int TableHachage::actualHash = 0;
int TableHachage::nbElements = 0;
pCompany TableHachage::companies[Max] = {nullptr};
std::vector<Company> TableHachage::addsComps;
std::vector<QString> TableHachage::delsComps;

//*******************************************************************************************

TableHachage::TableHachage(){}
//***********************************************************************************


int TableHachage::fonctionHachageSommeASCII(QString cle){
    int hash=0;
    for(QChar c : cle)
       hash += static_cast<int>(c.toLatin1());
    return hash % Max;
}
//*******************************************************************************************

int TableHachage::fonctionHachagedjb2Hash(QString str) {
    const char* data = str.toUtf8().constData();
        unsigned long hash = 5381;

        int c;
        while ((c = *data++)) {
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        }

        return hash%Max;
}
//*******************************************************************************************

int TableHachage::bernstein(QString nom) {
    unsigned int hash = 5381;
    for (QChar c : nom) {
        hash = 33 * hash + c.digitValue();
    }
    return hash % Max;
}
//*******************************************************************************************

int TableHachage::fonctionSansHachage(QString nom){
    for(int i=0; i< Max ;i++)
    {
        if(companies[i] == nullptr)
        {
             return i;
        }
    }
    return -1;
}
//***********************************************************************************
int TableHachage::functionHash(QString nom){
    if (actualHash>=0 && actualHash<4)

           return (this->*fonctionhachage[actualHash])(nom);

    else
        return -1;

}
//*******************************************************************************************

void TableHachage::setActuelhash(int hash){
    TableHachage::actualHash=hash;
}

int TableHachage::getActuelhash(){
    return actualHash;
}
//*******************************************************************************************

bool TableHachage::inserer(QString nom, QString ind, QString sect, QString lien, QString voc, QString desc){

    int index= functionHash(nom);
    if( index != -1){
        pCompany current = companies[index];
        while (current != nullptr) {
            // Vérifier si le nom existe déjà
            if (current->nom ==nom) {
                // Le nom existe déjà, donc ne rien faire
                return false;
            }
            current = current->next;
        }

        // Le nom n'existe pas, insérer le nouvel élément au début de la liste chaînée
        pCompany newElement = new Company{nom, ind, sect, lien, voc, desc, companies[index] };
        newElement->next = companies[index];
        companies[index] = newElement;

        // Augmenter le nombre d'éléments dans la table
        TableHachage::nbElements++;
        return true;
    }

    return false;

}


//*******************************************************************************************

pCompany TableHachage:: get(QString cle) {
    if(actualHash==0){
        for(int i=0; i<Max; i++){
            pCompany current = companies[i];

            while (current != nullptr && current->nom != cle) {
                current = current->next;
            }
            if(current)
                return current;
        }
        return nullptr;
    }

    int index = functionHash(cle);
    pCompany current = companies[index];

    while (current != nullptr && current->nom != cle) {
        current = current->next;
    }

    return current;
}
//*******************************************************************************************

void TableHachage::suppression(QString nom) {
    if(actualHash==0){
        int i = 0;
        while(companies[i] && companies[i]->nom != nom)
            i++;
        if(companies[i]){
            delete companies[i];
            companies[i] = nullptr;

        }
        nbElements--;
        return;
    }

    int index = functionHash(nom);

    pCompany previousCompany = nullptr;
    pCompany currentCompany = companies[index];
    while (currentCompany != nullptr) {
        if (currentCompany->nom == nom) {
            // L'élément a été trouvé, supprimez-le
            if (previousCompany == nullptr) {
                // Premier élément de la liste, mettez à jour la tête de liste
                companies[index] = currentCompany->next;
            } else {
                // Élément intermédiaire ou dernier élément de la liste, mettez à jour les pointeurs
                previousCompany->next = currentCompany->next;
            }

            // Libérez la mémoire occupée par l'élément
            delete currentCompany;

            // Décrémentez le nombre d'éléments
            nbElements--;

        }

        previousCompany = currentCompany;
        currentCompany = currentCompany->next;
    }

}

//*******************************************************************************************

int TableHachage::size() {
    int count = 0;
    for (int i = 0; i < Max; ++i) {
        pCompany current = companies[i];
        while (current != nullptr) {
            ++count;
            current = current->next;
        }
    }

    return count;
}

int TableHachage::nbOQP(){
    int count = 0;

    for (int i = 0; i < Max; ++i) {
        pCompany current = companies[i];
        if (current) {
            ++count;
            //current = current->next;
        }
    }

    return count;
}

//*******************************************************************************************

bool TableHachage::contient(QString cle) {
    return get(cle) != nullptr;
}
//*******************************************************************************************

bool TableHachage::estVide() {
    return nbElements == 0;
}
//*******************************************************************************************

TableHachage::~TableHachage() {
    for (int i = 0; i < Max; ++i) {
        pCompany current = companies[i];
        while (current != nullptr) {
            pCompany next = current->next;
            delete current;
            current = next;
        }
        companies[i] = nullptr;
    }
}

void TableHachage::viderTable() {
    for (int i = 0; i < Max; ++i) {
        pCompany current = companies[i];
        while (current != nullptr) {
            pCompany next = current->next;
            delete current;
            current = next;
        }
        companies[i] = nullptr;
    }
}
//*******************************************************************************************

pCompany TableHachage::rechercherElement(QString nom) {
    if(actualHash==0){
        for(int i=0; i<Max; i++){
            pCompany current = companies[i];

            while (current != nullptr && current->nom != nom) {
                current = current->next;
            }
            if(current)
                return current;
        }
        return nullptr;
    }

    int index = functionHash(nom);
    pCompany currentCompany = companies[index];
    while (currentCompany != nullptr) {
        if (currentCompany->nom == nom) {

            return currentCompany;
        }
        currentCompany = currentCompany->next;
    }


    return nullptr;
}
//*******************************************************************************************

void TableHachage::updateToDb(){
    //QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    // Check if a connection with the same name already exists
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        // If it does, remove the existing connection
        QSqlDatabase::removeDatabase("qt_sql_default_connection");
    }

    // Add a new database connection
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE", "qt_sql_default_connection");
    QString dbPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/GaindeSettDB/companies.db";
    database.setDatabaseName(dbPath);

    if(QFile::exists(dbPath))
        qDebug() << "Database file exist\n";
    else{
        qDebug() << "Database file does not exist\n";
        return;
    }
    if(!database.open()){
        qDebug() << "Enable to open the database\n";
        return;
    }
    qDebug() << "database opened\n";

    QSqlQuery query(database);
    qDebug() << "Adds size " << addsComps.size();
    for (Company company : this->addsComps) {
        query.prepare("INSERT INTO companies (nom, industrie, secteur, lien, vocation, description) "
                      "VALUES (:nom, :industrie, :secteur, :lien, :vocation, :description)");

        query.bindValue(":nom", company.nom);
        query.bindValue(":industrie", company.industrie);
        query.bindValue(":secteur", company.secteur);
        query.bindValue(":lien", company.lien);
        query.bindValue(":vocation", company.vocation);
        query.bindValue(":description", company.description);

        if (!query.exec()) {
            qDebug() << "Erreur sur " << company.nom << ": " << query.lastError().text();

        }
    }

    for (QString nom : this->delsComps) {
        query.prepare("DELETE FROM companies where nom='"+nom+"'");

        if (!query.exec()) {
            qDebug() << "Error sur la suppression de " << nom << ": " << query.lastError().text();
        }
    }


    database.close();
    this->addsComps.clear();
    this->delsComps.clear();
}

int TableHachage::getNbIterationsRecherche(QString nom){
    int count = 0;
    if(actualHash==0){
        for(int i=0; i<Max; i++){
            pCompany current = companies[i];

            while (current != nullptr && current->nom != nom) {
                count++;
                current = current->next;
            }
            if(current)
                return count;
        }
        return 0;
    }

    int index = functionHash(nom);
    pCompany currentCompany = companies[index];
    while (currentCompany != nullptr) {
        count++;
        if (currentCompany->nom == nom) {

            return count;
        }
        currentCompany = currentCompany->next;
    }


    return 0;
}
