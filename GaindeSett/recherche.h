#ifndef RECHERCHE_H
#define RECHERCHE_H

#include <QDialog>
#include "tablehachage.h"

namespace Ui {
class Recherche;
}

class Recherche : public QDialog
{
    Q_OBJECT

public:
    void setTable(TableHachage &table);
    explicit Recherche(QWidget *parent = 0);
    ~Recherche();

private slots:
    void on_pushButton_3_clicked();

private:
    Ui::Recherche *ui;
    TableHachage tab;
};

#endif // RECHERCHE_H
