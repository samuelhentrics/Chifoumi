/***************************************************************
 * Name:      parametrage.cpp
 * Author:    Samuel HENTRICS LOISTINE, Ahmed FAKHFAKH, Cédric ETCHEPARE
 * Created:   2022-05-27
 * Description : Permet le paramètrage du jeu
 **************************************************************/


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

void Parametrage::setNom(QString nom){
    ui->leNom->setText(nom);
}

void Parametrage::setPoints(unsigned int points){
    ui->lePoints->setText(QString::number(points));
}

void Parametrage::setTemps(unsigned int temps){
    ui->leTemps->setText(QString::number(temps));
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
        msgBox.setText("Le nombre de points doit être supérieur ou égal à 1.");
        msgBox.exec();
        ui->buttonBox->setDisabled(true);
    }
    else {
        if (point>=1) // si l'utilisateur a respecté l'intervalle
        {
            ui->buttonBox->setEnabled(true);
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
        msgBox.setText("Le temps doit être au minimum de 10 secondes.");
        msgBox.exec();
        ui->buttonBox->setDisabled(true);
    }
    else{
        if (temp >=10) // si l'utilisateur a respecté l'intervalle
        {
            ui->buttonBox->setEnabled(true);
            return temp;
        }
    }

    return 0 ;

}

