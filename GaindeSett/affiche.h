#ifndef AFFICHE_H
#define AFFICHE_H

#include <QDialog>
#include "databaseheader.h"


namespace Ui {
class Affiche;
}

class Affiche : public QDialog
{
    Q_OBJECT

public:
    explicit Affiche(QWidget *parent = 0);
    ~Affiche();
    void travail();

private:
    Ui::Affiche *ui;
    QSqlQueryModel *model;
};

#endif // AFFICHE_H
