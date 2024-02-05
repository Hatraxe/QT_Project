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
        if (user["username"].toString() == username) {
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

