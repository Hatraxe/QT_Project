#ifndef USER_H
#define USER_H

#include <QString>
#include <QList>
#include "UserRights.h"
#include "Profile.h"

class User {
public:
    User(const QString &firstName, const QString &lastName, const QString &username, const QString &password, const UserRights &rights, const QList<Profile*> &profiles);
    User(const User& other);
    ~User();

    // Setters
    void setFirstName(const QString &firstName);
    void setLastName(const QString &lastName);
    void setUsername(const QString &username);
    void setPassword(const QString &password);
    void setRights(const UserRights &rights);
    void setProfiles(const QList<Profile*> &profiles);

    QString getFirstName() const;
    QString getLastName() const;
    QString getPassword() const;
    QString getUsername() const;


    // Other methods
    void addProfile(Profile *profile); // Ajoute un profil à l'utilisateur
    QList<Profile*> getProfiles() const; // Renvoie la liste des profils de l'utilisateur
    UserRights getRights() const; // Renvoie les droits de l'utilisateur

private:
    QString firstName;
    QString lastName;
    QString username;
    QString password;
    QList<Profile*> profiles; // Liste des profils de l'utilisateur
    UserRights rights; // Droits de l'utilisateur
};

#endif // USER_H
