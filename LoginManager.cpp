/*!
 * \file LoginManager.cpp
 * \brief Implémentation de la classe LoginManager.
 */

#include "LoginManager.h"

/*!
 * \brief Constructeur de la classe LoginManager.
 * \param storage Le stockage des utilisateurs pour vérifier les informations d'identification lors de la connexion.
 *
 * Initialise le gestionnaire de connexion avec un stockage d'utilisateurs donné.
 */
LoginManager::LoginManager(std::shared_ptr<UserStorage> storage) : storage(std::move(storage)) {
}

/*!
 * \brief Tente de connecter un utilisateur avec un nom d'utilisateur et un mot de passe donnés.
 * \param username Le nom d'utilisateur pour la tentative de connexion.
 * \param password Le mot de passe pour la tentative de connexion.
 * \return bool Retourne vrai si la connexion est réussie, sinon faux.
 *
 * Parcourt la liste des utilisateurs stockés pour trouver une correspondance avec les informations d'identification fournies.
 * Si une correspondance est trouvée, l'utilisateur est considéré comme connecté et stocké comme l'utilisateur actuel.
 */
bool LoginManager::login(const QString &username, const QString &password) {
    auto users = storage->getUsers();
    for (const auto& user : users) {


        if (user.getUsername() == username && user.checkPassword(password)) {
            currentUser = std::make_shared<User>(user);
            return true;
        }

    }
    return false;
}

/*!
 * \brief Déconnecte l'utilisateur actuellement connecté.
 *
 * Réinitialise le pointeur intelligent de l'utilisateur actuellement connecté, le mettant à nullptr.
 */
void LoginManager::logout() {
    currentUser.reset(); // Réinitialise l'utilisateur actuellement connecté
}

/*!
 * \brief Obtient l'utilisateur actuellement connecté.
 * \return std::shared_ptr<User> Le pointeur intelligent vers l'utilisateur actuellement connecté, ou nullptr si aucun utilisateur n'est connecté.
 *
 * Retourne un pointeur intelligent vers l'utilisateur actuellement connecté si celui-ci existe, sinon retourne nullptr.
 */
std::shared_ptr<User> LoginManager::getCurrentUser() const {
    return currentUser; // Retourne le pointeur intelligent vers l'utilisateur actuel
}
