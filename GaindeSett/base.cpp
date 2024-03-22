#include "base.h"
#include "databaseheader.h"
#include "tablehachage.h"
#include <QMessageBox>
#include <QDebug>
#include <QStandardPaths>


void Base::charger(TableHachage &table){
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");


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
    qDebug() << "database opened charger\n";

    QSqlQuery query(database);
    //query = QSqlQuery(database);
    query.prepare("select * from companies");
    query.exec();

    while(query.next()){

        int x = table.inserer(query.value(1).toString(),
                               query.value(2).toString(),
                               query.value(3).toString(),
                               query.value(4).toString(),
                               query.value(5).toString(),
                               query.value(6).toString());
        if(!x)  qDebug() << "Erreur insert";
    }
    qDebug() << "size " << table.size();

    qDebug() << "Last error " << query.lastError().text();

    database.close();

}

