/***************************************************************
 * Name:      parametrage.h
 * Author:    Samuel HENTRICS LOISTINE, Ahmed FAKHFAKH, Cédric ETCHEPARE
 * Created:   2022-05-27
 * Description : Permet le paramètrage du jeu
 **************************************************************/

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

public:
    void setNom(QString nom);
    /* Permet de mettre dans le champ de saisie, le nom actuel du
     * joueur de la partie*/
    void setPoints(unsigned int points);
    /* Permet de mettre dans le champ de saisie, les points actuels
     * pour gagner une partie*/
    void setTemps(unsigned int temps);
    /* Permet de mettre dans le champ de saisie, le temps maximum
     * actuel pour gagner une partie*/

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
