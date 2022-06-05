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


    connect(ui->bEntrer, SIGNAL(clicked()), this, SLOT(demanderConnexion()));

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

    // On va récupérer le mot de passe de la BDD
    QSqlQuery query("SELECT mdp FROM Identifiants WHERE utilisateur='sam';");
    query.exec();

    // Vérification si le mot de passe est correcte
    qDebug() << query.value(0);
    if(query.value(0).toString() == password){
        qDebug() << "pas bon";
        estConnecte=true;
        close();
    }
    // Si le mot de passe est incorrect, on affiche un message d'erreur
    else{
        QMessageBox::information(this, "Mot de passe incorrect",
                                 "Votre mot de passe semble incorrect, veuillez réessayer.");
    }
}

bool Connexion::infoConnexion(){
    return estConnecte;
}
