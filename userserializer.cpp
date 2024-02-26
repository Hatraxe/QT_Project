#include "UserSerializer.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

bool UserSerializer::serializeToFile(const QList<User>& users, const QString& filename) {
    QJsonArray usersArray;

    for (const User& user : users) {
        QJsonObject userObject;
        userObject["firstname"] = user.getFirstName();
        userObject["lastname"] = user.getLastName();
        userObject["username"] = user.getUsername();
        userObject["password"] = user.getPassword();

        // Sérialisation des droits d'utilisateur
        QJsonObject rightsObject;
        UserRights rights = user.getRights();
        rightsObject["canView"] = rights.canView();
        rightsObject["canEdit"] = rights.canEdit();
        rightsObject["isAdmin"] = rights.isAdmin();
        userObject["rights"] = rightsObject;

        // Sérialisation des profils
        QJsonArray profilesArray;
        for (Profile* profile : user.getProfiles()) {
            profilesArray.append(QJsonValue(profile->getName()));
        }
        userObject["profiles"] = profilesArray;

        usersArray.append(userObject);
    }

    QJsonObject rootObject;
    rootObject["users"] = usersArray;

    QJsonDocument doc(rootObject);
    QFile file(filename);

    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Failed to open file for writing:" << filename;
        return false;
    }

    file.write(doc.toJson());
    file.close();
    return true;
}
