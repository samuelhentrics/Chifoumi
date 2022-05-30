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

bool Database::createTable()
{
    QSqlQuery query;
    bool ok =query.exec("create table Identifiants (utilisateur varchar(5) primary key, mdp varchar(30))");
    if (ok)
    {
        qDebug() <<"table crée";
        return true;
    }
    else
    {
        qDebug() <<"table existante";
        return false;
    }
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
        qDebug() << "Erreur lors de l'insertion : ";
        qDebug() << query.lastError().text();
        return false;
    }
    else
        return true;
}
