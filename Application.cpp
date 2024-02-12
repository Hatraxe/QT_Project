#include "Application.h"
#include "./ui_application.h"
#include "signinform.h"
#include "loginform.h"

Application::Application(QWidget *parent) : QMainWindow(parent), ui(new Ui::Application) {
    ui->setupUi(this);

    // Créez les instances des formulaires
    auto signInForm = new SignInForm(this); // Assurez-vous de passer 'this' pour définir le parent et gérer correctement la mémoire
    auto loginForm = new LoginForm(this);

    // Ajoutez les formulaires au QStackedWidget
    ui->stackedWidget->addWidget(signInForm);
    ui->stackedWidget->addWidget(loginForm);

    // Optionnellement, définissez le widget à afficher en premier
    if (isFirstLaunch()) {
        ui->stackedWidget->setCurrentWidget(signInForm);
    } else {
        ui->stackedWidget->setCurrentWidget(loginForm);
    }
}

Application::~Application() {
    delete ui;
    delete userStorage;
    delete loginManager;
}

void Application::initializeApplication() {
    if (isFirstLaunch()) {
        showUserCreationForm();
    } else {
        showLoginPage();
    }
}

bool Application::isFirstLaunch() {
    // Vérifie si un utilisateur autre que le super utilisateur existe
    return !userStorage->nonSuperUserExists();
}

void Application::showUserCreationForm() {
    // Implémentez la logique pour afficher le formulaire de création d'utilisateur
    // Ceci peut impliquer de changer de widget ou de fenêtre affichée
    // Exemple : ui->stackedWidget->setCurrentIndex(INDEX_DU_FORMULAIRE_CREATION);
}

void Application::showLoginPage() {
    // Implémentez la logique pour afficher la page de connexion
    // Ceci peut impliquer de changer de widget ou de fenêtre affichée
    // Exemple : ui->stackedWidget->setCurrentIndex(INDEX_DE_LA_PAGE_CONNEXION);
}
