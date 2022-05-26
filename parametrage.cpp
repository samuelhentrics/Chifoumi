#include "parametrage.h"
#include "ui_parametrage.h"

Parametrage::Parametrage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Parametrage)
{
    ui->setupUi(this);
}

Parametrage::~Parametrage()
{
    delete ui;
}
