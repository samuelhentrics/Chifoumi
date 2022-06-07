#include "resultats.h"
#include "ui_resultats.h"

resultats::resultats(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::resultats)
{
    ui->setupUi(this);
}

resultats::~resultats()
{
    delete ui;
}
