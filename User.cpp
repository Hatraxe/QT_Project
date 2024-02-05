#include "user.h"

User::User(const QString &username, const QString &password)
    : username(username), password(password), rights(UserRights(false, false, false)) {
    // Initialisez rights avec des valeurs par défaut, par exemple sans droits.
    // Vous pouvez ajuster ces valeurs par défaut selon les besoins de votre application.
}

User::~User() {
    // Nettoyez la liste des profils si nécessaire. Par exemple :
    qDeleteAll(profiles);
    profiles.clear();
}

void User::addProfile(Profile *profile) {
    if (profile != nullptr) {
        profiles.append(profile);
    }
}

QList<Profile*> User::getProfiles() const {
    return profiles;
}

UserRights User::getRights() const {
    return rights;
}
