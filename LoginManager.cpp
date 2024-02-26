#include "LoginManager.h"

LoginManager::LoginManager(std::shared_ptr<UserStorage> storage) : storage(std::move(storage)) {
}

bool LoginManager::login(const QString &username, const QString &password) {
    // auto users = storage->getUsers();
    // for (const auto& user : users) {
    //     if (user.getUsername() == username && user.checkPassword(password)) {
    //         // Si le login est réussi, utilisez l'utilisateur existant
    //         currentUser = std::make_shared<User>(user); // Assurez-vous que User a un constructeur de copie si nécessaire
    //         return true;
    //     }
    // }
    return false;
}

void LoginManager::logout() {
    currentUser.reset(); // Réinitialise l'utilisateur actuellement connecté
}

std::shared_ptr<User> LoginManager::getCurrentUser() const {
    return currentUser; // Retourne le pointeur intelligent vers l'utilisateur actuel
}
