#ifndef RESULTATS_H
#define RESULTATS_H

#include <QDialog>
#include "database.h"

namespace Ui {
class Resultats;
}

class Resultats : public QDialog
{
    Q_OBJECT


public:
    explicit Resultats(QWidget *parent = nullptr);
    ~Resultats();

    ///* SLOTS PUBLICS
public slots:
    void majTabScore();
    /* Permet de mettre à jour le tableau des scores si de nouvelles saisies ont été faites */


    ///* Attributs privées
private:
    Database *db = new Database();

private:
    Ui::Resultats *ui;

};

#endif // RESULTATS_H
