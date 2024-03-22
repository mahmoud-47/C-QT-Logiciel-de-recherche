#include "gaindeplot.h"
#include "ui_gaindeplot.h"

#include "qcustomplot.h"
#include <chrono>
#include <QStandardPaths>



GaindePlot::GaindePlot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GaindePlot)
{
    ui->setupUi(this);

}

void GaindePlot::travail(){
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
    qDebug() << "database opened\n";

    QSqlQuery query(database);
    //query = QSqlQuery(database);
    query.prepare("select * from companies limit 1000");
    query.exec();

    QVector<double> x(1000), y(1000), x1(1000), y1(1000);
    QVector<QString> noms;

    int oldHash = this->tab.getActuelhash();

    while(query.next())
        noms.push_back(query.value(1).toString());
    database.close();

    QString HashNames[4]={"SansHash", "SommeASCII", "Djb2Hash", "bernstein"};

    tab.setActuelhash(this->hash1);
    Base().charger(this->tab);
    double i = 0;
    for(QString nom : noms){
        x.push_back(i);

        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        pCompany com = this->tab.rechercherElement(nom);
        std::chrono::steady_clock::time_point stop = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

        y.push_back(duration.count());

        i++;
    }
    tab.viderTable();


    tab.setActuelhash(this->hash2);
    Base().charger(this->tab);
    i = 0;
    for(QString nom : noms){
        x1.push_back(i);

        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        pCompany com = this->tab.rechercherElement(nom);

        std::chrono::steady_clock::time_point stop = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

        y1.push_back(duration.count());

        i++;
    }
    tab.viderTable();

    tab.setActuelhash(oldHash);
    Base().charger(this->tab);

    ui->plot->clearGraphs();
    // creer graphe et ajoter les datas:
    ui->plot->addGraph();
    ui->plot->graph(0)->setData(x, y);
    ui->plot->graph(0)->setPen(QPen(QColor(255, 50, 50)));
    ui->plot->graph(0)->setName("Fonction " + HashNames[this->hash1]);
    ui->plot->addGraph();
    ui->plot->graph(1)->setData(x1, y1);
    ui->plot->graph(1)->setName("Fonction " + HashNames[this->hash2]);

    ui->plot->xAxis->setLabel("Donnees");
    ui->plot->yAxis->setLabel("Temps");

    ui->plot->xAxis->setRange(0, 1000);
    ui->plot->yAxis->setRange(0, 40000);
    ui->plot->legend->setVisible(true);
    ui->plot->replot();
}

GaindePlot::~GaindePlot()
{
    delete ui;
}

void GaindePlot::setTable(TableHachage &table){
    this->tab = table;
}

void GaindePlot::setHashs(int h1, int h2){
    this->hash1 = h1;
    this->hash2 = h2;
}


