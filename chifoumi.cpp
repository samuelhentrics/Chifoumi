/***************************************************************
 * Name:      chifoumiMain.cpp
 * Author:    Samuel HENTRICS LOISTINE, Ahmed FAKHFAKH, Cédric ETCHEPARE
 * Created:   2022-04-28
 * Description : Chifoumi v3
 **************************************************************/
#include "chifoumi.h"
#include "ui_chifoumi.h"
#include <QMessageBox>

#include <cstdlib>
#include <ctime>


///* ---- PARTIE MODèLE ---------------------------


Chifoumi::Chifoumi(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Chifoumi)
{
    //ctor
    // partie modèle
    scoreJoueur=0;
    scoreMachine=0;
    coupJoueur=rien;
    coupMachine=rien;
    ui->setupUi(this);

    connect(ui->bNouvellePartie, SIGNAL(clicked()), this, SLOT(lancerPartie()));
    connect(ui->actionQuitter, SIGNAL(triggered()), QCoreApplication::instance(), SLOT(quit()), Qt::QueuedConnection);
    connect(ui->actionA_propos_de, SIGNAL(triggered()), this, SLOT(aProposDe()));

    // Activation des connexions pour les événements afin de jouer
    connect(ui->bCiseau, SIGNAL(pressed()), this, SLOT(jouerCiseau()));
    connect(ui->bPapier, SIGNAL(pressed()), this, SLOT(jouerPapier()));
    connect(ui->bPierre, SIGNAL(pressed()), this, SLOT(jouerPierre()));
}

Chifoumi::~Chifoumi()
{
    delete ui;
}

void Chifoumi::lancerPartie(){
    // Activer les boutons pierre, papier, ciseau
    ui->bPierre->setEnabled(true);
    ui->bPapier->setEnabled(true);
    ui->bCiseau->setEnabled(true);

    // Texte du joueur en bleu
    ui->lJoueur->setStyleSheet("color: blue");
    ui->lScoreJoueur->setStyleSheet("color: blue");

    // Réinitialisation des scores
    initScores();
    initCoups();

    // Reinitialiser les images des coups des joueurs et leurs scores
    ui->lCoupJoueur->setPixmap(QPixmap(":/res/images/rien_115.png"));
    ui->lCoupMachine->setPixmap(QPixmap(":/res/images/rien_115.png"));
    ui->lScoreJoueur->setText(QString::number(scoreJoueur));
    ui->lScoreMachine->setText(QString::number(scoreMachine));
}


void Chifoumi::finirPartie()
{
    //On vérifie si le joueur à gagné.
    if (getScoreJoueur()==5)
    {
        // Désctiver les boutons pierre, papier, ciseau
        ui->bPierre->setEnabled(false);
        ui->bPapier->setEnabled(false);
        ui->bCiseau->setEnabled(false);
        // Afficher le message de fin du partie
        QMessageBox* mBox;
        mBox = new QMessageBox();
        mBox->information(this,
                          tr("Fin de partie"),
                         "Bravo le joueur ! Vous gagné en 5 points.");
    }
    //On vérifie si la machine à gagnée.
    if (getScoreMachine()==5)
    {
        // Désctiver les boutons pierre, papier, ciseau
        ui->bPierre->setEnabled(false);
        ui->bPapier->setEnabled(false);
        ui->bCiseau->setEnabled(false);
        // Afficher le message de fin du partie
        QMessageBox* mBox;
        mBox = new QMessageBox();
        mBox->information(this,
                          tr("Fin de partie"),
                         "Bravo la machine ! Vous gagné en 5 points.");
    }
}

void Chifoumi::jouerCiseau(){
    emit jouerPartie(ciseau);
}

void Chifoumi::jouerPapier(){
    emit jouerPartie(papier);
}

void Chifoumi::jouerPierre(){
    emit jouerPartie(pierre);
}

void Chifoumi::jouerPartie(UnCoup coup){
    // Déterminer jeu
    coupJoueur=coup;
    coupMachine=genererUnCoup();

    // Determiner gagnant
    majScores(determinerGagnant());

    // Mise à jour de l'interface

    // -- Mise à jour de l'interface pour le coup du joueur
    switch (coupJoueur) {
    case pierre:
        ui->lCoupJoueur->setPixmap(QPixmap(":/res/images/pierre_115.png"));
        break;

    case papier:
        ui->lCoupJoueur->setPixmap(QPixmap(":/res/images/papier_115.png"));
        break;

    case ciseau:
        ui->lCoupJoueur->setPixmap(QPixmap(":/res/images/ciseau_115.png"));
        break;

    default:break;

    }

    // -- Mise à jour de l'interface pour le coup de la machine
    switch (coupMachine) {
    case pierre:
        ui->lCoupMachine->setPixmap(QPixmap(":/res/images/pierre_115.png"));
        break;

    case papier:
        ui->lCoupMachine->setPixmap(QPixmap(":/res/images/papier_115.png"));
        break;

    case ciseau:
        ui->lCoupMachine->setPixmap(QPixmap(":/res/images/ciseau_115.png"));
        break;

    default:break;

    }

    // -- Mise à jour de l'interface pour les scores du joueur et de la machine
    ui->lScoreJoueur->setText(QString::number(scoreJoueur));
    ui->lScoreMachine->setText(QString::number(scoreMachine));

    emit finirPartie();


}

void Chifoumi::aProposDe(){
    QMessageBox* mBoxInfo = new QMessageBox();
    mBoxInfo->setWindowTitle("A propos de cette application");
    mBoxInfo->setText("Version 3.0.\n"
                      "Dernière modification le : 04/05/2022.\n"
                      "Crée par Samuel HENTRICS LOISTINE, Cédric ETCHEPARE, Ahmed FAKHFAKH");
    mBoxInfo->show();
}

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
