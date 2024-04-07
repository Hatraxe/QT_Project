/*!
 * \file UserDataView.h
 * \brief Définition de la classe UserDataView pour l'affichage des informations de l'utilisateur.
 *
 * UserDataView offre une interface utilisateur pour afficher et gérer les informations
 * de l'utilisateur connecté, telles que le changement de profil, de mot de passe, et la déconnexion.
 */

#ifndef USERDATAVIEW_H
#define USERDATAVIEW_H

#include <QWidget>
#include <QMessageBox>
#include <memory>
#include "LoginManager.h"
#include "DatabaseManager.h"

/*!
 * Espace de noms Ui. Utilisé par le système UIC de Qt pour gérer l'interface utilisateur.
 */
namespace Ui {
class UserDataView;
}

/*!
 * \class UserDataView
 * \brief Classe représentant la vue des données de l'utilisateur.
 *
 * Fournit une interface graphique pour afficher les informations de l'utilisateur connecté
 * et permettre certaines actions comme la déconnexion ou le changement de profil.
 */
class UserDataView : public QWidget {
    Q_OBJECT

public:
    /*!
     * \brief Constructeur de UserDataView.
     * \param parent Le widget parent de cette vue.
     * \param loginManager Le gestionnaire de connexion pour accéder aux informations de l'utilisateur connecté.
     *
     * Initialise une nouvelle vue pour afficher les informations de l'utilisateur connecté.
     */
    explicit UserDataView(QWidget *parent, std::shared_ptr<LoginManager> loginManager);

    /*!
     * \brief Destructeur de UserDataView.
     *
     * Nettoie les ressources utilisées par la vue.
     */
    ~UserDataView();

    /*!
     * \brief Rafraîchit les informations affichées de l'utilisateur.
     *
     * Met à jour l'interface avec les informations actuelles de l'utilisateur connecté.
     */
    void refreshUserInfos();


    void setDatabaseManager(std::shared_ptr<DatabaseManager> dbManager);

    bool isValidQuery(const QString& query, const UserRights& rights);




signals:
    /*!
     * \brief Signal émis lorsque l'utilisateur demande à se déconnecter.
     */
    void logoutRequested();

private slots:
    /*!
     * \brief Gère le clic sur le bouton de changement de profil.
     */
    void changeProfilClic();

    /*!
     * \brief Gère le clic sur le bouton de déconnexion.
     */
    void deconnexionClic();

    /*!
     * \brief Gère le clic sur le bouton de changement de mot de passe.
     */
    void changePasswordClic();

    /*!
     * \brief Gère le clic sur le bouton "OK" pour confirmer une action.
     */
    void okClic();



    void ajouterClic();
    void supprimerClic();
    void executerClic();
    void indexComboBoxBddChanged(int index);
    void displayTableContent(const QString &tableName);


private:
    Ui::UserDataView *ui; ///< Pointeur vers l'interface utilisateur générée par UIC.
    std::shared_ptr<LoginManager> loginManager; ///< Gestionnaire de connexion pour accéder à l'utilisateur connecté.
    std::shared_ptr<DatabaseManager> databaseManager; // Gère les interactions avec les bases de données
    void refreshDatabasesList(); // Met à jour la liste des bases de données disponibles
    void refreshTablesList(); // Met à jour la liste des tables pour la base de données sélectionnée
};

#endif // USERDATAVIEW_H
