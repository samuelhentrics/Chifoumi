/***************************************************************
 * Name:      chifoumiVue.cpp
 * Author:    Samuel HENTRICS LOISTINE, Ahmed FAKHFAKH, Cédric ETCHEPARE
 * Created:   2022-05-27
 * Description : Chifoumi v6
 **************************************************************/

#include "chifoumivue.h"
#include "chifoumi.h"
#include "ui_chifoumivue.h"
#include <QMessageBox>
#include "QDebug"
#include <cstdlib>
#include <ctime>


///* ---- PARTIE MODèLE ---------------------------


ChifoumiVue::ChifoumiVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ChifoumiVue)
{

    // Paramètrage de base pour une partie
    nomJoueur="Vous"; // Si la jouer n'a pas saisie son nom dans les paramètres
    scoreGagnant=5; // Score à atteindre par défaut afin de gagner
    tempsPartie=30; // temps limite par défaut afin que la partie se termine
    ui->setupUi(this);

    // Activation des connexions pour les boutons
    connect(ui->bNouvellePartie, SIGNAL(clicked()), this, SLOT(lancerPartie()));
    connect(ui->actionQuitter, SIGNAL(triggered()), QCoreApplication::instance(), SLOT(quit()), Qt::QueuedConnection);
    connect(ui->actionA_propos_de, SIGNAL(triggered()), this, SLOT(aProposDe()));
    connect(ui->actionParam_trage, SIGNAL(triggered()), this, SLOT(parametrerJeu()));
    connect(ui->bPause, SIGNAL(clicked()), this, SLOT(majPause()));

    // Activation des connexions pour les événements afin de jouer
    connect(ui->bCiseau, SIGNAL(pressed()), this, SLOT(jouerCiseau()));
    connect(ui->bPapier, SIGNAL(pressed()), this, SLOT(jouerPapier()));
    connect(ui->bPierre, SIGNAL(pressed()), this, SLOT(jouerPierre()));
    connect(timer, SIGNAL(timeout()), this, SLOT(majTemps()));
}

ChifoumiVue::~ChifoumiVue()
{
    delete ui;
}


QString ChifoumiVue::getNomJoueur(){
    return QString(nomJoueur);
}

unsigned int ChifoumiVue::getScoreJeu(){
    return scoreGagnant;
}

unsigned int ChifoumiVue::getTempsJeu(){
    return tempsPartie;
}

void ChifoumiVue::lancerPartie(){
    // Activer les boutons pierre, papier, ciseau
    ui->bPierre->setEnabled(true);
    ui->bPapier->setEnabled(true);
    ui->bCiseau->setEnabled(true);
    ui->bPause->setEnabled(true);

    // Texte du joueur en bleu
    ui->lJoueur->setStyleSheet("color: blue");
    ui->lScoreJoueur->setStyleSheet("color: blue");

    // Réinitialisation des scores
    leJeu->initScores();
    leJeu->initCoups();

    // Reinitialiser les images des coups des joueurs et leurs scores
    ui->lCoupJoueur->setPixmap(QPixmap(":/res/images/rien_115.png"));
    ui->lCoupMachine->setPixmap(QPixmap(":/res/images/rien_115.png"));
    ui->lScoreJoueur->setText(QString::number(leJeu->getScoreJoueur()));
    ui->lScoreMachine->setText(QString::number(leJeu->getScoreMachine()));

    // Activation du timer
    tempsRestant=tempsPartie;
    ui->lTempsRestant->setText(QString::number(tempsRestant));
    timer->start(1000);

    // Désactivation du paramètrage
    disconnect(ui->actionParam_trage, SIGNAL(triggered()), this, SLOT(parametrerJeu()));
}


void ChifoumiVue::finirPartie()
{
    QMessageBox* mBox;
    mBox = new QMessageBox();

    //On vérifie si le joueur à gagné.
    if (leJeu->getScoreJoueur()==scoreGagnant)
    {
        // On désactive tous les boutons pour jouer
        desactiver();
        // Afficher le message de fin du partie
        mBox->information(this,
                          tr("Fin de partie"),
                         "Bravo "+QString(nomJoueur)+" ! Vous gagnez en "+QString::number(scoreGagnant)+" points.");
    }

    //On vérifie si la machine à gagnée.
    else if (leJeu->getScoreMachine()==scoreGagnant)
    {
        // On désactive tous les boutons pour jouer
        desactiver();
        // Afficher le message de fin du partie
        mBox->information(this,
                          tr("Fin de partie"),
                         "Bravo la machine ! Vous gagnez en "+QString::number(scoreGagnant)+" points.");
    }

    // On vérifie si le timer est à zéro
    else if (tempsRestant==0)
    {
        // On désactive tous les boutons pour jouer
        desactiver();
        // Afficher le message de fin du partie
        QString message;
        if (leJeu->getScoreJoueur()>leJeu->getScoreMachine()){
            message="Helas chers joueurs, temps de jeu fini ! Vous terminez toutefois mieux, avec "+QString::number(leJeu->getScoreJoueur())+" points.";
        }
        else if (leJeu->getScoreMachine()>leJeu->getScoreJoueur()){
            message="Helas chers joueurs, temps de jeu fini ! La machine termine toutefois mieux, avec "+QString::number(leJeu->getScoreMachine())+" points.";
        }
        else{
            message="Helas chers joueurs, temps de jeu fini ! Vous terminez avec une égalité";
        }
        mBox->information(this,
                          tr("Fin de partie"),
                         message);
    }


}

void ChifoumiVue::desactiver(){
    // Désactiver les boutons pierre, papier, ciseau
    ui->bPierre->setEnabled(false);
    ui->bPapier->setEnabled(false);
    ui->bCiseau->setEnabled(false);

    // Désactiver le timer
    timer->stop();
    ui->bPause->setText("Pause");
    ui->bPause->setEnabled(false);

    // On réactive la possibilité de paramètrer le jeu
    connect(ui->actionParam_trage, SIGNAL(triggered()), this, SLOT(parametrerJeu()));
}

void ChifoumiVue::majTemps(){
    tempsRestant-=1;
    ui->lTempsRestant->setText(QString::number(tempsRestant));
    if (tempsRestant==0){
        emit finirPartie();
    }
}

void ChifoumiVue::majPause(){
    // Met le jeu en pause si le timer est actif
    if (timer->isActive()){
        // Désactive le choix des coups ainsi que la possibilité de lancer une nouvelle partie
        ui->bPierre->setEnabled(false);
        ui->bPapier->setEnabled(false);
        ui->bCiseau->setEnabled(false);
        ui->bNouvellePartie->setEnabled(false);
        timer->stop(); // Arrete le timer
        ui->bPause->setText("Reprise jeu"); // Renomme le bouton "Pause" en "Reprise jeu"
    }
    // Si le timer est inactif, le jeu se reprend
    else{
        // Réactive le choix des coups ainsi que la possibilité de lancer une nouvelle partie
        ui->bPierre->setEnabled(true);
        ui->bPapier->setEnabled(true);
        ui->bCiseau->setEnabled(true);
        ui->bNouvellePartie->setEnabled(true);
        timer->start(); // Relance le timer
        ui->bPause->setText("Pause");  // Renomme le bouton "Reprise jeu" en "Pause"

    }
}

void ChifoumiVue::jouerCiseau(){
    emit jouerPartie(Chifoumi::UnCoup::ciseau);
}

void ChifoumiVue::jouerPapier(){
    emit jouerPartie(Chifoumi::UnCoup::papier);
}

void ChifoumiVue::jouerPierre(){
    emit jouerPartie(Chifoumi::UnCoup::pierre);
}

void ChifoumiVue::jouerPartie(Chifoumi::UnCoup coup){
    // Déterminer jeu
    leJeu->setCoupJoueur(coup);
    leJeu->setCoupMachine(leJeu->genererUnCoup());

    // Determiner gagnant
    leJeu->majScores(leJeu->determinerGagnant());

    // Mise à jour de l'interface
    // -- Mise à jour de l'interface pour le coup du joueur
    switch (leJeu->getCoupJoueur()) {
    case Chifoumi::UnCoup::pierre:
        ui->lCoupJoueur->setPixmap(QPixmap(":/res/images/pierre_115.png"));
        break;

    case Chifoumi::UnCoup::papier:
        ui->lCoupJoueur->setPixmap(QPixmap(":/res/images/papier_115.png"));
        break;

    case Chifoumi::UnCoup::ciseau:
        ui->lCoupJoueur->setPixmap(QPixmap(":/res/images/ciseau_115.png"));
        break;

    default:break;

    }

    // -- Mise à jour de l'interface pour le coup de la machine
    switch (leJeu->getCoupMachine()) {
    case Chifoumi::UnCoup::pierre:
        ui->lCoupMachine->setPixmap(QPixmap(":/res/images/pierre_115.png"));
        break;

    case Chifoumi::UnCoup::papier:
        ui->lCoupMachine->setPixmap(QPixmap(":/res/images/papier_115.png"));
        break;

    case Chifoumi::UnCoup::ciseau:
        ui->lCoupMachine->setPixmap(QPixmap(":/res/images/ciseau_115.png"));
        break;

    default:break;

    }

    // -- Mise à jour de l'interface pour les scores du joueur et de la machine
    ui->lScoreJoueur->setText(QString::number(leJeu->getScoreJoueur()));
    ui->lScoreMachine->setText(QString::number(leJeu->getScoreMachine()));

    emit finirPartie();


}

void ChifoumiVue::aProposDe(){
    QMessageBox* mBoxInfo = new QMessageBox();
    mBoxInfo->setWindowTitle("A propos de cette application");
    mBoxInfo->setText("Version 5.0.\n"
                      "Dernière modification le : 24/05/2022.\n"
                      "Crée par Samuel HENTRICS LOISTINE, Cédric ETCHEPARE, Ahmed FAKHFAKH");
    mBoxInfo->show();
}

void ChifoumiVue::parametrerJeu(){
    param = new Parametrage(getNomJoueur(), getScoreJeu(), getTempsJeu(), this);
    int retour = param->exec();
    switch(retour)
    {
        case QDialog::Accepted :
            if (param->getNom()!="") // Si l'utilisateur à remplit le champ de 'nom'
            {
                ui->lJoueur->setText(QString(param->getNom())); // On change le label avec le nom saisie par l'utilisateur
                nomJoueur=param->getNom(); // on change la valeur du variable nomJoueur par le nom saisie par l'utilisateur
            }

            if (param->getPoints()!=0) // Si l'utilisateur à remplit le champ de 'Points'
            {
                ui->lGagnantScore->setText(QString::number(param->getPoints())); // On change le label avec le nombre de points saisie par l'utilisateur
                scoreGagnant=param->getPoints(); // on change la valeur du variable GagnantScore par le nombre de points saisie par l'utilisateur
            }

            if (param->getTemps()!=0) // Si l'utilisateur à remplit le champ de 'Temps'
            {
                ui->lTempsRestant->setText(QString::number(param->getTemps())); // On change le label avec le temps saisie par l'utilisateur
                tempsPartie=param->getTemps(); // on change la valeur du variable tempsPartie par le temps saisie par l'utilisateur
            }
        break;
        default:break;
    }
}
