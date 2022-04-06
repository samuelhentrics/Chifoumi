/***************************************************************
 * Name:      chifoumiMain.h
 * Author:    P.Dagorret ()
 * Created:   2021-05-10
 * Description : classe m�tier (= mod�le) Chifoumi-v1
 **************************************************************/
#include "chifoumi.h"

#include <cstdlib>
#include <ctime>


///* ---- PARTIE MOD�LE ---------------------------

Chifoumi::Chifoumi()
{
    //ctor
    // partie mod�le
}

Chifoumi::~Chifoumi()
{
    //dtor
}

/// Getters

Chifoumi::UnCoup Chifoumi::getCoupJoueur() {
    return coupJoueur;
}

Chifoumi::UnCoup Chifoumi::getCoupMachine() {
    return coupMachine;
}

unsigned int Chifoumi::getScoreJoueur() {
    return scoreJoueur;
}

unsigned int Chifoumi::getScoreMachine() {
    return scoreMachine;
}

char Chifoumi::determinerGagnant()
{
    char gagnantARetourner;

    // avant de commencer : match nul
    gagnantARetourner = 'N';

    // il sera modifi� dans l'un des cas suivants
    if (getCoupJoueur()>getCoupMachine()){

    }

    return gagnantARetourner;
}

///* M�thodes utilitaires du Mod�le

int randMinMax(int min, int max){
    /* pr�-condition : min<max ;
       Le nbre al�atoire est compris entre [min, max[ */
    return rand()%(max-min) + min;
}

Chifoumi::UnCoup Chifoumi::genererUnCoup()
{
    UnCoup valeurGeneree;   // valeur � retourner
    int valeurAleatoire;   // valeur al�atoire retourner par la machine
    valeurGeneree=rien;
    valeurAleatoire = randMinMax(1,3);
    switch (valeurAleatoire) {
    case 1 : valeurGeneree=pierre; break;
    case 2 : valeurGeneree=papier; break;
    case 3 : valeurGeneree=ciseau; break;
    default : break;
    }
    return valeurGeneree;
}

/// Setters

void Chifoumi::setCoupJoueur(UnCoup p_coup) {
    coupJoueur = p_coup;
}

void Chifoumi::setCoupMachine(UnCoup p_coup) {
    coupMachine = p_coup;
}

void Chifoumi::setScoreJoueur(unsigned int p_score) {
    scoreJoueur = p_score+1;
}

void Chifoumi::setScoreMachine(unsigned int p_score) {
    scoreJoueur = p_score+1;
}

void Chifoumi::majScores(char p_gagnant) {
    if (p_gagnant=='M'){
        setScoreMachine(getScoreMachine());
    }
    else if (p_gagnant=='J'){
        setScoreJoueur(getScoreJoueur());
    }
}

void Chifoumi::initScores() {
    scoreJoueur=0;
    scoreMachine=0;
}

void Chifoumi::initCoups() {
    coupJoueur= rien;
    coupMachine = rien;
}
