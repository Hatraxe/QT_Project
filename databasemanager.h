/**
 * @file DatabaseManager.h
 * @brief Gère la connexion aux bases de données SQLite et leurs interactions.
 *
 * Cette classe fournit des fonctionnalités pour ajouter, supprimer, lister les bases de données SQLite,
 * exécuter des requêtes SQL et fermer toutes les connexions ouvertes.
 */

#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QDebug>
#include <QList>


/**
 * @class DatabaseManager
 * @brief Gestionnaire de bases de données pour l'application.
 *
 * Permet d'ajouter, supprimer, et lister les bases de données SQLite,
 * ainsi que d'exécuter des requêtes SQL spécifiques.
 */

class DatabaseManager {
public:
    /**
     * @brief Constructeur par défaut de DatabaseManager.
     */
    DatabaseManager();

    /**
     * @brief Destructeur de DatabaseManager.
     *
     * Ferme toutes les bases de données ouvertes avant la destruction de l'objet.
     */
    ~DatabaseManager();

    /**
     * @brief Ajoute une base de données SQLite à l'application.
     * @param filePath Le chemin du fichier de la base de données à ajouter.
     * @return bool Retourne true si la base de données a été ajoutée avec succès, false sinon.
     */
    bool addDatabase(const QString &filePath);

    /**
     * @brief Supprime une base de données de l'application.
     * @param connectionName Le nom de la connexion associée à la base de données à supprimer.
     * @return bool Retourne true si la base de données a été supprimée avec succès, false sinon.
     */
    bool removeDatabase(const QString &connectionName);

    /**
     * @brief Liste les tables d'une base de données spécifiée.
     * @param connectionName Le nom de la connexion à la base de données.
     * @return QStringList Liste des noms de tables dans la base de données.
     */
    QStringList listTables(const QString &connectionName);

    /**
     * @brief Exécute une requête SQL sur une base de données spécifiée.
     * @param connectionName Le nom de la connexion à la base de données sur laquelle exécuter la requête.
     * @param query La requête SQL à exécuter.
     * @return QSqlQueryModel* Un modèle contenant le résultat de la requête. Retourne nullptr en cas d'échec.
     */
    QSqlQueryModel* executeQuery(const QString &connectionName, const QString &query);

    /**
     * @brief Ferme toutes les bases de données ouvertes.
     */
    void closeAllDatabases();

    /**
     * @brief Obtient les noms de toutes les bases de données gérées.
     * @return QStringList Liste des noms de connexion des bases de données.
     */
    QStringList getDatabaseNames() const;

private:
    QList<QSqlDatabase> databases; ///< Liste des bases de données ouvertes gérées par le gestionnaire.
};

#endif // DATABASEMANAGER_H
