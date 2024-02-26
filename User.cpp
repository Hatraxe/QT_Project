#include "User.h"
#include "UserRights.h"
#include "Profile.h"

// Constructeur
User::User(const QString &firstName, const QString &lastName, const QString &username,
           const QString &password, const UserRights &rights, const QList<Profile*> &profiles)
    : firstName(firstName), lastName(lastName), username(username),
    password(password), rights(rights), profiles(profiles) {}

User::User(const User& other)
    : firstName(other.firstName), lastName(other.lastName),
    username(other.username), password(other.password),
    rights(other.rights) {
    // Copie profonde des profils
    for (Profile* profile : other.profiles) {
        profiles.append(new Profile(*profile)); // Supposons que Profile a un constructeur de copie
    }
}


// Destructeur
User::~User() {
    qDeleteAll(profiles); // Supprime tous les profils de la liste et libère la mémoire
    profiles.clear(); // Assurez-vous que la liste est vide après la suppression
}

// Setter pour firstName
void User::setFirstName(const QString &firstName) {
    this->firstName = firstName;
}

// Setter pour lastName
void User::setLastName(const QString &lastName) {
    this->lastName = lastName;
}

// Setter pour username
void User::setUsername(const QString &username) {
    this->username = username;
}

// Setter pour password
void User::setPassword(const QString &password) {
    this->password = password;
}

// Setter pour rights
void User::setRights(const UserRights &rights) {
    this->rights = rights;
}

// Setter pour profiles
void User::setProfiles(const QList<Profile*> &profiles) {
    this->profiles = profiles;
}

// Ajoute un profil à l'utilisateur
void User::addProfile(Profile *profile) {
    if (profile != nullptr && !this->profiles.contains(profile)) {
        this->profiles.append(profile);
    }
}

// Renvoie la liste des profils de l'utilisateur
QList<Profile*> User::getProfiles() const {
    return profiles;
}

// Renvoie les droits de l'utilisateur
UserRights User::getRights() const {
    return rights;

}


QString User::getFirstName() const {
    return firstName;
}

QString User::getLastName() const {
    return lastName;
}

QString User::getUsername() const {
    return username;
}

QString User::getPassword() const {
    return password;
}
