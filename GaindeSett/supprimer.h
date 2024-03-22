#ifndef SUPPRIMER_H
#define SUPPRIMER_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include "tablehachage.h"

namespace Ui {
class Supprimer;
}

class Supprimer : public QDialog
{
    Q_OBJECT

public:
    explicit Supprimer(QWidget *parent = 0);
    void setTable(TableHachage &table);
    ~Supprimer();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Supprimer *ui;
    TableHachage tab;
};

#endif // SUPPRIMER_H
