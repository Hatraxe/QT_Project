#include "Application.h"
#include "./ui_application.h"
#include "SignInForm.h"  // Assurez-vous d'avoir le bon nom de fichier d'en-tête
#include "LoginForm.h"

Application::Application(QWidget *parent) : QMainWindow(parent), ui(new Ui::Application) {
    ui->setupUi(this);
    // Initialisation de UserStorage et LoginManager
    userStorage = new UserStorage("UserFile.json");
    loginManager = new LoginManager(userStorage);
    // Créez les instances des formulaires
    SignInForm *signInForm = new SignInForm(this);  // Assurez-vous de passer 'this' pour définir le parent et gérer correctement la mémoire
    LoginForm *loginForm = new LoginForm(this);

    // Ajoutez les formulaires au QStackedWidget
    ui->stackedWidget->addWidget(signInForm);
    ui->stackedWidget->addWidget(loginForm);

    // Affiche le formulaire approprié en fonction du premier lancement
    if (isFirstLaunch()) {
        ui->stackedWidget->setCurrentWidget(signInForm);
    } else {
        ui->stackedWidget->setCurrentWidget(loginForm);
    }
}

Application::~Application() {
    delete ui;
    // Assurez-vous que userStorage et loginManager sont correctement initialisés avant d'être utilisés
    // Si ce ne sont pas des objets dynamiques, ils n'ont pas besoin d'être supprimés avec delete.
    // delete userStorage;
    // delete loginManager;
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
    // Assurez-vous que userStorage est correctement initialisé avant d'être utilisé
    // Si userStorage est un pointeur, assurez-vous qu'il pointe vers un objet valide.
    // return !userStorage->nonSuperUserExists();

   return !userStorage->nonSuperUserExists(); // Remplacez cette logique par votre vérification réelle
}

void Application::showUserCreationForm() {
    // Implémentez la logique pour afficher le formulaire de création d'utilisateur
    // Ceci peut impliquer de changer de widget ou de fenêtre affichée
    // Exemple : ui->stackedWidget->setCurrentWidget(INDEX_DU_FORMULAIRE_CREATION);

}

void Application::showLoginPage() {
    // Implémentez la logique pour afficher la page de connexion
    // Ceci peut impliquer de changer de widget ou de fenêtre affichée
    // Exemple : ui->stackedWidget->setCurrentWidget(INDEX_DE_LA_PAGE_CONNEXION);
}
