#include "user.h"

User::User(const QString &firstName,const QString &lastName,const QString &username, const QString &password, const UserRights &rights)
    : firstName(firstName),lastName(lastName),username(username), password(password), rights(rights) {
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
