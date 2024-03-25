/*!
 * \file UserDeserializer.h
 * \brief Définition de la classe UserDeserializer pour la désérialisation des utilisateurs.
 *
 * La classe UserDeserializer offre une fonctionnalité pour charger des utilisateurs
 * à partir d'un fichier JSON, convertissant les données JSON en objets User.
 */

#ifndef USERDESERIALIZER_H
#define USERDESERIALIZER_H

#include <QList>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QCoreApplication>
#include "User.h"

/*!
 * \class UserDeserializer
 * \brief Classe utilitaire pour désérialiser des objets User à partir d'un fichier JSON.
 *
 * UserDeserializer contient des méthodes statiques pour charger et transformer les données JSON
 * en instances de la classe User, facilitant ainsi leur utilisation dans l'application.
 */
class UserDeserializer {
public:
    /*!
     * \brief Désérialise les utilisateurs à partir d'un fichier JSON.
     * \param filename Le chemin d'accès au fichier JSON contenant les données des utilisateurs.
     * \return Une liste d'objets User chargés à partir du fichier JSON.
     *
     * Lit le fichier JSON spécifié, extrait les données des utilisateurs et les convertit
     * en une liste d'objets User. Chaque objet User est créé en utilisant les données
     * extraites du fichier.
     */
    static QList<User> deserializeFromFile(const QString& filename);
};

#endif // USERDESERIALIZER_H
