/*!
 * \file UserSerializer.h
 * \brief Définition de la classe UserSerializer pour la sérialisation des utilisateurs.
 *
 * La classe UserSerializer offre une fonctionnalité pour enregistrer des utilisateurs
 * dans un fichier JSON, convertissant les objets User en données JSON.
 */

#ifndef USERSERIALIZER_H
#define USERSERIALIZER_H

#include <QList>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "User.h"

/*!
 * \class UserSerializer
 * \brief Classe utilitaire pour sérialiser des objets User dans un fichier JSON.
 *
 * UserSerializer contient des méthodes statiques pour enregistrer des instances de la classe User
 * dans un fichier JSON, facilitant ainsi leur persistance.
 */
class UserSerializer {
public:
    /*!
     * \brief Sérialise les utilisateurs dans un fichier JSON.
     * \param users La liste des objets User à sérialiser.
     * \param filename Le chemin d'accès au fichier JSON où enregistrer les données des utilisateurs.
     * \return bool Retourne vrai si la sérialisation et l'enregistrement dans le fichier ont réussi, faux sinon.
     *
     * Prend une liste d'objets User, les convertit en format JSON et les sauvegarde
     * dans le fichier spécifié par filename. Si le fichier ne peut pas être ouvert ou si une erreur survient
     * lors de l'écriture, la fonction retourne faux.
     */
    static bool serializeToFile(const QList<User>& users, const QString& filename);
};

#endif // USERSERIALIZER_H
