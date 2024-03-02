/*!
 * \file User.cpp
 * \brief Implémentation de la classe User.
 *
 * Définit le comportement des utilisateurs, y compris la gestion des profils et des droits d'accès.
 */

#include "User.h"

/*!
 * \brief Constructeur complet de User.
 */
User::User(const QString &firstName, const QString &lastName, const QString &username,
           const QString &password, const UserRights &rights, const QList<Profile*> &profiles)
    : firstName(firstName), lastName(lastName), username(username),
    password(password), rights(rights), profiles(profiles) {}

/*!
 * \brief Constructeur alternatif de User sans droits spécifiés.
 */
User::User(const QString &firstName, const QString &lastName, const QString &username,
           const QString &password, const QList<Profile*> &profiles)
    : firstName(firstName), lastName(lastName), username(username),
    password(password), rights(), profiles(profiles) {}

/*!
 * \brief Constructeur de copie de User.
 */
User::User(const User& other)
    : firstName(other.firstName), lastName(other.lastName),
    username(other.username), password(other.password),
    rights(other.rights), profiles() {
    for (Profile* profile : other.profiles) {
        profiles.append(new Profile(*profile));
    }
}

/*!
 * \brief Destructeur de User.
 */
User::~User() {
    qDeleteAll(profiles);
    profiles.clear();
}

/*!
 * \brief Vérifie si le mot de passe fourni correspond au mot de passe de l'utilisateur.
 */
bool User::checkPassword(const QString &password) const {
    // Hash le mot de passe fourni en utilisant le même algorithme que lors de la création du mot de passe
    QByteArray hashedInputPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);

    // Compare le mot de passe hashé avec le mot de passe hashé stocké
    return QString::compare(QString(hashedInputPassword.toHex()), this->password) == 0;
}



/*!
 * \brief Ajoute un profil à l'utilisateur.
 */
void User::addProfile(Profile *profile) {
    if (profile && !profiles.contains(profile)) {
        profiles.append(profile);
    }
}

/*!
 * \brief Définit le profil courant de l'utilisateur.
 */
void User::setCurrentProfile(Profile *profile) {
    currentProfile = profile;
}

// Getter pour currentProfile
Profile* User::getCurrentProfile() const {
    return this->currentProfile;
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
QString User::getMail() const {
    return username;
}

