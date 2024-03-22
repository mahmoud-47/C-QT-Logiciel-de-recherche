#include "supprimer.h"
#include "ui_supprimer.h"

Supprimer::Supprimer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Supprimer)
{
    ui->setupUi(this);
}

Supprimer::~Supprimer()
{
    delete ui;
}

void Supprimer::on_pushButton_2_clicked()
{
    close();
}

void Supprimer::on_pushButton_clicked()
{
    QMessageBox msgBox;

        QString nom = ui->lineEdit->text();
        msgBox.setText("Voulez vous reellement supprimer " + nom + "?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);

        msgBox.setButtonText(QMessageBox::Yes, "Oui");
        msgBox.setButtonText(QMessageBox::No, "Non");
        msgBox.setWindowTitle("Suppression");

        int ret = msgBox.exec();

        if (ret == QMessageBox::Yes) {
            if(tab.contient(nom)){
                tab.suppression(nom);
                TableHachage::delsComps.push_back(nom);
                QMessageBox::information(this, "Success", nom + " a été supprimé");
            }else
                QMessageBox::information(this, "Error", nom + " n'a pas été trouvé");
        } else {
            close();
        }
}

void Supprimer::setTable(TableHachage &table){
    this->tab = table;
}
