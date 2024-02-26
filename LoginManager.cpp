#include "LoginManager.h"
#include <QDebug>

#include "LoginManager.h"

LoginManager::LoginManager(UserStorage *storage) : storage(storage), currentUser("") {
}

bool LoginManager::login(const QString &username, const QString &password) {
    if (storage->validateUser(username, password)) {
        currentUser = username; // Met à jour l'utilisateur connecté
        return true;
    }
    return false;
}

void LoginManager::logout() {
    currentUser = ""; // Réinitialise l'utilisateur connecté
}

