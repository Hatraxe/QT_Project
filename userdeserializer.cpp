// UserDeserializer.cpp
#include "UserDeserializer.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QCoreApplication>

QList<User> UserDeserializer::deserializeFromFile(const QString& filename) {
    QList<User> users;
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file:" << filename;
        return users; // Retourne une liste vide si le fichier ne peut pas être ouvert
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonArray usersArray = doc.object().value("users").toArray();
    file.close();

    for (const QJsonValue &userVal : usersArray) {
        QJsonObject userObject = userVal.toObject();
        QString firstName = userObject["firstname"].toString();
        QString lastName = userObject["lastname"].toString();
        QString username = userObject["username"].toString();
        QString password = userObject["password"].toString(); // Le mot de passe est supposé être déjà haché

        QJsonObject rightsObject = userObject["rights"].toObject();
        UserRights rights(
            rightsObject["canView"].toBool(),
            rightsObject["canEdit"].toBool(),
            rightsObject["isAdmin"].toBool()
            );

        QList<Profile*> profiles;
        QJsonArray profilesArray = userObject["profiles"].toArray();
        for (const QJsonValue &profileVal : profilesArray) {
            profiles.append(new Profile(profileVal.toString()));
        }

        users.append(User(firstName, lastName, username, password, rights, profiles));
    }

    return users;
}
