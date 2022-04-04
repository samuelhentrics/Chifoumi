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
	return rien;
}

Chifoumi::UnCoup Chifoumi::getCoupMachine() {
    return rien;
}

unsigned int Chifoumi::getScoreJoueur() {
    return 0;
}

unsigned int Chifoumi::getScoreMachine() {
    return 0;
}

char Chifoumi::determinerGagnant()
{
    char gagnantARetourner;

    // avant de commencer : match nul
    gagnantARetourner = 'N';

    // il sera modifi� dans l'un des cas suivants


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

	valeurGeneree = rien;
    return valeurGeneree;
}

        /// Setters

void Chifoumi::setCoupJoueur(UnCoup p_coup) {
}

void Chifoumi::setCoupMachine(UnCoup p_coup) {
}

void Chifoumi::setScoreJoueur(unsigned int p_score) {
}

void Chifoumi::setScoreMachine(unsigned int p_score) {
}

void Chifoumi::majScores(char p_gagnant) {
}

void Chifoumi::initScores() {
}

void Chifoumi::initCoups() {
}
