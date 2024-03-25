/*!
 * \file DatabaseViewer.cpp
 * \brief Implémentation de la classe DatabaseViewer.
 */

#include "DatabaseViewer.h"

/*!
 * \brief Constructeur de DatabaseViewer qui initialise le widget et configure la base de données.
 * \param parent Le widget parent.
 *
 * Ce constructeur initialise la connexion à la base de données SQLite en utilisant le pilote "QSQLITE"
 * et appelle setupUi pour configurer l'interface utilisateur du visualiseur.
 */
DatabaseViewer::DatabaseViewer(QWidget *parent) : QWidget(parent) {
    db = QSqlDatabase::addDatabase("QSQLITE"); // Utilise le pilote SQLite
    setupUi();
}

/*!
 * \brief Destructeur de DatabaseViewer.
 *
 * Ferme la connexion à la base de données lors de la destruction de l'instance de DatabaseViewer.
 */
DatabaseViewer::~DatabaseViewer() {
    db.close();
}

/*!
 * \brief Tente d'établir une connexion à la base de données SQLite spécifiée.
 * \param databasePath Chemin vers le fichier de la base de données SQLite.
 * \return bool Retourne vrai si la connexion a réussi, faux sinon.
 *
 * Si la connexion échoue, la méthode affiche un message d'erreur dans la console.
 */
bool DatabaseViewer::connectToDatabase(const QString &databasePath) {
    db.setDatabaseName(databasePath);

    if (!db.open()) {
        qDebug() << "Erreur lors de la connexion à la base de données :" << db.lastError().text();
        return false;
    }

    return true;
}

/*!
 * \brief Rafraîchit les données affichées dans le visualiseur.
 *
 * Cette méthode appelle loadData pour recharger les données de la base de données et mettre à jour l'affichage.
 */
void DatabaseViewer::refreshData() {
    if (!currentTableName.isEmpty()) {
        loadData(currentTableName);
    }
}


/*!
 * \brief Configure l'interface utilisateur du visualiseur.
 *
 * Crée et ajoute un QTableView au layout du widget pour afficher les données de la base de données.
 */
void DatabaseViewer::setupUi() {
    auto layout = new QVBoxLayout(this);
    auto tableView = new QTableView(this);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    layout->addWidget(tableView);
}


/*!
 * \brief Charge les données de la table spécifiée dans la base de données et les affiche.
 *
 * Utilise un QSqlTableModel pour lier les données de la table à un QTableView pour l'affichage.
 */
void DatabaseViewer::loadData(const QString &tableName) {
    auto model = new QSqlTableModel(this, db);
    model->setTable(tableName);
    model->select();

    QTableView *tableView = findChild<QTableView *>();
    if (tableView) {
        tableView->setModel(model);
    }
}


void DatabaseViewer::setCurrentTable(const QString &tableName) {
    currentTableName = tableName;
    loadData(currentTableName);
}


