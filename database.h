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
    ///* Procédures publiques
public:
    Database();
    bool openDatabase();
    // renvoie vrai si la base s'ouvre, faux sinon
    void closeDatabase();
    // Permet de fermer la base de donnée
    bool restoreDatabase();
    // Retourne faux si impossible d'acceder la bdd et vrai sinon
    bool verifierMotDePasse(QString nom, QString mdp);
    /* Retourne vrai si le mot de passe est celui de l'utilisateur, faux sinon. */
    bool updateNomUtilisateur(QString ancienNom, QString nouveauNom);
    /* Essaye de modifier le nom d'un utilisateur, retourne vrai si cela a marché
     * faux, si le nom d'utilisateur existe déjà*/
    bool insertResultat(QString nom, unsigned int scoreJoueur, unsigned int scoreMachine);
    /* Permet d'inserer les résultats d'une partie finie */

    ///* Attributs publics
private:
    QSqlDatabase mydb;

    ///* Procédures privées
private:
    bool createTable();
    // permet de créer le table Identifiants
    bool insertTable(const QVariantList &);
    // permet de peupler la table Identifiants

};

#endif // DATABASE_H
