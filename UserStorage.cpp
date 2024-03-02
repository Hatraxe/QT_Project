/*!
 * \file UserStorage.cpp
 * \brief Implémentation de la classe UserStorage.
 *
 * Fournit l'implémentation des méthodes pour gérer le stockage, la validation,
 * et la récupération des utilisateurs.
 */

#include "UserStorage.h"
#include "UserSerializer.h"
#include "UserDeserializer.h"

/*!
 * \brief Constructeur de UserStorage qui initialise le stockage des utilisateurs.
 *
 * Charge les utilisateurs existants à partir d'un fichier JSON spécifié ou crée un fichier
 * s'il n'existe pas. Prépare le système de stockage pour gérer les utilisateurs.
 */
UserStorage::UserStorage() {
    // Obtenir le chemin vers le dossier contenant l'exécutable de l'application
    QString appFolderPath = QCoreApplication::applicationDirPath();

    // Construire le chemin complet vers le dossier des données de l'application
    QString dataFolderPath = QDir(appFolderPath).filePath("AppData");

    // Créer le dossier s'il n'existe pas
    QDir dataFolder(dataFolderPath);
    if (!dataFolder.exists()) {
        dataFolder.mkpath(".");
    }

    // Construire le chemin complet vers le fichier des utilisateurs
    userFilePath = dataFolder.filePath("UserFile.json");

    // Vérifier si le fichier UserFile.json existe
    QFile userFile(userFilePath);
    if (!userFile.exists()) {
        // Hasher le mot de passe "password"
        QString password = "password";
        QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);

        // Définir le super utilisateur
        QJsonObject superUser;
        superUser["firstname"] = "Super";
        superUser["lastname"] = "User";
        superUser["username"] = "superuser";
        superUser["password"] = QString(hashedPassword.toHex());
        superUser["email"] = "superuser@example.com";

        // Définir les droits du super utilisateur
        QJsonObject rights;
        rights["canView"] = true;
        rights["canEdit"] = true;
        rights["isAdmin"] = true;
        superUser["rights"] = rights;

        // Ajouter le super utilisateur à un tableau d'utilisateurs
        QJsonArray usersArray;
        usersArray.append(superUser);

        // Créer l'objet JSON racine
        QJsonObject rootObj;
        rootObj["users"] = usersArray;

        // Écrire l'objet JSON dans le fichier
        if (userFile.open(QIODevice::WriteOnly)) {
            QJsonDocument doc(rootObj);
            userFile.write(doc.toJson());
            userFile.close();
        }
    }

    // Désérialiser les utilisateurs existants dans le fichier
    users = UserDeserializer::deserializeFromFile(userFilePath);
}



/*!
 * \brief Enregistre un nouvel utilisateur dans le système de stockage.
 *
 * \param user L'utilisateur à enregistrer.
 *
 * Ajoute l'utilisateur à la liste si celui-ci n'existe pas déjà. Sérialise ensuite la liste
 * mise à jour des utilisateurs dans le fichier JSON.
 */
void UserStorage::saveUser(const User& user) {
    // Logique pour ajouter ou mettre à jour un utilisateur

    // Vérifie si l'utilisateur existe déjà dans la liste
    auto it = std::find_if(users.begin(), users.end(), [&user](const User& u) {
        return u.getUsername() == user.getUsername();
    });

    // Si l'utilisateur n'existe pas, ajoute à la liste
    if (it == users.end()) {
        users.append(user);
    }
    UserSerializer::serializeToFile(users, userFilePath);
}

/*!
 * \brief Valide les informations de connexion d'un utilisateur.
 *
 * \param username Le nom d'utilisateur.
 * \param password Le mot de passe.
 * \return True si les informations de connexion sont valides, sinon False.
 *
 * Compare le nom d'utilisateur et le mot de passe (après hashage) avec les données
 * des utilisateurs chargés pour valider les informations de connexion.
 */
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

        userFilePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + QDir::separator() + filename;

        users = UserDeserializer::deserializeFromFile(userFilePath);
    }
}


void UserStorage::setUserFilePath(const QString &newUserFilePath) {
    if (userFilePath != newUserFilePath) {
        userFilePath = newUserFilePath;

    }
}

void UserStorage::setUsers(const QList<User> &newUsers) {
    users = newUsers;

}
