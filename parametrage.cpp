#include "parametrage.h"
#include "ui_parametrage.h"

Parametrage::Parametrage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Parametrage)
{
    ui->setupUi(this);
    // Activation des connexions
    QObject::connect(ui->leNom,SIGNAL(textChanged(const QString&)),this,SLOT(getNom()));
    QObject::connect(ui->lePoints,SIGNAL(textChanged(const QString&)),this,SLOT(getPoints()));
    QObject::connect(ui->leTemps,SIGNAL(textChanged(const QString&)),this,SLOT(getTemps()));
}

Parametrage::~Parametrage()
{
    delete ui;
}

QString Parametrage::getNom()
{
    QString nom = ui->leNom->text();
    return nom;
}

unsigned int Parametrage::getPoints()
{
    QString points = ui->lePoints->text();
    unsigned int point = points.toUInt();
    if (point>1) // si l'utilisateur a respecté l'intervalle
    {
        return point;
    }
    return 0 ;
}

unsigned int Parametrage::getTemps()
{
    QString temps = ui->leTemps->text();
    unsigned int temp = temps.toUInt();
    if (temp >10) // si l'utilisateur a respecté l'intervalle
    {
        return temp;
    }
    return 0 ;
}

