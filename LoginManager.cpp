#include "LoginManager.h"
#include <QDebug>

LoginManager::LoginManager(UserStorage *storage)
    : storage(storage) {
}

bool LoginManager::login(const QString &username, const QString &password) {
    // Ici, vous implémenteriez la logique pour vérifier si les informations d'identification fournies sont correctes.
    // Cela pourrait impliquer de vérifier les informations d'identification contre les données stockées dans `storage`.
    if (storage->validateUser(username, password)) {
        qDebug() << "Connexion réussie pour l'utilisateur :" << username;
        // Vous pourriez également ici définir l'utilisateur comme étant "connecté" dans un attribut de classe.
        return true;
    } else {
        qDebug() << "Échec de la connexion pour l'utilisateur :" << username;
        return false;
    }
}

void LoginManager::logout() {
    // Ici, vous implémenteriez la logique pour déconnecter l'utilisateur.
    // Cela pourrait simplement réinitialiser l'état de l'utilisateur actuellement connecté.
    qDebug() << "Utilisateur déconnecté.";
    // Réinitialiser l'état de connexion ici
}
