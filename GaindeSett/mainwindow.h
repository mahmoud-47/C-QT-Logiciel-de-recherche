#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "affiche.h"
#include "recherche.h"
#include "insere.h"
#include "supprimer.h"
#include"gaindeplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();
    void on_actionCharger_2_triggered();
    void on_pushButton_3_clicked();
    void on_actionQuitter_triggered();
    void on_actionRechercher_triggered();
    void on_actionTaille_triggered();
    void on_actionnserer_triggered();
    void on_actionSupprimer_triggered();
    void on_actionf1_triggered();
    void on_actionSansHach_triggered();
    void on_actionf2_triggered();
    void on_actionf3_triggered();
    void on_actionCharger_triggered();
    void on_pushButton_clicked();
    void on_actionNombre_de_lignes_triggered();
    void on_actionSauvegarder_triggered();
    void on_actionHachage_Actuelle_triggered();
    void on_SommeAsciiSanshachage_triggered();
    void on_djb2Hash_Sanshachage_triggered();
    void on_bernstein_Sanshachage_triggered();
    void on_SommeAscii_djb2Hash_triggered();
    void on_SommeAscii_bernstein_triggered();
    void on_djb2Hash_bernstein_triggered();

private:
    Ui::MainWindow *ui;
    Affiche *pAffiche;
    Recherche *pRecherche;
    Insere *pInsere;
    Supprimer *pSupprimer;
    GaindePlot* pGaindePlot;

};

#endif // MAINWINDOW_H
