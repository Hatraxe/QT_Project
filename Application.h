#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>
#include "userstorage.h" // Assurez-vous d'inclure ou de définir cette classe
#include "loginmanager.h" // Assurez-vous d'inclure ou de définir cette classe

namespace Ui {
class Application;
}

class Application : public QMainWindow
{
    Q_OBJECT

public:
    explicit Application(QWidget *parent = nullptr);
    ~Application();

private slots:
    void on_page_customContextMenuRequested(const QPoint &pos);

private:
    Ui::Application *ui;
    UserStorage *userStorage; // Gestion des données utilisateur
    LoginManager *loginManager; // Gestion de la connexion/déconnexion

    void initializeApplication(); // Initialisation de l'application
    bool isFirstLaunch(); // Vérifier si c'est le premier lancement
    void showUserCreationForm(); // Afficher le formulaire de création d'utilisateur
    void showLoginPage(); // Afficher la page de connexion
};

#endif // APPLICATION_H
