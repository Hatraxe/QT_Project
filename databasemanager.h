#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QDebug>
#include <QList>

class DatabaseManager {
public:
    DatabaseManager();
    ~DatabaseManager();

    // Ajoute une base de données à l'application et ouvre la connexion
    bool addDatabase(const QString &filePath);

    // Supprime une base de données de l'application
    bool removeDatabase(const QString &connectionName);

    // Liste les tables d'une base de données spécifiée
    QStringList listTables(const QString &connectionName);

    // Exécute une requête SQL sur une base de données spécifiée et retourne un modèle pour affichage
    QSqlQueryModel* executeQuery(const QString &connectionName, const QString &query);

    // Ferme toutes les connexions aux bases de données et les supprime
    void closeAllDatabases();

    QStringList getDatabaseNames() const;

private:
    QList<QSqlDatabase> databases; // Liste contenant les bases de données ouvertes
};

#endif // DATABASEMANAGER_H
