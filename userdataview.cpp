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

    // Connexion des boutons aux slots correspondants pour le Tab Infos utilisateur
    connect(ui->logoutButton, &QPushButton::clicked, this, &UserDataView::deconnexionClic);
    connect(ui->changePasswordButton, &QPushButton::clicked, this, &UserDataView::changePasswordClic);
    connect(ui->changeProfileButton, &QPushButton::clicked, this, &UserDataView::changeProfilClic);
    connect(ui->okButton, &QPushButton::clicked, this, &UserDataView::okClic);

    // Pour le Tab Gestion des Bdd
    connect(ui->ajouterPushButton, &QPushButton::clicked, this, &UserDataView::ajouterClic);
    connect(ui->supprimerPushButton, &QPushButton::clicked, this, &UserDataView::supprimerClic);
    connect(ui->executePushButton, &QPushButton::clicked, this, &UserDataView::executerClic);
    connect(ui->dispoBddComboBox, &QComboBox::currentIndexChanged, this, &UserDataView::indexComboBoxBddChanged);
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

            // On peut imaginer ici une gestion des droits utilisateurs plus poussée.

            ui->ajouterPushButton->setEnabled(user->getRights().canView());
            ui->supprimerPushButton->setEnabled(user->getRights().canView());
            ui->executePushButton->setEnabled(user->getRights().canView());
        }
    }
}

/*!
 * \brief Gère l'action de déconnexion demandée par l'utilisateur.
 */
void UserDataView::deconnexionClic() {
    emit logoutRequested();
}

/*!
 * \brief Ouvre un dialogue pour changer le mot de passe de l'utilisateur.
 */
void UserDataView::changePasswordClic() {
    // Implémentation future
    // Nous ne l'avons pas implémenté car pas nécessaire mais cela peut être intéressant pour le futur
}

/*!
 * \brief Ouvre un dialogue pour permettre à l'utilisateur de modifier son profil.
 */
void UserDataView::changeProfilClic() {
    // Implémentation future
    // idem
}

/*!
 * \brief Gère le clic sur le bouton "OK" pour confirmer le changement de profil sélectionné.
 *
 * Met à jour le profil actuel de l'utilisateur avec le profil sélectionné dans la comboBox.
 */
void UserDataView::okClic() {
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

void UserDataView::ajouterClic() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Ouvrir une base de données"), "", tr("Base de données SQLite (*.sqlite *.db)"));
    if (!fileName.isEmpty()) {
        databaseManager->addDatabase(fileName);

        refreshDatabasesList();
    }
}

void UserDataView::supprimerClic() {
    auto user = loginManager->getCurrentUser();
    if (!user || !user->getRights().canEdit()) {
        QMessageBox::warning(this, tr("Accès refusé"), tr("Vous n'avez pas les droits nécessaires pour supprimer une base de données."));
        return;
    }

    QString currentDbName = ui->dispoBddComboBox->currentText();
    // Vérifie si le modèle actuel utilise la base de données à supprimer
    auto model = dynamic_cast<QSqlQueryModel*>(ui->vueContenuBddTableView->model());
    if (model) {
        // Désassocie le modèle de la vue avant de supprimer la base de données
        ui->vueContenuBddTableView->setModel(nullptr);
        delete model;
    }

    // Tentative de suppression de la base de données
    bool success = databaseManager->removeDatabase(currentDbName);
    if (success) {
        QMessageBox::information(this, tr("Suppression réussie"), tr("La base de données \"%1\" a été supprimée avec succès.").arg(currentDbName));
    } else {
        QMessageBox::critical(this, tr("Échec de la suppression"), tr("Impossible de supprimer la base de données \"%1\".").arg(currentDbName));
    }

    refreshDatabasesList();
}



void UserDataView::executerClic() {
    auto user = loginManager->getCurrentUser();
    if (!user || !user->getRights().canView()) {
        QMessageBox::warning(this, tr("Accès refusé"), tr("Vous n'avez pas les droits nécessaires pour exécuter cette action."));
        return;
    }

    QString queryStr = ui->requeteSQLText->text().trimmed();
    QString connectionName = ui->dispoBddComboBox->currentText();

    // Validation avancée des requêtes pour sécurité accrue
    if (!isValidQuery(queryStr, user->getRights())) {
        QMessageBox::warning(this, tr("Requête invalide"), tr("La requête n'est pas autorisée."));
        return;
    }

    QSqlDatabase db = QSqlDatabase::database(connectionName);
    if (!db.isOpen()) {
        QMessageBox::critical(this, tr("Erreur de base de données"), tr("La connexion à la base de données est fermée ou invalide."));
        return;
    }

    // Réutilisation ou création d'un nouveau modèle QSqlQueryModel
    auto model = dynamic_cast<QSqlQueryModel*>(ui->vueContenuBddTableView->model());
    if (!model) {
        model = new QSqlQueryModel;
    }

    model->setQuery(queryStr, db);
    if (model->lastError().isValid()) {
        QMessageBox::critical(this, tr("Erreur de requête SQL"), model->lastError().text());
        delete model; // Supprime le modèle pour éviter les fuites de mémoire
        ui->vueContenuBddTableView->setModel(nullptr);
    } else {
        // Ajustements de l'interface de la vue en cas de succès
        if (model->rowCount() == 0) {
            QMessageBox::information(this, tr("Requête SQL"), tr("La requête a été exécutée avec succès, mais n'a retourné aucun résultat."));
        } else {
            QMessageBox::information(this, tr("Requête SQL"), tr("La requête a été exécutée avec succès."));
        }
        ui->vueContenuBddTableView->setModel(model);
        ui->vueContenuBddTableView->resizeColumnsToContents();
        ui->vueContenuBddTableView->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->vueContenuBddTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    }
}

bool UserDataView::isValidQuery(const QString& query, const UserRights& rights) {
    // Ici cette méthode est un exemple basique de gestion des droits. Si l'utilisateur n'est pas admin et que la
    // requête commence par autre chose que SELECT on renvoie une erreur.

    if (!rights.isAdmin() && !query.startsWith("SELECT", Qt::CaseInsensitive)) {
        return false;
    }
    return true;
}



void UserDataView::indexComboBoxBddChanged(int index) {
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




