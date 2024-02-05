#include "Application.h"
#include "./ui_application.h" // Assurez-vous que le chemin vers le fichier UI est correct

Application::Application(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Application) {
    ui->setupUi(this);
    userStorage = new UserStorage("C:\\Users\adrie\\Documents\\S8\\TP_PlatLog\\TP_PlatLog\\UserFile.json"); // Initialisez avec le chemin du fichier ou d'autres paramètres si nécessaire
    loginManager = new LoginManager(userStorage);

    initializeApplication();
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
    // Implémentez la logique pour déterminer si c'est le premier lancement
    // Par exemple, vérifiez l'existence du fichier utilisateur ou d'autres indicateurs
    return !userStorage->userFileExists();
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
