#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include <memory>
#include "UserStorage.h"

class LoginManager {
public:
    explicit LoginManager(std::shared_ptr<UserStorage> storage);
    bool login(const QString &username, const QString &password);
    void logout();
    std::shared_ptr<User> getCurrentUser() const;

private:
    std::shared_ptr<UserStorage> storage; // Utilisation de std::shared_ptr pour UserStorage
    std::shared_ptr<User> currentUser; // Utilisation de std::shared_ptr pour User
};

#endif // LOGINMANAGER_H
