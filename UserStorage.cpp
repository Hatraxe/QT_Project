#include "UserStorage.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QIODevice>
#include <QStandardPaths>
#include <QCryptographicHash>



UserStorage::UserStorage(const QString &filename) : filename(filename) {
    userFilePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/" + filename;
    initializeStorage();
}

bool UserStorage::userFileExists() {
    return QFile::exists(userFilePath);
}

bool UserStorage::userExists(const QString &username) {
    QFile file(userFilePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject root = doc.object();
    QJsonArray users = root["users"].toArray();

    for (const QJsonValue &value : users) {
        QJsonObject user = value.toObject();
        // Ignorer le super utilisateur dans cette vérification
        if (user["username"].toString() == username && username != "superuser") {
            return true;
        }
    }

    return false;
}

void UserStorage::saveUser(const QString &username, const QString &password) {
    QFile file(userFilePath);
    QJsonDocument doc;
    QJsonObject root;
    if (file.open(QIODevice::ReadOnly)) {
        doc = QJsonDocument::fromJson(file.readAll());
        root = doc.object();
        file.close();
    }

    // Hasher le mot de passe avant de l'enregistrer
    QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);

    QJsonArray users = root["users"].toArray();
    QJsonObject newUser;
    newUser["username"] = username;
    newUser["password"] = QString(hashedPassword.toHex()); // Stocker le hash sous forme hexadécimale
    users.append(newUser);
    root["users"] = users;
    doc.setObject(root);

    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    }
}


bool UserStorage::validateUser(const QString &username, const QString &password) {
    QFile file(userFilePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject root = doc.object();
    QJsonArray users = root["users"].toArray();

    QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    QString hashedPasswordHex = QString(hashedPassword.toHex());

    for (const QJsonValue &value : users) {
        QJsonObject user = value.toObject();
        if (user["username"].toString() == username && user["password"].toString() == hashedPasswordHex) {
            return true;
        }
    }

    return false;
}

// Méthode pour initialiser le stockage
void UserStorage::initializeStorage() {
    if (!userFileExists()) {
        // Créer le fichier et ajouter le super utilisateur
        QFile file(userFilePath);
        if (file.open(QIODevice::WriteOnly)) {
            QJsonObject root;
            QJsonArray users;

            // Créer le super utilisateur
            QJsonObject superUser;
            superUser["username"] = "superuser";
            QByteArray hashedPassword = QCryptographicHash::hash(QString("Password1!").toUtf8(), QCryptographicHash::Sha256);
            superUser["password"] = QString(hashedPassword.toHex());
            users.append(superUser);

            // Ajouter d'autres initialisations ici si nécessaire

            root["users"] = users;
            QJsonDocument doc(root);
            file.write(doc.toJson());
            file.close();
        }
    }
}

bool UserStorage::nonSuperUserExists() {
    QFile file(userFilePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject root = doc.object();
    QJsonArray users = root["users"].toArray();

    for (const QJsonValue &userVal : users) {
        QJsonObject user = userVal.toObject();
        if (user["username"].toString() != "superuser") {
            return true; // Un utilisateur autre que le super utilisateur a été trouvé
        }
    }

    return false; // Aucun utilisateur autre que le super utilisateur n'a été trouvé
}


