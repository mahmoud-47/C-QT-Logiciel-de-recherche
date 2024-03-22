#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "tablehachage.h"
#include "base.h"
#include <QStandardPaths>

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#  include <QDesktopWidget>
#endif
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>

TableHachage matable;
Base up;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    pAffiche = new Affiche;
    pRecherche = new Recherche;
    pInsere = new Insere;
    pSupprimer = new Supprimer;
    pGaindePlot = new GaindePlot;

}

MainWindow::~MainWindow()
{
    delete ui;
    delete pAffiche;
    delete pRecherche;
    delete pInsere;
    delete pSupprimer;
    delete pGaindePlot;
}



void MainWindow::on_pushButton_2_clicked()
{
    pAffiche->travail();
    pAffiche->show();
}

void MainWindow::on_actionCharger_2_triggered()
{
    pAffiche->travail();
    pAffiche->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    this->on_actionTaille_triggered();

}

void MainWindow::on_actionQuitter_triggered()
{
    close();
}

void MainWindow::on_actionRechercher_triggered()
{
    if(matable.estVide()){
        QMessageBox::information(this, "Taille de la base", "Vous devez charger la base de donnees d'abord.");
        return;

    }
    pRecherche->setTable(matable);
    pRecherche->show();
}

void MainWindow::on_actionTaille_triggered()
{
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        // If it does, remove the existing connection
        QSqlDatabase::removeDatabase("qt_sql_default_connection");
    }

    // Add a new database connection
    QString dbPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/GaindeSettDB/companies.db";
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE", "qt_sql_default_connection");
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
    query.prepare("select count(*) from companies");
    query.exec();
    query.next();

    qDebug() << "Last error " << query.lastError().text();
    database.close();

    QString nb = QString::number(query.value(0).toInt());

    QMessageBox::information(this, "Taille de la base", "La base de données compte "+nb+" structures.");
}

void MainWindow::on_actionnserer_triggered()
{
    if(matable.estVide()){
        QMessageBox::information(this, "Taille de la base", "Vous devez charger la base de donnees d'abord.");
        return;
    }
    pInsere->setBase(up);
    pInsere->setTable(matable);
    pInsere->show();
}

void MainWindow::on_actionSupprimer_triggered()
{
    if(matable.estVide()){
        QMessageBox::information(this, "Taille de la base", "Vous devez charger la base de donnees d'abord.");
        return;

    }
    pSupprimer->setTable(matable);
    pSupprimer->show();
}

void MainWindow::on_actionSansHach_triggered()
{

    TableHachage().setActuelhash(0);
    on_actionCharger_triggered();
}

void MainWindow::on_actionf1_triggered()
{

     TableHachage().setActuelhash(1);
     on_actionCharger_triggered();
}

void MainWindow::on_actionf2_triggered()
{

    TableHachage().setActuelhash(2);
    on_actionCharger_triggered();
}

void MainWindow::on_actionf3_triggered()
{

    TableHachage().setActuelhash(3);
    on_actionCharger_triggered();
}

void MainWindow::on_actionCharger_triggered()
{
    matable.viderTable();
    Base().charger(matable);
    QMessageBox::information(this, "Success", "La base de données a ete chargee correctement");
}

void MainWindow::on_pushButton_clicked() //bouton charger
{
    on_actionCharger_triggered();
}

void MainWindow::on_actionNombre_de_lignes_triggered()
{
    QMessageBox::information(this, "Success", "La nombre d elements de la structure = " + QString::number(matable.size()) + " Le nomdre de cases prises = " + QString::number(matable.nbOQP()) );

}

void MainWindow::on_actionSauvegarder_triggered()
{
    //Base().liberer();
    matable.updateToDb();
    QMessageBox::information(this, "Success", "La sauvegarde a reussi");
}


void MainWindow::on_actionHachage_Actuelle_triggered()
{
    QString noms[4]={"SansHash", "SommeASCII", "Djb2Hash", "bernstein"};
    QMessageBox::information(this, "Success", "La fonction de hachage actuelle est : " + noms[matable.getActuelhash()]);
}



void MainWindow::on_SommeAsciiSanshachage_triggered()
{
    pGaindePlot->setHashs(0, 1);
    pGaindePlot->travail();
    pGaindePlot->show();
}

void MainWindow::on_djb2Hash_Sanshachage_triggered()
{
    pGaindePlot->setHashs(0, 2);
    pGaindePlot->travail();
    pGaindePlot->show();
}

void MainWindow::on_bernstein_Sanshachage_triggered()
{
    pGaindePlot->setHashs(0, 3);
    pGaindePlot->travail();
    pGaindePlot->show();
}

void MainWindow::on_SommeAscii_djb2Hash_triggered()
{
    pGaindePlot->setHashs(1, 2);
    pGaindePlot->travail();
    pGaindePlot->show();
}

void MainWindow::on_SommeAscii_bernstein_triggered()
{
    pGaindePlot->setHashs(1, 3);
    pGaindePlot->travail();
    pGaindePlot->show();
}

void MainWindow::on_djb2Hash_bernstein_triggered()
{
    pGaindePlot->setHashs(2, 3);
    pGaindePlot->travail();
    pGaindePlot->show();
}
