#ifndef USER_H
#define USER_H

#include <QString>
#include <QList>
#include "profile.h"
#include "userrights.h"

class User {
public:
    User(const QString &username, const QString &password, const UserRights &rights);
    ~User();

    void addProfile(Profile *profile); // Ajoute un profil à l'utilisateur
    QList<Profile*> getProfiles() const; // Renvoie la liste des profils de l'utilisateur
    UserRights getRights() const; // Renvoie les droits de l'utilisateur

private:
    QString username;
    QString password;
    QList<Profile*> profiles; // Liste des profils de l'utilisateur
    UserRights rights; // Droits de l'utilisateur
};

#endif // USER_H
