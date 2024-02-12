#include "SignInForm.h"
#include "ui_signinform.h"
#include <QMessageBox>

SignInForm::SignInForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignInForm) {
    ui->setupUi(this);
    connect(ui->pushButton_Inscrire, &QPushButton::clicked, this, &SignInForm::on_signInButton_clicked);
}

SignInForm::~SignInForm() {
    delete ui;
}

void SignInForm::on_signInButton_clicked() {
    // Exemple de récupération de valeurs depuis l'interface utilisateur
    QString nom = ui->lineEdit_Nom->text();
    QString prenom = ui->lineEdit_Prenom->text();
    QString email = ui->lineEdit_Email->text();
    QString password = ui->lineEdit_Mdp->text();
    QString confirmPassword = ui->lineEdit_ConfirmMdp->text();

    // Vérification basique de la saisie
    if (nom.isEmpty() || prenom.isEmpty() || email.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
        QMessageBox::warning(this, "Inscription incomplète", "Veuillez remplir tous les champs.");
        return;
    }

    if (password != confirmPassword) {
        QMessageBox::warning(this, "Erreur de mot de passe", "Les mots de passe ne correspondent pas.");
        return;
    }

    // Ici, insérez la logique pour créer un nouvel utilisateur, par exemple :
    // if (!createUser(nom, prenom, email, password)) {
    //     QMessageBox::warning(this, "Erreur", "Impossible de créer l'utilisateur.");
    // } else {
    //     QMessageBox::information(this, "Succès", "Utilisateur créé avec succès.");
    //     // Vous pouvez émettre un signal pour indiquer la création réussie, changer de vue, etc.
    // }
}
