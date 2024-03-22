#ifndef INSERE_H
#define INSERE_H

#include <QDialog>
#include "tablehachage.h"
#include "base.h"

namespace Ui {
class Insere;
}

class Insere : public QDialog
{
    Q_OBJECT

public:
    explicit Insere(QWidget *parent = 0);
    void setTable(TableHachage &table);
    void setBase(Base &up);
    ~Insere();

private slots:

    void on_btnEffacer_clicked();

    void on_btnEnregistrer_clicked();

private:
    Ui::Insere *ui;
    TableHachage tab;
    Base updates;
};

#endif // INSERE_H
