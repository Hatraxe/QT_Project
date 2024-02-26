#include "Application.h"
#include "./ui_application.h"
#include "SignInForm.h"
#include "LoginForm.h"
#include <memory> // Nécessaire pour std::make_unique
using namespace std;




Application::Application(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Application),
    userStorage(std::make_shared<UserStorage>("UserFile.json")) {  //
    loginManager = std::make_unique<LoginManager>(userStorage);
    ui->setupUi(this);
    initializeApplication();
}

Application::~Application() {
    delete ui;  // ui est géré manuellement et doit être supprimé
}

void Application::initializeApplication() {
    // Les objets userStorage et loginManager sont déjà initialisés dans le constructeur

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
    return userStorage->getUsers().size() == 1;
}

void Application::showUserCreationForm() {
    // Trouve l'index de signInForm dans le QStackedWidget
    for(int i = 0; i < ui->stackedWidget->count(); ++i) {
        QWidget* widget = ui->stackedWidget->widget(i);
        if (qobject_cast<SignInForm*>(widget)) {
            ui->stackedWidget->setCurrentIndex(i);
            break;
        }
    }
}

void Application::showLoginPage() {
    // Trouve l'index de loginForm dans le QStackedWidget
    for(int i = 0; i < ui->stackedWidget->count(); ++i) {
        QWidget* widget = ui->stackedWidget->widget(i);
        if (qobject_cast<LoginForm*>(widget)) {
            ui->stackedWidget->setCurrentIndex(i);
            break;
        }
    }
}
