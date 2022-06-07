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

    ///* Procédures publiques de la vue
public:
    QString getNom();
    /* Retourne le nom d'utilisateur saisi dans le formulaire */
    bool infoConnexion();
    /* Retourne vrai si le joueur est connecté, faux si celui-ci ne l'est pas */

    ///* Attributs privés de la vue
private:
    Ui::Connexion *ui;
    bool estConnecte;
    /* Statut du joueur si celui-ci est connecté */
    Database *db = new Database();
    /* Base de données */

    ///* Slots privés de la vue
private slots:
    void demanderConnexion();
    // Permet de vérifier si l'utilisateur a renseigné les bonnes informations de connexion
};

#endif // CONNEXION_H
