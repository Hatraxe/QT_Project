#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include "userstorage.h"

#include <QString>

class LoginManager {
public:
    LoginManager(UserStorage *storage);
    bool login(const QString &username, const QString &password);
    void logout();

private:
    UserStorage *storage;
    QString currentUser; // Nom d'utilisateur de l'utilisateur actuellement connecté
};


#endif // LOGINMANAGER_H
;
