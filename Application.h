/*!
 * \file Application.h
 * \brief Définition de la classe Application qui gère la fenêtre principale de l'application.
 * \author AMOROSO Adrien / SOULIER Louis
 * \version 1.0
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMainWindow>
#include <memory>
#include "UserStorage.h"
#include "LoginManager.h"

// Forward declaration du namespace Ui
namespace Ui {
class Application;
}

/*!
 * \class Application
 * \brief La classe Application représente la fenêtre principale de l'application.
 *
 * Cette classe gère la navigation entre les différentes vues de l'application et détient les instances
 * principales de gestion des utilisateurs et de la connexion.
 */
class Application : public QMainWindow {
    Q_OBJECT

public:
    /*!
     * \brief Constructeur de la classe Application.
     * \param parent Le widget parent de cette fenêtre principale.
     */
    explicit Application(QWidget *parent = nullptr);

    /*!
     * \brief Destructeur de la classe Application.
     */
    ~Application() override;

    /*!
     * \brief Accesseur pour obtenir le gestionnaire de stockage des utilisateurs.
     * \return Un pointeur partagé vers l'instance de UserStorage.
     */
    std::shared_ptr<UserStorage> getUserStorage() const { return userStorage; }

private:
    Ui::Application *ui;  ///< Pointeur vers l'interface utilisateur générée par uic.
    std::shared_ptr<UserStorage> userStorage;  ///< Gestionnaire de stockage des utilisateurs.
    std::shared_ptr<LoginManager> loginManager;  ///< Gestionnaire de la connexion des utilisateurs.
    int signInFormIndex;  ///< Index du formulaire d'inscription dans le QStackedWidget.
    int loginFormIndex;  ///< Index du formulaire de connexion dans le QStackedWidget.
    int userDataViewIndex;  ///< Index de la vue des données utilisateur dans le QStackedWidget.

    /*!
     * \brief Initialise l'application, notamment les vues et les gestionnaires.
     */
    void initializeApplication();

    /*!
     * \brief Détermine si c'est le premier lancement de l'application.
     * \return true si c'est le premier lancement, false sinon.
     */
    bool isFirstLaunch();

private slots:
    /*!
     * \brief Affiche la page de connexion.
     */
    void showLoginPage();

    /*!
     * \brief Affiche le formulaire de création de l'utilisateur.
     */
    void showUserCreationForm();

    /*!
     * \brief Affiche la vue des données utilisateur.
     */
    void showUserDataViewPage();

    /*!
     * \brief Gère la demande de déconnexion de l'utilisateur.
     */
    void handleLogout();
};

#endif // APPLICATION_H
