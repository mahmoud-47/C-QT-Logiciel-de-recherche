#include "recherche.h"
#include "ui_recherche.h"
#include "tablehachage.h"
#include <QDebug>
#include <QMessageBox>

Recherche::Recherche(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Recherche)
{
    ui->setupUi(this);


}

void Recherche::setTable(TableHachage &table){
    tab = table;
}

Recherche::~Recherche()
{
    delete ui;
}

void Recherche::on_pushButton_3_clicked()
{
    QString nom = ui->txtSearch->text();
    //TableHachage tb;
    pCompany res = tab.rechercherElement(nom);
    if(!res)
        QMessageBox::information(this, "No result", "La recherche avec " + nom + " renvoie zero resultats");
    else{
        ui->txtNom->setText(res->nom);
        ui->txtIndustrie->setText(res->industrie);
        ui->txtSecteur->setText(res->secteur);
        ui->txtLien->setText(res->lien);
        ui->txtVocation->setText(res->vocation);
        ui->txtDescription->setText(res->description);
    }
}
