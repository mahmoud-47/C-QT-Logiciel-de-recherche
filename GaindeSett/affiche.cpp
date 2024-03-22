#include "affiche.h"
#include "ui_affiche.h"
#include<QStandardPaths>

Affiche::Affiche(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Affiche)
{
    ui->setupUi(this);


}

Affiche::~Affiche()
{
    delete ui;
    delete model;
}

void Affiche::travail(){
    QString dbPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/GaindeSettDB/companies.db";
    qDebug() << dbPath;
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
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
    qDebug() << "database opened aff\n";

    QSqlQuery query(database);
    //query = QSqlQuery(database);
    query.prepare("select * from companies");
    query.exec();
    qDebug() << "Last Query " << query.lastQuery();
    qDebug() << "Last error " << query.lastError().text();

    //if(model==NULL)
    model = new QSqlQueryModel();

    model->setQuery(std::move(query));
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0, 40);  //id
    ui->tableView->setColumnWidth(1, 180); //nom
    ui->tableView->setColumnWidth(2, 220); //industry
    ui->tableView->setColumnWidth(3, 150); //secteur
    ui->tableView->setColumnWidth(4, 250); //lien
    ui->tableView->setColumnWidth(5, 300); //vocation
    ui->tableView->setColumnWidth(6, 450); //description

    database.close();
}
