/***************************************************************
 * Name:      connexion.h
 * Author:    Samuel HENTRICS LOISTINE, Ahmed FAKHFAKH, Cédric ETCHEPARE
 * Created:   2022-05-30
 * Description : Chifoumi v7
 **************************************************************/

#ifndef CONNEXION_H
#define CONNEXION_H

#include <QDialog>
#include "database.h"

namespace Ui {
class Connexion;
}

class Connexion : public QDialog
{
    Q_OBJECT

public:
    explicit Connexion(QWidget *parent = nullptr);
    ~Connexion();
    bool infoConnexion();
    /* Retourne vrai si le joueur est connecté, faux si celui-ci ne l'est pas */

private:
    Ui::Connexion *ui;
    bool estConnecte;
    /* Statut du joueur si celui-ci est connecté */
    Database *db = new Database();
    /* Base de données */


private slots:
    void demanderConnexion();
    // permet de se connecter
};

#endif // CONNEXION_H
