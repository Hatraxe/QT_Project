#include "UserStorage.h"
#include "UserSerializer.h"
#include "userdeserializer.h"
#include <QCryptographicHash>
#include <QFile>
#include <QStandardPaths>
#include <QDir>
#include <QCoreApplication>

UserStorage::UserStorage(const QString &filename) : filename(filename) {
    // Construire le chemin complet vers le fichier des utilisateurs
    //userFilePath = QCoreApplication::applicationDirPath() + QDir::separator() + "UserFile.json";
    userFilePath = "C:\\Users\\adrie\\Documents\\S8\\TP_PlatLog\\TP_PlatLog\\UserFile.json";


    // Crée le répertoire s'il n'existe pas
    QDir dir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    // Désérialise les utilisateurs existants dans le fichier
    users = UserDeserializer::deserializeFromFile(userFilePath);

    // Si la liste est vide, ajouter un super utilisateur ici
    // ou de il faut alors gérer ce cas autrement
}

void UserStorage::saveUser(const User& user) {
    // Vérifie si l'utilisateur existe déjà dans la liste
    auto it = std::find_if(users.begin(), users.end(), [&user](const User& u) {
        return u.getUsername() == user.getUsername();
    });

    // Si l'utilisateur n'existe pas, ajoute à la liste
    if (it == users.end()) {
        users.append(user);
    } else {
        // Optionnel: Mettre à jour l'utilisateur existant ou gérer l'erreur
    }

    // Sérialise la liste mise à jour des utilisateurs dans le fichier JSON
    UserSerializer::serializeToFile(users, userFilePath);
}

bool UserStorage::validateUser(const QString &username, const QString &password) {
    QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    QString hashedPasswordHex = QString(hashedPassword.toHex());

    for (const User& user : users) {
        if (user.getUsername() == username && user.getPassword() == hashedPasswordHex) {
            return true;
        }
    }
    return false;
}


// Getters
QString UserStorage::getFilename() const {
    return filename;
}

QString UserStorage::getUserFilePath() const {
    return userFilePath;
}

QList<User> UserStorage::getUsers() const {
    return users;
}

// Setters
void UserStorage::setFilename(const QString &newFilename) {
    if (filename != newFilename) {
        filename = newFilename;
        // Mettre à jour le chemin complet du fichier basé sur le nouveau nom de fichier
        userFilePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + QDir::separator() + filename;

        // Recharger les utilisateurs à partir du nouveau fichier
        users = UserDeserializer::deserializeFromFile(userFilePath);
    }
}


void UserStorage::setUserFilePath(const QString &newUserFilePath) {
    if (userFilePath != newUserFilePath) {
        userFilePath = newUserFilePath;
        // De même, vous pouvez choisir de recharger les utilisateurs ici
    }
}

void UserStorage::setUsers(const QList<User> &newUsers) {
    users = newUsers;
    // Notez que cela remplacera la liste des utilisateurs en mémoire. Assurez-vous que c'est l'intention.
}
