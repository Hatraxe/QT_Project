#include "DatabaseManager.h"
#include "qfileinfo.h"
#include <QSqlTableModel>
#include <QPointer>

DatabaseManager::DatabaseManager() {}

DatabaseManager::~DatabaseManager() {
    closeAllDatabases();
}

bool DatabaseManager::addDatabase(const QString &filePath) {
    QString connectionName = QFileInfo(filePath).fileName();
    if (QSqlDatabase::contains(connectionName)) {
        return true; // Retourne vrai si la base de données existe déjà pour éviter les doublons
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    db.setDatabaseName(filePath);
    if (!db.open()) {
        return false;
    }
    databases.append(db);
    return true;
}

bool DatabaseManager::removeDatabase(const QString &connectionName) {
    QSqlDatabase db = QSqlDatabase::database(connectionName, false);
    if (db.isValid()) {
        db.close();
        QSqlDatabase::removeDatabase(connectionName);
        auto it = std::find_if(databases.begin(), databases.end(), [&connectionName](const QSqlDatabase& db) {
            return db.connectionName() == connectionName;
        });
        if (it != databases.end()) {
            databases.erase(it);
           // emit databaseRemoved(connectionName); // Signale la suppression d'une base de données
        }
        return true;
    }
    return false;
}

QStringList DatabaseManager::listTables(const QString &connectionName) {
    QSqlDatabase db = QSqlDatabase::database(connectionName);
    if (db.isOpen()) {
        return db.tables();
    }
    return QStringList();
}

QSqlQueryModel* DatabaseManager::executeQuery(const QString &connectionName, const QString &query) {
    QSqlDatabase db = QSqlDatabase::database(connectionName);
    if (!db.isOpen()) {
        // Retourne nullptr si la base de données n'est pas ouverte
        return nullptr;
    }

    QPointer<QSqlQueryModel> model = new QSqlQueryModel;
    model->setQuery(query, db);
    if (model->lastError().isValid()) {
        // En cas d'erreur, nettoye et retourne nullptr
        delete model;
        return nullptr;
    }

    return model;
}


void DatabaseManager::closeAllDatabases() {
    foreach (QSqlDatabase db, databases) {
        db.close();
    }
    databases.clear();
}

QStringList DatabaseManager::getDatabaseNames() const {
    QStringList names;
    for (const QSqlDatabase &db : databases) {
        names.append(db.connectionName());
    }
    return names;
}

