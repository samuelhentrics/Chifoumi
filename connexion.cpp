#include "connexion.h"
#include "ui_connexion.h"
#include <QMessageBox>
#include <QDebug>

Connexion::Connexion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Connexion)
{
    estConnecte = false; // Par défaut, le joueur n'est pas connecté

    ui->setupUi(this);
    // Activation des événements
    connect(ui->bEntrer, SIGNAL(clicked()), this, SLOT(demanderConnexion()));

    // Tentative de connexion (et restauration si nécéssaire) à
    if (!db->restoreDatabase()){
        ui->bEntrer->setDisabled(true);
        ui->lError->setText("Erreur à la connexion de la BDD.\nVérifiez le DSN.");
    }
}

Connexion::~Connexion()
{
    delete ui;
}

void Connexion::demanderConnexion(){
    // On récupére les données saisies dans les champs
    QString username = ui->leUtilisateur->text();
    QString password = ui->leMdp->text();

    // Tentative de connexion
    if(db->verifierMotDePasse(username, password)){
        estConnecte=true;
        close();
    }
    // Si le mot de passe est incorrect, on affiche un message d'erreur
    else{
        QMessageBox::information(this, "Identifiant incorrect",
                                 "Votre identifiant semble incorrect, veuillez réessayer.");
    }
}

QString Connexion::getNom(){
    return ui->leUtilisateur->text();
}


bool Connexion::infoConnexion(){
    return estConnecte;
}
