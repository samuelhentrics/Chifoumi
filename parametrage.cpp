/***************************************************************
 * Name:      parametrage.cpp
 * Author:    Samuel HENTRICS LOISTINE, Ahmed FAKHFAKH, Cédric ETCHEPARE
 * Created:   2022-05-29
 * Description : Permet le paramètrage du jeu
 **************************************************************/


#include "parametrage.h"
#include "ui_parametrage.h"
#include <QMessageBox>
#include <QPushButton>
#include <QIntValidator>

///* ---- PARTIE VUE ---------------------------

Parametrage::Parametrage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Parametrage)
{
    ui->setupUi(this);

    // Activation des connexions
    QObject::connect(ui->leNom,SIGNAL(textChanged(const QString&)),this,SLOT(verifierNom()));
}

Parametrage::~Parametrage()
{
    delete ui;
}

///* Setters

void Parametrage::setNom(QString nom){
    ui->leNom->setText(nom);
}

void Parametrage::setPoints(unsigned int points){
    ui->lePoints->setValue(points);
}

void Parametrage::setTemps(unsigned int temps){
    ui->leTemps->setValue(temps);
}


///* Getters

QString Parametrage::getNom()
{
    return ui->leNom->text();
}

unsigned int Parametrage::getPoints()
{
    return ui->lePoints->value() ;
}

unsigned int Parametrage::getTemps()
{
    return ui->leTemps->value() ;
}

///* Slots privés

void Parametrage::verifierNom()
{
    QString nom = ui->leNom->text();
    if (nom==""){
        QMessageBox msgBox;
        msgBox.setWindowTitle("Saisie Impossible");
        msgBox.setText("Votre nom ne peut être vide.");
        msgBox.exec();
        ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
    }
    else{
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
}

