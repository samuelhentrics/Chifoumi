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
    Database *db = new Database();
    ChifoumiVue *chifoumi;

private slots:
    void connexion();
};

#endif // CONNEXION_H
