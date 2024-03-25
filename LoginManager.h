/*!
 * \file LoginManager.h
 * \brief Définition de la classe LoginManager qui gère la session d'un utilisateur.
 *
 * LoginManager offre des fonctionnalités pour connecter un utilisateur à l'application,
 * le déconnecter et accéder à l'utilisateur actuellement connecté.
 */

#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include <memory>
#include "UserStorage.h"
#include "User.h"

/*!
 * \class LoginManager
 * \brief Gère les opérations de connexion et de déconnexion des utilisateurs.
 *
 * Cette classe utilise UserStorage pour vérifier les informations d'identification
 * des utilisateurs lors de la tentative de connexion et maintient une référence
 * à l'utilisateur actuellement connecté.
 */
class LoginManager {
public:
    /*!
     * \brief Constructeur de LoginManager.
     * \param storage Un pointeur partagé vers UserStorage utilisé pour accéder aux données des utilisateurs.
     */
    explicit LoginManager(std::shared_ptr<UserStorage> storage);

    /*!
     * \brief Tente de connecter un utilisateur avec le nom d'utilisateur et le mot de passe fournis.
     * \param username Le nom d'utilisateur.
     * \param password Le mot de passe.
     * \return bool Retourne vrai si la connexion est réussie, faux sinon.
     */
    bool login(const QString &username, const QString &password);

    /*!
     * \brief Déconnecte l'utilisateur actuellement connecté.
     */
    void logout();

    /*!
     * \brief Renvoie l'utilisateur actuellement connecté.
     * \return Un pointeur partagé vers l'utilisateur actuellement connecté, ou nullptr si aucun utilisateur n'est connecté.
     */
    std::shared_ptr<User> getCurrentUser() const;

private:
    std::shared_ptr<UserStorage> storage; ///< Stockage des utilisateurs pour vérifier les informations d'identification.
    std::shared_ptr<User> currentUser; ///< Utilisateur actuellement connecté.
};

#endif // LOGINMANAGER_H
