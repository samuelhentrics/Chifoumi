#include "parametrage.h"
#include "ui_parametrage.h"
#include <QMessageBox>
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
    bool valeurCorrecte;
    unsigned int point = points.toUInt(&valeurCorrecte, 10);
    if (!valeurCorrecte){
        QMessageBox msgBox;
        msgBox.setWindowTitle("Saisie Impossible");
        msgBox.setText("Ce champ ne contient pas de valeur numérique.");
        msgBox.exec();
    }
    else {
        if (point>1) // si l'utilisateur a respecté l'intervalle
        {
            return point;
        }
    }

    return 0 ;
}

unsigned int Parametrage::getTemps()
{
    QString temps = ui->leTemps->text();
    bool valeurCorrecte;
    unsigned int temp = temps.toUInt(&valeurCorrecte, 10);
    if (!valeurCorrecte){
        QMessageBox msgBox;
        msgBox.setWindowTitle("Saisie Impossible");
        msgBox.setText("Ce champ ne contient pas de valeur numérique.");
        msgBox.exec();
    }
    else{
        if (temp >10) // si l'utilisateur a respecté l'intervalle
        {
            return temp;
        }
    }

    return 0 ;

}

