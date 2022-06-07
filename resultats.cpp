#include "resultats.h"
#include "ui_resultats.h"
#include <QTableWidgetItem>

Resultats::Resultats(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Resultats)
{
    ui->setupUi(this);

    // Activation de la connexion pour fermer la boite de dialogue
    connect(ui->bFermer, SIGNAL(clicked()), this, SLOT(close()));


    // On ajoute tous les résultats dans le tableau

    QSqlQuery query;
    query.exec("SELECT DATE(R.horodatage), TIME(R.horodatage), U.nom, R.scoreJoueur, R.scoreMachine "
               "FROM Resultats R "
               "JOIN Utilisateurs U ON U.id=R.joueur_id "
               "WHERE R.scoreJoueur>=R.scoreMachine "
               "ORDER BY R.horodatage DESC "
               "LIMIT 10;");


    for(int i = 0; query.next(); i++){
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(query.value(3).toInt())));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(QString::number(query.value(4).toInt())));
    }

}

Resultats::~Resultats()
{
    delete ui;
}

void Resultats::majTabScore(){
    // On réinitialise le tableau
    ui->tableWidget->setRowCount(0);

    // On ajoute tous les résultats dans le tableau

    QSqlQuery query;
    query.exec("SELECT DATE(R.horodatage), TIME(R.horodatage), U.nom, R.scoreJoueur, R.scoreMachine "
               "FROM Resultats R "
               "JOIN Utilisateurs U ON U.id=R.joueur_id "
               "WHERE R.scoreJoueur>=R.scoreMachine "
               "ORDER BY R.horodatage DESC "
               "LIMIT 10;");


    for(int i = 0; query.next(); i++){
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(query.value(3).toInt())));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(QString::number(query.value(4).toInt())));
    }
}
