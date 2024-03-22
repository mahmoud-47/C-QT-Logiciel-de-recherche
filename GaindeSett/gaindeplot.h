#ifndef GAINDEPLOT_H
#define GAINDEPLOT_H

#include <QDialog>
#include <QTimer>
#include "qcustomplot.h"

#include "tablehachage.h"
#include "databaseheader.h"
#include "base.h"

namespace Ui {
class GaindePlot;
}

class GaindePlot : public QDialog
{
    Q_OBJECT

public:
    explicit GaindePlot(QWidget *parent = 0);
    ~GaindePlot();
    void travail();

    void setTable(TableHachage &table);
    void setHashs(int, int);


private:
    Ui::GaindePlot *ui;
    TableHachage tab;
    int hash1;
    int hash2;
};

#endif // GAINDEPLOT_H
