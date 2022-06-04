#include "connexion.h"
#include "ui_connexion.h"
#include <QDebug>

Connexion::Connexion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Connexion)
{
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
    QSqlQuery query;
    QString formule = "SELECT mdp FROM Utilisateurs WHERE utilisateur = :user";

    // Filtre
    query.prepare(formule);
    query.bindValue(":user", username);

    // Vérification si le mot de passe est correcte
    if(query.value(0) == password){
        qDebug() << "ok";
    }
    // Si le mot de passe est incorrect, on affiche un message d'erreur
    else{
        QMessageBox::information(this, "Mot de passe incorrect",
                                 "Votre mot de passe semble incorrect, veuillez réessayer.");
    }
}
