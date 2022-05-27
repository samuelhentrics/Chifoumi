/***************************************************************
 * Name:      chifoumiMain.cpp
 * Author:    Samuel HENTRICS LOISTINE, Ahmed FAKHFAKH, Cédric ETCHEPARE
 * Created:   2022-04-14
 * Description : Chifoumi v0
 **************************************************************/

#include "chifoumi.h"

#include <cstdlib>
#include <ctime>


///* ---- PARTIE MODèLE ---------------------------

Chifoumi::Chifoumi()
{
    //ctor
    // partie modèle
    scoreJoueur=0;
    scoreMachine=0;
    coupJoueur=rien;
    coupMachine=rien;

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

    // il sera modifié dans l'un des cas suivants

    if (getCoupJoueur()>=0 && getCoupJoueur()<=2
            && getCoupMachine()>=0 && getCoupMachine()<=2){
        if (getCoupJoueur()==0 && getCoupMachine()==2){
            gagnantARetourner = 'J';
        }
        else if (getCoupMachine()==0 && getCoupJoueur()==2){
            gagnantARetourner = 'M';
        }
        else if (getCoupJoueur()>getCoupMachine()){
            gagnantARetourner = 'J';
        }
        else if (getCoupMachine()>getCoupJoueur()){
            gagnantARetourner = 'M';
        }
    }

    return gagnantARetourner;
}

///* Méthodes utilitaires du Modèle

int randMinMax(int min, int max){
    /* pré-condition : min<max ;
       Le nbre aléatoire est compris entre [min, max[ */
    return rand()%(max-min) + min;
}

Chifoumi::UnCoup Chifoumi::genererUnCoup()
{
    UnCoup valeurGeneree;   // valeur à retourner
    int valeurAleatoire;   // valeur aléatoire retourner par la machine
    valeurGeneree=rien;
    valeurAleatoire = randMinMax(1,4);
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
    scoreJoueur = p_score;
}

void Chifoumi::setScoreMachine(unsigned int p_score) {
    scoreMachine = p_score;
}

void Chifoumi::majScores(char p_gagnant) {
    if (p_gagnant=='M'){
        // On incrémente le score de la machine si la machine a gagné
        setScoreMachine(getScoreMachine()+1);
    }
    else if (p_gagnant=='J'){
        // On incrémente le score du joueur si le joueur a gagné
        setScoreJoueur(getScoreJoueur()+1);
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
