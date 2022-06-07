/***************************************************************
 * Name:      chifoumi.h
 * Author:    Samuel HENTRICS LOISTINE, Ahmed FAKHFAKH, Cédric ETCHEPARE
 * Created:   2022-04-14
 * Description : classe métier (= Modèle) Chifoumi-v1
 **************************************************************/

#ifndef CHIFOUMI_H
#define CHIFOUMI_H
#include <iostream>

using namespace std;

class Chifoumi
{
    ///* ---- PARTIE MODèLE ---------------------------

    ///* Une définition de type énuméré
public:
    enum UnCoup {pierre, papier, ciseau, rien};

    ///* Méthodes du Modèle
public:
    Chifoumi();
    virtual ~Chifoumi();

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
    void initScores();
    /* initialise à 0 les attributs scoreJoueur et scoreMachine
               NON indispensable */
    void initCoups();
    /* initialise à rien les attributs coupJoueur et coupMachine
               NON indispensable */


    ///* Attributs du Modèle
private:
    unsigned int scoreJoueur;   // score actuel du joueur
    unsigned int scoreMachine;  // score actuel de la Machine
    UnCoup coupJoueur;          // dernier coup joué par le joueur
    UnCoup coupMachine;         // dernier coup joué par la machine
};

#endif // CHIFOUMI_H
