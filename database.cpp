#include "database.h"

Database::Database()
{

}

bool Database::openDatabase()
{
    mydb = QSqlDatabase::addDatabase(CONNECT_TYPE);
    mydb.setDatabaseName(DATABASE_NAME);
    if(mydb.open())
    {
        return true;
    } else {
        return false;
    }
}

void Database::closeDatabase()
{
    mydb.close();
}

bool Database::restoreDatabase(){
    bool ok = openDatabase();
    if(ok){
        qDebug() << "Tentative création bdd";
        createTable();
    }
    return ok;

}

bool Database::createTable()
{
    QSqlQuery query;
    bool ok =query.exec("create table Identifiants (utilisateur varchar(25) primary key, mdp varchar(30));");

    // On va insérer un joueur de base lors de la création de la base/si la base existe mais
    // le joueur n'existe pas.

    qDebug() << "Tentative ajout Elliot";
    QSqlQuery insertQuery("insert into identifiants values ('elliot','test');");
    if (insertQuery.exec()){
        qDebug() << "Ajout de l'utilisateur principal, OK";
    }
    else {
        qDebug() << "Erreur lors de l'ajout d'Elliot.";
    }

    return ok;
}

bool Database::insertTable(const QVariantList &data)
{
    QSqlQuery query;
    QString insertions="insert into Identifiants "
                       " values(:utilisateur, :mdp);";
    query.prepare(insertions);
    query.bindValue(":utilisateur", data[0].toString());
    query.bindValue(":mdp", data[1].toString());
    if(!query.exec()){
//        qDebug() << "Erreur lors de l'insertion : ";
//        qDebug() << query.lastError().text();
        return false;
    }
    else
        return true;
}

bool Database::verifierMotDePasse(QString nom, QString mdp){
    // On va récupérer le mot de passe de la BDD
    QSqlQuery query("SELECT mdp FROM identifiants");
    query.exec();

    if(query.value(0).toString() == mdp){
        return true;
    }
    else{
        return false;
    }
}
