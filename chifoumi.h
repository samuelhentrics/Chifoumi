#ifndef CHIFOUMI_H
#define CHIFOUMI_H

#include <QMainWindow>
#include <QTimer>
#include "parametrage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Chifoumi; }
QT_END_NAMESPACE

class Chifoumi : public QMainWindow
{
    Q_OBJECT    

public:
    Chifoumi(QWidget *parent = nullptr);
    ~Chifoumi();

private:
    Ui::Chifoumi *ui;

    ///* ---- PARTIE MODèLE ---------------------------

        ///* Une définition de type énuméré
    public:
        enum UnCoup {pierre, papier, ciseau, rien};

        ///* Méthodes du Modèle

        // Getters
        UnCoup getCoupJoueur();
            /* retourne le dernier coup joué par le joueur */
        UnCoup getCoupMachine();
            /* retourne le dernier coup joué par le joueur */
        unsigned int getScoreJoueur();
            /* retourne le score du joueur */
        unsigned int getScoreMachine();
            /* retourne le score de la machine */
        char determinerGagnant();
            /* détermine le gagnant 'J' pour joueur, 'M' pour machine, 'N' pour match nul
               en fonction du dernier coup joué par chacun d'eux */

         ///* Méthodes utilitaires du Modèle
    private :
        UnCoup genererUnCoup();
    /* retourne une valeur aléatoire = pierre, papier ou ciseau.
       Utilisée pour faire jouer la machine */

        // Setters
    public:
        void setCoupJoueur(UnCoup p_coup);
            /* initialise l'attribut coupJoueur avec la valeur
               du paramètre p_coup */
        void setCoupMachine(UnCoup p_coup);
             /* initialise l'attribut coupmachine avec la valeur
               du paramètre p_coup */
        void setScoreJoueur(unsigned int p_score);
            /* initialise l'attribut scoreJoueur avec la valeur
               du paramètre p_score */
        void setScoreMachine(unsigned int p_score);
             /* initialise l'attribut coupMachine avec la valeur
               du paramètre p_score */

        // Autres modificateurs
         void majScores(char p_gagnant);
            /* Mise à jour des scores en fonction des règles de gestion actuelles :
                - 1 point pour le gagnant lorsqu'il y a un gagnant
                - 0 point en cas de match nul
            */


     private:
         void initScores();
             /* initialise à 0 les attributs scoreJoueur et scoreMachine
                NON indispensable */
         void initCoups();
             /* initialise à rien les attributs coupJoueur et coupMachine
                NON indispensable */
        void desactiver();
            /* permet de désactiver les boutons, le timer
             */

         ///* Attributs du Modèle
     private:
        unsigned int scoreJoueur;   // score actuel du joueur
        unsigned int scoreMachine;  // score actuel de la Machine
        UnCoup coupJoueur;          // dernier coup joué par le joueur
        UnCoup coupMachine;         // dernier coup joué par la machine
        QTimer *timer = new QTimer(this); // timer qui s'enclenche toutes les 1 secondes
        unsigned int tempsPartie; // Temps par défaut avant la fin d'une partie
        unsigned int tempsRestant; // Temps restant pour la partie
        Parametrage *param = new Parametrage(this);

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



#endif // CHIFOUMI_H
