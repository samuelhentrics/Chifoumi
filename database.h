/***************************************************************
 * Name:      database.h
 * Author:    Samuel HENTRICS LOISTINE, Ahmed FAKHFAKH, Cédric ETCHEPARE
 * Created:   2022-05-30
 * Description : Chifoumi v7
 **************************************************************/

#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QVariantList>

#define DATABASE_NAME "bdd_chifoumi"
#define CONNECT_TYPE "QODBC"

class Database
{
public:
    Database();
    bool openDatabase();
    // renvoie vrai si la base s'ouvre, faux sinon
    void closeDatabase();
    // Permet de fermer la base de donnée
    bool restoreDatabase();
    // // renvoie faux si impossible d'acceder la bdd et vrai sinon

private:
    QSqlDatabase mydb;

private:
    bool createTable();
    // permet de créer le table Identifiants
    bool insertTable(const QVariantList &);
    // permet de peupler la table Identifiants

};

#endif // DATABASE_H
