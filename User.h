/*!
 * \file User.h
 * \brief Définition de la classe User qui représente un utilisateur de l'application.
 *
 * La classe User stocke les informations d'un utilisateur, y compris ses droits, profils et informations personnelles.
 */

#ifndef USER_H
#define USER_H

#include <QString>
#include <QList>
#include <QCryptographicHash>

#include "UserRights.h"
#include "Profile.h"

/*!
 * \class User
 * \brief Classe représentant un utilisateur.
 *
 * Stocke les informations d'un utilisateur, gère les profils associés et les droits d'accès.
 */
class User {
public:
    /*!
     * \brief Constructeur complet de User.
     * \param firstName Prénom de l'utilisateur.
     * \param lastName Nom de famille de l'utilisateur.
     * \param username Nom d'utilisateur.
     * \param password Mot de passe (non haché).
     * \param rights Droits de l'utilisateur.
     * \param profiles Liste des profils associés à l'utilisateur.
     */
    User(const QString &firstName, const QString &lastName, const QString &username, const QString &password, const UserRights &rights, const QList<Profile*> &profiles);

    /*!
     * \brief Constructeur de copie.
     * \param other L'objet User à copier.
     */
    User(const User& other);

    /*!
     * \brief Constructeur alternatif sans droits spécifiés.
     * \param firstName Prénom de l'utilisateur.
     * \param lastName Nom de famille de l'utilisateur.
     * \param username Nom d'utilisateur.
     * \param password Mot de passe (non haché).
     * \param profiles Liste des profils associés à l'utilisateur.
     */
    User(const QString &firstName, const QString &lastName, const QString &username, const QString &password, const QList<Profile*> &profiles);

    /*!
     * \brief Destructeur de User.
     */
    ~User();

    // Setters
    void setFirstName(const QString &firstName);
    void setLastName(const QString &lastName);
    void setUsername(const QString &username);
    void setPassword(const QString &password);
    void setRights(const UserRights &rights);
    void setProfiles(const QList<Profile*> &profiles);
    void addProfile(Profile *profile); // Ajoute un profil à l'utilisateur
    void setCurrentProfile(Profile *profile); // Définit le profil courant de l'utilisateur

    // Getters
    QString getFirstName() const;
    QString getLastName() const;
    QString getPassword() const;
    QString getUsername() const;
    QString getMail() const;
    QList<Profile*> getProfiles() const;
    UserRights getRights() const;
    Profile* getCurrentProfile() const;

    /*!
     * \brief Vérifie si le mot de passe fourni correspond au mot de passe de l'utilisateur.
     * \param password Le mot de passe à vérifier.
     * \return true si le mot de passe correspond, false sinon.
     */
    bool checkPassword(const QString &password) const;

private:
    QString firstName;
    QString lastName;
    QString username;
    QString password; // Devrait être stocké de manière sécurisée
    QList<Profile*> profiles; // Liste des profils de l'utilisateur
    UserRights rights; // Droits de l'utilisateur
    Profile *currentProfile; // Profil courant de l'utilisateur
};

#endif // USER_H
