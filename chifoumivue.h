/***************************************************************
 * Name:      chifoumiVue.h
 * Author:    Samuel HENTRICS LOISTINE, Ahmed FAKHFAKH, Cédric ETCHEPARE
 * Created:   2022-05-27
 * Description : Chifoumi v6
 **************************************************************/

#ifndef CHIFOUMIVUE_H
#define CHIFOUMIVUE_H

#include <QMainWindow>
#include <QTimer>
#include "chifoumi.h"
#include "parametrage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ChifoumiVue; }
QT_END_NAMESPACE

class ChifoumiVue : public QMainWindow
{
    Q_OBJECT

public:
    ChifoumiVue(QWidget *parent = nullptr);
    ~ChifoumiVue();

private:
    Ui::ChifoumiVue *ui;

         ///* Attributs privés de la vue
     private:
        Chifoumi *leJeu = new Chifoumi();
        QString nomJoueur; // nom du joueur
        unsigned int scoreGagnant;  // score à atteindre pour gagner
        QTimer *timer = new QTimer(this); // timer qui s'enclenche toutes les 1 secondes
        unsigned int tempsPartie; // Temps par défaut avant la fin d'une partie
        unsigned int tempsRestant; // Temps restant pour la partie
        Parametrage *param = new Parametrage(this);;

        ///* Procédures publiques de la vue
    public:
        QString getNomJoueur();
            /* permet de récupérer le nom du joueur dans le jeu */
        unsigned int getScoreMaxJeu();
            /* permet de récupérer le score à atteindre pour gagner
             * une partie dans le jeu */
        unsigned int getTempsMaxJeu();
            /* permet de récupérer temps maximum pour gagner
             * une partie dans le jeu */

        ///* Procédures privées de la vue
    private:
       void desactiver();
           /* permet de désactiver les boutons, le timer
            */

       ///* Slots privés de la vue
    private slots:
        void lancerPartie();
            /* Permet de lancer une partie entre le joueur et la machine
            */
        void jouerCiseau();
            /* Le joueur décide de jouer ciseau */
        void jouerPapier();
            /* Le joueur décide de jouer papier */
        void jouerPierre();
            /* Le joueur décide de jouer pierre */
        void jouerPartie(Chifoumi::UnCoup coup);
            /* Permet de déterminer le gagnant et met à jour l'interface
              à partir d'un coup (coup) donné par le joueur */
        void aProposDe();
            /* Permet l'affichage "A propos de..." pour l'utilisateur */
        void finirPartie();
            /* Permet de finir la partie lorsque un joueur a atteint 5 points */
        void majTemps();
            /* Met à jour le temps restant lors d'une partie et peut arreter la partie
            si le compteur est à zero*/
        void majPause();
            /* Met le jeu en pause lorsque l'utilisateur demande à mettre le jeu en pause.
             * Ou alors reprend la partie si le timer est inactif*/
        void parametrerJeu();
        /* Fonction permettant à l'utilisateur de paramètrer le jeu
         * (son nom, la durée d'une partie, le nombre de points pour gagner) */

};



#endif // CHIFOUMIVUE_H
