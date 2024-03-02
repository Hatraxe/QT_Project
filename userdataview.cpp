/*!
 * \file UserDataView.cpp
 * \brief Implémentation de la classe UserDataView pour l'affichage et la gestion des informations de l'utilisateur.
 */

#include "UserDataView.h"
#include "ui_userdataview.h"
#include <QMessageBox>

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
    loginManager(loginManager) {
    ui->setupUi(this);

    // Connexion des boutons aux slots correspondants
    connect(ui->logoutButton, &QPushButton::clicked, this, &UserDataView::on_logoutButton_clicked);
    connect(ui->changePasswordButton, &QPushButton::clicked, this, &UserDataView::on_changePasswordButton_clicked);
    connect(ui->changeProfileButton, &QPushButton::clicked, this, &UserDataView::on_changeProfileButton_clicked);
    connect(ui->okButton, &QPushButton::clicked, this, &UserDataView::on_okButton_clicked);
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
