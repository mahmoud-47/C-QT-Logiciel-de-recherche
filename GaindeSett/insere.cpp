#include "insere.h"
#include "ui_insere.h"
#include "tablehachage.h"
#include<QMessageBox>

Insere::Insere(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Insere)
{
    ui->setupUi(this);
}

Insere::~Insere()
{
    delete ui;
}

void Insere::on_btnEffacer_clicked()
{
    ui->txtNom->setText("");
    ui->txtIndustrie->setText("");
    ui->txtSecteur->setText("");
    ui->txtVocation->setText("");
    ui->txtLien->setText("");
    ui->txtDescription->setText("");
}

void Insere::on_btnEnregistrer_clicked()
{
    QString nom = ui->txtNom->text();
    QString ind = ui->txtIndustrie->text();
    QString sect =ui->txtSecteur->text();
    QString link = ui->txtLien->text();
    QString voc = ui->txtVocation->text();
    QString desc = ui->txtDescription->toPlainText();

    if(nom=="" || ind=="" || sect=="" || link=="" || voc=="" || desc=="")
        QMessageBox::information(this, "Erreur", "Tous les champs sont obligatoires");
    else if(tab.contient(nom))
        QMessageBox::information(this, "Erreur", "La base de donnees contient deja " + ui->txtNom->text());
    else{
        tab.inserer(nom,ind,sect, link, voc, desc);
        Company cmp = {nom, ind, sect, link, voc, desc};
        TableHachage::addsComps.push_back(cmp);
        QMessageBox::information(this, "Success", nom + " a été ajouté");
    }
}

void Insere::setTable(TableHachage &table){
    tab = table;
}

void Insere::setBase(Base &up){
    this->updates = up;
}
