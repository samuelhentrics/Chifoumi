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
    void closeDatabase();

private:
    QSqlDatabase mydb;

private:
    bool createTable();
    bool insertTable(const QVariantList &);

};

#endif // DATABASE_H
