#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include "userstorage.h" // Assurez-vous d'inclure UserStorage

class LoginManager {
public:
    LoginManager(UserStorage *storage);
    bool login(const QString &username, const QString &password); // Gère la connexion de l'utilisateur
    void logout(); // Gère la déconnexion de l'utilisateur

private:
    UserStorage *storage; // Référence au stockage des utilisateurs
    // Ajoutez ici des attributs supplémentaires si nécessaire, par exemple, l'utilisateur actuellement connecté
};

#endif // LOGINMANAGER_H
;
