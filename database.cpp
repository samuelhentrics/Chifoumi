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
        //qDebug() << "Tentative création bdd";
        createTable();
    }
    return ok;

}

bool Database::createTable()
{
    QSqlQuery query;
    bool ok =query.exec("create table Utilisateurs (nom varchar(25) primary key, mdp varchar(30));");

    // On va insérer un joueur de base lors de la création de la base/si la base existe mais
    // le joueur n'existe pas.

    //qDebug() << "Tentative ajout Elliot";
    if (query.exec("insert into Utilisateurs values ('Elliot', 'test');")){
        //qDebug() << "Ajout de l'utilisateur principal, OK";
    }
    else {
        //qDebug() << "Erreur lors de l'ajout d'Elliot.";
    }

    return ok;
}

bool Database::insertTable(const QVariantList &data)
{
    QSqlQuery query;
    QString insertions="insert into Utilisateurs "
                       " values(:nom, :mdp);";
    query.prepare(insertions);
    query.bindValue(":nom", data[0].toString());
    query.bindValue(":mdp", data[1].toString());
    if(!query.exec()){
        //qDebug() << "Erreur lors de l'insertion : ";
        //qDebug() << query.lastError().text();
        return false;
    }
    else
        return true;
}

bool Database::verifierMotDePasse(QString nom, QString mdp){
    // On récupére le mot de passe de la BDD
    QSqlQuery query;
    query.exec("SELECT * FROM Utilisateurs");

    // On va vérifier s'il existe dans notre base, le nom d'utilisateur ainsi
    // que la correspondance du mot de passe si celui-ci existe
    for (int i =0; query.next(); i++){
        if(query.value(0).toString() == nom && query.value(1).toString()==mdp){
            return true;
        }
    }
    return false;
}

bool Database::updateNomUtilisateur(QString ancienNom, QString nouveauNom){
    QSqlQuery query;
    query.exec("SELECT * FROM Utilisateurs");

    // On va vérifier s'il existe dans notre base, le nouveau nom d'utilisateur
    for (int i =0; query.next(); i++){
        if(query.value(0).toString() == nouveauNom){
            //qDebug() << "Nouveau nom déjà existant";
            return false;
        }
    }

    // Sinon, on effectue la modification
    QString formuleModif="update Utilisateurs "
                       "set nom=:nouveauNom"
                       " where nom=:ancienNom";

    // On va mettre les infos que l'on souhaite
    query.prepare(formuleModif);
    query.bindValue(":nouveauNom", nouveauNom);
    query.bindValue(":ancienNom", ancienNom);
    if(!query.exec()){
        //qDebug() << "Erreur lors de l'insertion : ";
        //qDebug() << query.lastError().text();
        return false;
    }
    else{
        //qDebug() << "Modification du nom d'utilisateur OK";
        return true;
    }
}
