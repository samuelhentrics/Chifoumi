#include "parametrage.h"
#include "ui_parametrage.h"

parametrage::parametrage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::parametrage)
{
    ui->setupUi(this);
}

parametrage::~parametrage()
{
    delete ui;
}
