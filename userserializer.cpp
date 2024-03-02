/*!
 * \file UserSerializer.cpp
 * \brief Implémentation de la classe UserSerializer.
 *
 * Fournit des méthodes pour sérialiser une liste d'utilisateurs en JSON et sauvegarder dans un fichier.
 */

#include "UserSerializer.h"

/*!
 * \brief Sérialise une liste d'objets User en JSON et sauvegarde dans un fichier.
 *
 * \param users La liste des utilisateurs à sérialiser.
 * \param filename Le nom du fichier où sauvegarder le JSON.
 * \return True si la sérialisation et la sauvegarde réussissent, False sinon.
 *
 * Parcourt chaque utilisateur dans la liste fournie, extrait leurs informations et les convertit
 * en format JSON. Ensuite, sauvegarde ce JSON dans le fichier spécifié par filename. Si le fichier
 * ne peut être ouvert en écriture, retourne false.
 */
bool UserSerializer::serializeToFile(const QList<User>& users, const QString& filename) {
    QJsonArray usersArray;

    // Boucle sur chaque utilisateur pour créer leur représentation JSON
    for (const User& user : users) {
        QJsonObject userObject;
        userObject["firstname"] = user.getFirstName();
        userObject["lastname"] = user.getLastName();
        userObject["username"] = user.getUsername();
        userObject["password"] = user.getPassword(); // Note: Le mot de passe est déjà haché

        // Sérialisation des droits de l'utilisateur
        QJsonObject rightsObject;
        UserRights rights = user.getRights();
        rightsObject["canView"] = rights.canView();
        rightsObject["canEdit"] = rights.canEdit();
        rightsObject["isAdmin"] = rights.isAdmin();
        userObject["rights"] = rightsObject;

        // Sérialisation des profils de l'utilisateur
        QJsonArray profilesArray;
        for (Profile* profile : user.getProfiles()) {
            profilesArray.append(QJsonValue(profile->getName()));
        }
        userObject["profiles"] = profilesArray;

        usersArray.append(userObject);
    }

    // Création de l'objet JSON racine et ajout du tableau des utilisateurs
    QJsonObject rootObject;
    rootObject["users"] = usersArray;

    // Écriture du document JSON dans le fichier
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
