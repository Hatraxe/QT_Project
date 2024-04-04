/*!
 * \file SignInForm.cpp
 * \brief Implémentation de la classe SignInForm pour la gestion du formulaire d'inscription.
 */

#include "SignInForm.h"
#include "ui_signinform.h"

#include "UserStorage.h"
#include "User.h"
using namespace std;

/*!
 * \brief Constructeur de SignInForm.
 * \param parent Le widget parent de ce formulaire.
 * \param storage Le stockage des utilisateurs pour gérer l'inscription.
 *
 * Initialise un nouveau formulaire d'inscription avec un accès au stockage des utilisateurs.
 */
SignInForm::SignInForm(QWidget *parent, std::shared_ptr<UserStorage> storage)
    : QWidget(parent), ui(new Ui::SignInForm), userStorage(storage) {
    ui->setupUi(this);
    // Connecte le bouton d'inscription à son slot
    connect(ui->signInButton, &QPushButton::clicked, this, &SignInForm::signIn);
}

/*!
 * \brief Destructeur de SignInForm.
 *
 * Nettoie les ressources utilisées par le formulaire d'inscription.
 */
SignInForm::~SignInForm() {
    delete ui;
}

/*!
 * \brief Slot activé lorsque le bouton d'inscription est cliqué.
 *
 * Récupère les informations de l'utilisateur depuis l'interface, vérifie la validité des données,
 * crée un nouvel utilisateur, et informe de la réussite ou de l'échec de l'opération.
 */
void SignInForm::signIn() {
    // Récupération et validation des valeurs entrées par l'utilisateur
    QString firstname = ui->lineEdit_Nom->text();
    QString lastname = ui->lineEdit_Prenom->text();
    QString email = ui->lineEdit_Email->text();
    QString password = ui->lineEdit_Mdp->text();
    QString confirmPassword = ui->lineEdit_ConfirmMdp->text();


    // Vérification basique de la saisie
    if (firstname.isEmpty() || lastname.isEmpty() || email.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
        QMessageBox::warning(this, "Inscription incomplète", "Veuillez remplir tous les champs.");
        return;
    }

    if (password != confirmPassword) {
        QMessageBox::warning(this, "Erreur de mot de passe", "Les mots de passe ne correspondent pas.");
        return;
    }



    // Création des profils
    QList<Profile*> profiles;
    Profile* profile1 = new Profile("profil1");
    Profile* profile2 = new Profile("profil2");
    profiles.append(profile1);
    profiles.append(profile2);

    // Hashage du mot de passe
    QByteArray passwordHash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);


    UserRights rights;
    rights.setCanView(true); // L'utilisateur peut uniquement visualiser
    rights.setCanEdit(false); // L'utilisateur ne peut pas éditer
    rights.setIsAdmin(false); // L'utilisateur n'est pas administrateur

    // Création de l'objet User
    User newUser(firstname, lastname, email, QString(passwordHash.toHex()), rights, profiles);

    // Sérialisation du nouvel utilisateur

    userStorage->saveUser(newUser);


    // Informer l'utilisateur et émettre un signal
    QMessageBox::information(this, "Succès", "Utilisateur créé avec succès.");
    emit userCreated(); // Émet le signal pour indiquer la création réussie

}
