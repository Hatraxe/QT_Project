/*!
 * \file LoginForm.cpp
 * \brief Implémentation de la classe LoginForm.
 */

#include "LoginForm.h"
#include "ui_loginform.h"
#include <QSignalSpy>
/*!
 * \brief Constructeur de LoginForm qui initialise les composants UI et les connexions de signaux.
 * \param parent Le widget parent de LoginForm.
 * \param loginManager Le gestionnaire de connexion utilisé pour authentifier les utilisateurs.
 *
 * Connecte le bouton d'inscription à son slot correspondant.
 */
LoginForm::LoginForm(QWidget *parent, std::shared_ptr<LoginManager> loginManager)
    : QWidget(parent),
    ui(new Ui::LoginForm),
    loginManager(loginManager)
{
    ui->setupUi(this);

    // QSignalSpy spy(ui->pushButton_Login, &QPushButton::clicked);

    // Connecte le bouton de connexion à son slot
    connect(ui->pushButton_Login, &QPushButton::clicked, this, &LoginForm::login);
    qDebug() << "Connection du signal clicked au slot on push button clicked";

    // Connecte le bouton "Mot de passe oublié" à son slot
    connect(ui->pushButton_MdpOublie, &QPushButton::clicked, this, &LoginForm::mdpOublie);
    // Connecte le bouton d'inscription à son slot
    connect(ui->signUpButton, &QPushButton::clicked, this, &LoginForm::signInSignal);
}

/*!
 * \brief Destructeur de LoginForm qui nettoie l'interface utilisateur.
 */
LoginForm::~LoginForm() {
    delete ui;
}

/*!
 * \brief Tente de connecter l'utilisateur avec les identifiants fournis.
 *
 * Si la connexion est réussie, émet le signal userConnected. Sinon, affiche une alerte.
 */
void LoginForm::login() {
    QString login = ui->lineEdit_Login_Email->text();
    QString motDePasse = ui->lineEdit_Mdp->text();
    qDebug() << "on push button login clicked";


    // Tente de se connecter avec le LoginManager
    if (loginManager && loginManager->login(login, motDePasse)) {
        QMessageBox::information(this, "Connexion réussie", "Vous êtes maintenant connecté.");
        emit userConnected();
    } else {
        QMessageBox::warning(this, "Échec de la connexion", "Login ou mot de passe incorrect.");
    }
}

/*!
 * \brief Affiche une information sur la récupération du mot de passe.
 *
 * Ce slot est déclenché par un clic sur le bouton "Mot de passe oublié".
 */
void LoginForm::mdpOublie() {
    QMessageBox::information(this, "Récupération du mot de passe", "Pour récupérer votre mot de passe, veuillez contacter l'administrateur.");
}

/*!
 * \brief Émet le signal signUpRequested lorsqu'un utilisateur souhaite s'inscrire.
 *
 * Ce slot est déclenché par un clic sur le bouton "S'inscrire".
 */
void LoginForm::signInSignal() {
    emit signUpRequested();
}
