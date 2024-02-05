#include "DatabaseViewer.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QVBoxLayout>
#include <QTableView>
#include <QSqlTableModel>

DatabaseViewer::DatabaseViewer(QWidget *parent) : QWidget(parent) {
    db = QSqlDatabase::addDatabase("QSQLITE"); // Utilise le pilote SQLite
    setupUi();
}

DatabaseViewer::~DatabaseViewer() {
    db.close();
}

bool DatabaseViewer::connectToDatabase(const QString &databasePath) {
    db.setDatabaseName(databasePath);

    if (!db.open()) {
        qDebug() << "Erreur lors de la connexion à la base de données :" << db.lastError().text();
        return false;
    }

    return true;
}

void DatabaseViewer::refreshData() {
    loadData();
}

void DatabaseViewer::setupUi() {
    // Exemple de configuration d'interface utilisateur avec un QTableView
    auto layout = new QVBoxLayout(this);
    auto tableView = new QTableView(this);
    layout->addWidget(tableView);

    // Configurez ici d'autres éléments de l'interface utilisateur si nécessaire
}

void DatabaseViewer::loadData() {
    // Exemple de chargement de données avec QSqlTableModel
    auto model = new QSqlTableModel(this, db);
    model->setTable("nom_de_votre_table"); // Remplacez par le nom de votre table
    model->select();

    // Configurez le modèle sur votre vue, par exemple un QTableView
    QTableView *tableView = findChild<QTableView *>();
    if (tableView) {
        tableView->setModel(model);
    }
}
