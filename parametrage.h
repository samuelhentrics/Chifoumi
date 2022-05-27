#ifndef PARAMETRAGE_H
#define PARAMETRAGE_H

#include <QDialog>

namespace Ui {
class Parametrage;
}

class Parametrage : public QDialog
{
    Q_OBJECT

public:
    explicit Parametrage(QWidget *parent = nullptr);
    ~Parametrage();
public slots:
    QString getNom();
    // permet de retouner le nom saisie par l'utilisateur
    unsigned int getPoints();
    // permet de retourner le nombre max. de points saisie par l'utilisateur
    unsigned int getTemps();
    // permet de retourner le temps max. à jouer saisie par l'utilisateur

private:
    Ui::Parametrage *ui;
};

#endif // PARAMETRAGE_H