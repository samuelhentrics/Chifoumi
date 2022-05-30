#include "connexion.h"
#include "ui_connexion.h"

Connexion::Connexion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Connexion)
{  
    if (db->restoreDatabase()){
        ui->setupUi(this);
        connect(ui->bEntrer, SIGNAL(clicked()), this, SLOT(connexion()));
    }
    else{
        QMessageBox::warning(this, tr("Problème de connexion à la BDD"),
                             tr("Votre connexion à votre base de donnée s'est mal passée\n"
                                "Veuillez vérifier que votre DNS se nomme 'bdd_chifoumi'."));
    }
}

Connexion::~Connexion()
{
    delete ui;
}

void Connexion::connexion(){

}
