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
    bool ok =query.exec("create table Utilisateurs (id int(4) PRIMARY KEY NOT NULL AUTO_INCREMENT,"
                        "nom VARCHAR(25) NOT NULL, mdp VARCHAR(30) NOT NULL);");

    query.exec("create table Resultats (id int(4) PRIMARY KEY NOT NULL AUTO_INCREMENT,"
               "horodatage DATETIME DEFAULT CURRENT_TIMESTAMP,"
               "joueur_id int(4),"
               "scoreJoueur int(4) NOT NULL,"
               "scoreMachine int(4) NOT NULL,"
               "CONSTRAINT FK_Joueur FOREIGN KEY (joueur_id) REFERENCES Utilisateurs(id));");

    // On va insérer un joueur de base lors de la création de la base/si la base existe mais
    // le joueur n'existe pas.

    //qDebug() << "Tentative ajout Elliot";
    query.exec("SELECT COUNT(*) FROM Utilisateurs");
    query.next();
    //qDebug() << query.value(0).toInt();
    if (query.value(0).toInt()==0){
        if (query.exec("insert into Utilisateurs (nom, mdp) values ('Elliot', 'test');")){
            //qDebug() << "Ajout de l'utilisateur principal, OK";
        }
        else {
            //qDebug() << "Erreur lors de l'ajout d'Elliot.";
        }
    }

    return ok;
}

bool Database::insertTable(const QVariantList &data)
{
    QSqlQuery query;
    QString insertions="insert into Utilisateurs (nom, mdp) "
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
        if(query.value(1).toString() == nom && query.value(2).toString()==mdp){
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
        if(query.value(1).toString() == nouveauNom){
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

bool Database::insertResultat(QString nom, unsigned int scoreJoueur, unsigned int scoreMachine){
    QSqlQuery query;
    unsigned int numId;
    query.exec("SELECT * FROM Utilisateurs");

    // On va récupérer l'identifiant du joueur
    for (int i =0; query.next(); i++){
        if(query.value(1).toString() == nom){
            numId = query.value(0).toInt();
        }
    }

    // On va insérer le résultat
    QString insertion = "INSERT INTO Resultats (joueur_id, scoreJoueur, scoreMachine)"
                        "VALUES (:joueur_id, :scoreJoueur, :scoreMachine)";
    query.prepare(insertion);
    query.bindValue(":joueur_id", numId);
    query.bindValue(":scoreJoueur", scoreJoueur);
    query.bindValue(":scoreMachine", scoreMachine);
    return query.exec();
}
