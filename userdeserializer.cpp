/*!
 * \file UserDeserializer.cpp
 * \brief Implémentation de la classe UserDeserializer pour la désérialisation des utilisateurs.
 *
 * Fournit des méthodes pour charger des objets User à partir d'un fichier JSON, transformant
 * les données JSON en instances concrètes de la classe User.
 */

#include "UserDeserializer.h"

/*!
 * \brief Désérialise les utilisateurs à partir d'un fichier JSON.
 * \param filename Le chemin d'accès au fichier JSON contenant les données des utilisateurs.
 * \return Une liste d'objets User chargés à partir du fichier JSON.
 *
 * Ouvre et lit le fichier JSON spécifié, extrait les données des utilisateurs et les convertit
 * en une liste d'objets User. Si le fichier ne peut pas être ouvert, une liste vide est retournée.
 * Chaque utilisateur est créé avec ses droits et profils correspondants.
 */
QList<User> UserDeserializer::deserializeFromFile(const QString& filename) {
    QList<User> users;
    QFile file(filename);

    // Tentative d'ouverture du fichier
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file:" << filename;
        return users; // Retourne une liste vide si le fichier ne peut pas être ouvert
    }

    // Lecture et conversion du contenu JSON
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonArray usersArray = doc.object().value("users").toArray();
    file.close(); // Fermeture du fichier après lecture

    // Traitement de chaque utilisateur dans le tableau JSON
    for (const QJsonValue &userVal : usersArray) {
        // Extraction des données utilisateur
        QJsonObject userObject = userVal.toObject();
        QString firstName = userObject["firstname"].toString();
        QString lastName = userObject["lastname"].toString();
        QString username = userObject["username"].toString();
        QString password = userObject["password"].toString(); // Le mot de passe est supposé être déjà haché

        // Extraction et création des droits utilisateur
        QJsonObject rightsObject = userObject["rights"].toObject();
        UserRights rights(
            rightsObject["canView"].toBool(),
            rightsObject["canEdit"].toBool(),
            rightsObject["isAdmin"].toBool()
            );

        // Création de la liste des profils
        QList<Profile*> profiles;
        QJsonArray profilesArray = userObject["profiles"].toArray();
        for (const QJsonValue &profileVal : profilesArray) {
            profiles.append(new Profile(profileVal.toString()));
        }

        // Ajout de l'utilisateur à la liste
        users.append(User(firstName, lastName, username, password, rights, profiles));
    }

    return users; // Retourne la liste des utilisateurs désérialisés
}
