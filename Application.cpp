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

    // Initialisation de UserStorage et LoginManager
    userStorage = new UserStorage("UserFile.json");
    loginManager = new LoginManager(userStorage);

    // Initialisation des formulaires
    auto signInForm = new SignInForm(this); // 'this' assure la gestion automatique de la mémoire
    auto loginForm = new LoginForm(this);

    ui->stackedWidget->addWidget(signInForm);
    ui->stackedWidget->addWidget(loginForm);

    // Affiche le formulaire approprié en fonction du premier lancement
    if (isFirstLaunch()) {
        showUserCreationForm();
    } else {
        showLoginPage();
    }
}

bool Application::isFirstLaunch() {
    return !userStorage->nonSuperUserExists();
}

void Application::showUserCreationForm() {
    // Trouvez l'index de signInForm dans le QStackedWidget
    for(int i = 0; i < ui->stackedWidget->count(); ++i) {
        QWidget* widget = ui->stackedWidget->widget(i);
        if (qobject_cast<SignInForm*>(widget)) {
            ui->stackedWidget->setCurrentIndex(i);
            break;
        }
    }
}

void Application::showLoginPage() {
    // Trouvez l'index de loginForm dans le QStackedWidget
    for(int i = 0; i < ui->stackedWidget->count(); ++i) {
        QWidget* widget = ui->stackedWidget->widget(i);
        if (qobject_cast<LoginForm*>(widget)) {
            ui->stackedWidget->setCurrentIndex(i);
            break;
        }
    }
}
