/*!
 * \file Application.cpp
 * \brief Implémentation de la classe Application.
 */

#include "Application.h"
#include "./ui_application.h"
#include "SignInForm.h"
#include "LoginForm.h"
#include "userdataview.h"
using namespace std;

/*!
 * \brief Constructeur de Application.
 * \param parent Le widget parent.
 *
 * Initialise l'interface utilisateur et les composants principaux de l'application.
 */
Application::Application(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Application),
    userStorage(make_shared<UserStorage>()) {
    loginManager = make_shared<LoginManager>(userStorage);
    ui->setupUi(this);
    initializeApplication();
}

/*!
 * \brief Destructeur de Application.
 *
 * Nettoie l'interface utilisateur.
 */
Application::~Application() {
    delete ui;  // ui est géré manuellement et doit être supprimé
}

/*!
 * \brief Initialise les composants de l'application.
 *
 * Crée et ajoute les formulaires de connexion, d'inscription et de visualisation des données utilisateur
 * au QStackedWidget, et connecte les signaux aux slots appropriés.
 */
void Application::initializeApplication() {
    auto signInForm = new SignInForm(this, userStorage);
    auto loginForm = new LoginForm(this, loginManager);
    auto userDataView = new UserDataView(this, loginManager);

    signInFormIndex = ui->stackedWidget->addWidget(signInForm);
    loginFormIndex = ui->stackedWidget->addWidget(loginForm);
    userDataViewIndex = ui->stackedWidget->addWidget(userDataView);

    // Connexion des signaux et des slots
    connect(signInForm, &SignInForm::userCreated, this, &Application::showLoginPage);
    qDebug() << "connection du signal usercreated au slot ShowLoginPage";
    connect(loginForm, &LoginForm::userConnected, this, &Application::showUserDataViewPage);
    connect(loginForm, &LoginForm::userConnected, userDataView, &UserDataView::refreshUserInfos);
    connect(userDataView, &UserDataView::logoutRequested, this, &Application::handleLogout);
    connect(loginForm, &LoginForm::signUpRequested, this, &Application::showUserCreationForm);

    if (isFirstLaunch()) {
        showUserCreationForm();
    } else {
        showLoginPage();
    }
}

/*!
 * \brief Détermine si c'est le premier lancement de l'application.
 * \return true si c'est le premier lancement, sinon false.
 */
bool Application::isFirstLaunch() {
    return userStorage->getUsers().size() == 1;
}

/*!
 * \brief Affiche le formulaire de création d'utilisateur.
 */
void Application::showUserCreationForm() {
    ui->stackedWidget->setCurrentIndex(signInFormIndex);
}

/*!
 * \brief Affiche la page de connexion.
 */
void Application::showLoginPage() {
    ui->stackedWidget->setCurrentIndex(loginFormIndex);
}

/*!
 * \brief Affiche la vue des données utilisateur.
 */
void Application::showUserDataViewPage() {
    ui->stackedWidget->setCurrentIndex(userDataViewIndex);
}

/*!
 * \brief Gère la déconnexion de l'utilisateur.
 *
 * Réinitialise l'utilisateur actuellement connecté et affiche l'écran de connexion.
 */
void Application::handleLogout() {
    loginManager->logout();
    showLoginPage();
}
