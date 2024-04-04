/*!
 * \file UserDataView.cpp
 * \brief Implémentation de la classe UserDataView pour l'affichage et la gestion des informations de l'utilisateur.
 */

#include "UserDataView.h"
#include "ui_userdataview.h"
#include <QFileDialog>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlDatabase>

/*!
 * \brief Constructeur de UserDataView.
 * \param parent Le widget parent de cette vue.
 * \param loginManager Le gestionnaire de connexion pour accéder aux informations de l'utilisateur connecté.
 *
 * Initialise la vue UserDataView et connecte les boutons à leurs slots respectifs.
 */
UserDataView::UserDataView(QWidget *parent, std::shared_ptr<LoginManager> loginManager)
    : QWidget(parent),
    ui(new Ui::UserDataView),
    loginManager(loginManager) ,
    databaseManager(std::make_shared<DatabaseManager>()) {
    ui->setupUi(this);

    // Connexion des boutons aux slots correspondants
    connect(ui->logoutButton, &QPushButton::clicked, this, &UserDataView::on_logoutButton_clicked);
    connect(ui->changePasswordButton, &QPushButton::clicked, this, &UserDataView::on_changePasswordButton_clicked);
    connect(ui->changeProfileButton, &QPushButton::clicked, this, &UserDataView::on_changeProfileButton_clicked);
    connect(ui->okButton, &QPushButton::clicked, this, &UserDataView::on_okButton_clicked);


    connect(ui->ajouterPushButton, &QPushButton::clicked, this, &UserDataView::on_ajouterPushButton_clicked);
    connect(ui->supprimerPushButton, &QPushButton::clicked, this, &UserDataView::on_supprimerPushButton_clicked);
    connect(ui->executePushButton, &QPushButton::clicked, this, &UserDataView::on_executePushButton_clicked);
    connect(ui->dispoBddComboBox, &QComboBox::currentIndexChanged, this, &UserDataView::on_dispoBddComboBox_currentIndexChanged);
    connect(ui->tablesBddComboBox, &QComboBox::currentTextChanged, this, &UserDataView::displayTableContent);

}

/*!
 * \brief Destructeur de UserDataView.
 */
UserDataView::~UserDataView(){
    delete ui;
}

/*!
 * \brief Rafraîchit les informations de l'utilisateur affichées.
 *
 * Met à jour l'interface utilisateur avec les informations actuelles de l'utilisateur connecté,
 * incluant les noms, les droits d'accès et la liste des profils.
 */
void UserDataView::refreshUserInfos(){
    // Initialise l'affichage des informations utilisateur
    if (loginManager) {
        auto user = loginManager->getCurrentUser();
        if (user) {
            ui->nameUser->setText(user->getFirstName());
            ui->surnameUser->setText(user->getLastName());
            ui->mailUser->setText(user->getMail());

            QStringList rightsList;
            if (user->getRights().canView()) rightsList << "Vue";
            if (user->getRights().canEdit()) rightsList << "Édition";
            if (user->getRights().isAdmin()) rightsList << "Admin";
            ui->rightsUser->setText(rightsList.join(", "));
            if (rightsList.empty()) ui->rightsUser->setText("Aucun droits");

            ui->profileComboBox->clear();

            if (!user->getProfiles().isEmpty()) {
                for (Profile* profile : user->getProfiles()) {
                    ui->profileComboBox->addItem(profile->getName());
                }

                ui->okButton->setEnabled(true);
            } else {

                ui->okButton->setEnabled(false);
            }
        }
    }
}

/*!
 * \brief Gère l'action de déconnexion demandée par l'utilisateur.
 */
void UserDataView::on_logoutButton_clicked() {
    emit logoutRequested();
}

/*!
 * \brief Ouvre un dialogue pour changer le mot de passe de l'utilisateur.
 */
void UserDataView::on_changePasswordButton_clicked() {
    // Implémentation future
}

/*!
 * \brief Ouvre un dialogue pour permettre à l'utilisateur de modifier son profil.
 */
void UserDataView::on_changeProfileButton_clicked() {
    // Implémentation future
}

/*!
 * \brief Gère le clic sur le bouton "OK" pour confirmer le changement de profil sélectionné.
 *
 * Met à jour le profil actuel de l'utilisateur avec le profil sélectionné dans la comboBox.
 */
void UserDataView::on_okButton_clicked() {
    if (loginManager) {
        auto user = loginManager->getCurrentUser();
        if (user) {

            int index = ui->profileComboBox->currentIndex();
            user->setCurrentProfile(user->getProfiles().at(index));

            QMessageBox::information(this, "Profil", "Profil actuel mis à jour : " + user->getCurrentProfile()->getName());
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void UserDataView::on_ajouterPushButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Ouvrir une base de données"), "", tr("Base de données SQLite (*.sqlite *.db)"));
    if (!fileName.isEmpty()) {
        databaseManager->addDatabase(fileName);
        qDebug() << "ajout de la db";

        refreshDatabasesList();
    }
}

void UserDataView::on_supprimerPushButton_clicked() {
    QString currentDb = ui->dispoBddComboBox->currentText();
    databaseManager->removeDatabase(currentDb);
    refreshDatabasesList();
}

void UserDataView::on_executePushButton_clicked() {
    QString queryStr = ui->requeteSQLText->text().trimmed();
    QString connectionName = ui->dispoBddComboBox->currentText();

    // Validation de base des requêtes pour limiter les opérations à "SELECT"
    if (!queryStr.toUpper().startsWith("SELECT")) {
        QMessageBox::warning(this, tr("Opération non autorisée"), tr("Seules les opérations de sélection (SELECT) sont autorisées."));
        return;
    }

    QSqlDatabase db = QSqlDatabase::database(connectionName);
    if (!db.isOpen()) {
        QMessageBox::critical(this, tr("Erreur de base de données"), tr("La connexion à la base de données est fermée ou invalide."));
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(queryStr, db);

    if (model->lastError().isValid()) {
        QMessageBox::critical(this, tr("Erreur de requête SQL"), model->lastError().text());
        delete model; // Assurez-vous de supprimer le modèle en cas d'erreur pour éviter les fuites de mémoire
    } else if (model->rowCount() == 0) {
        QMessageBox::information(this, tr("Requête SQL"), tr("La requête a été exécutée avec succès, mais n'a retourné aucun résultat."));
        ui->vueContenuBddTableView->setModel(model);
    } else {
        QMessageBox::information(this, tr("Requête SQL"), tr("La requête a été exécutée avec succès."));
        ui->vueContenuBddTableView->setModel(model);
    }

    // Ajustements de l'interface de la vue
    ui->vueContenuBddTableView->resizeColumnsToContents();
    ui->vueContenuBddTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->vueContenuBddTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}


void UserDataView::on_dispoBddComboBox_currentIndexChanged(int index) {
    Q_UNUSED(index);
    refreshTablesList();
}

void UserDataView::refreshDatabasesList() {
    ui->dispoBddComboBox->clear(); // Efface les éléments existants
    QStringList dbNames = databaseManager->getDatabaseNames();
    ui->dispoBddComboBox->addItems(dbNames); // Ajoute les noms des bases de données disponibles

    if (!dbNames.isEmpty()) {
        refreshTablesList(); // Met à jour la liste des tables pour la première base de données par défaut
    }
}


void UserDataView::refreshTablesList() {
    ui->tablesBddComboBox->clear(); // Efface les éléments existants

    QString selectedDb = ui->dispoBddComboBox->currentText();
    if (!selectedDb.isEmpty()) {
        QStringList tableNames = databaseManager->listTables(selectedDb);
        ui->tablesBddComboBox->addItems(tableNames); // Ajoute les noms des tables de la base de données sélectionnée
    }
}


void UserDataView::displayTableContent(const QString &tableName) {
    if (tableName.isEmpty()) {
        return;
    }

    QString selectedDb = ui->dispoBddComboBox->currentText();
    QSqlDatabase db = QSqlDatabase::database(selectedDb);
    if (!db.isOpen()) {
        // Tente de réouvrir la base de données si elle n'est pas déjà ouverte
        if (!db.open()) {
            qDebug() << "Erreur lors de la réouverture de la base de données : " << db.lastError().text();
            return;
        }
    }

    QSqlTableModel *model = new QSqlTableModel(this, db);
    model->setTable(tableName);
    model->select();

    // Pour afficher toutes les modifications apportées aux données immédiatement dans la vue
    model->setEditStrategy(QSqlTableModel::OnFieldChange);

    ui->vueContenuBddTableView->setModel(model);

    // ajuste l'apparence et le comportement de la tableView
    ui->vueContenuBddTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->vueContenuBddTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->vueContenuBddTableView->resizeColumnsToContents();
}




