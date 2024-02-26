#ifndef USERSTORAGE_H
#define USERSTORAGE_H

#include <QString>
#include "User.h"

class UserStorage {
public:
    UserStorage(const QString &filename);
    void saveUser(const User& user); // Enregistre un nouvel utilisateur
    bool validateUser(const QString &username, const QString &password); // Valide les informations de connexion

    // Getters
    QString getFilename() const;
    QString getUserFilePath() const;
    QList<User> getUsers() const;

    // Setters
    void setFilename(const QString &filename);
    void setUserFilePath(const QString &userFilePath);
    void setUsers(const QList<User> &users);


private:
    QString filename; // Nom du fichier pour stocker les utilisateurs
    QString userFilePath; // Chemin complet vers le fichier des utilisateurs
    QList<User> users; // Liste des utilisateurs chargés
};

#endif // USERSTORAGE_H
