/***************************************************************
 * Name:      connexion.h
 * Author:    Samuel HENTRICS LOISTINE, Ahmed FAKHFAKH, Cédric ETCHEPARE
 * Created:   2022-05-30
 * Description : Chifoumi v7
 **************************************************************/

#ifndef CONNEXION_H
#define CONNEXION_H

#include <QDialog>
#include "chifoumivue.h"
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

private:
    Ui::Connexion *ui;
    Database *db = new Database(); //
    ChifoumiVue *chifoumi = new ChifoumiVue(); //

private slots:
    void demanderConnexion();
    // permet de se connecter
};

#endif // CONNEXION_H
