/*!
 * \file LoginForm.h
 * \brief Définition de la classe LoginForm pour la gestion du formulaire de connexion.
 *
 * LoginForm permet à l'utilisateur de se connecter à son compte ou de naviguer vers le formulaire d'inscription.
 */

#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <QMessageBox>
#include "LoginManager.h"

namespace Ui {
class LoginForm;
}

/*!
 * \class LoginForm
 * \brief La classe LoginForm crée une interface utilisateur pour que les utilisateurs puissent se connecter.
 *
 * Elle interagit avec LoginManager pour vérifier les informations de connexion.
 */
class LoginForm : public QWidget {
    Q_OBJECT

public:
    /*!
     * \brief Constructeur de LoginForm.
     * \param parent Le widget parent de ce formulaire.
     * \param loginManager Le gestionnaire de connexion partagé à utiliser pour la vérification des identifiants.
     */
    explicit LoginForm(QWidget *parent, std::shared_ptr<LoginManager> loginManager);

    /*!
     * \brief Destructeur de LoginForm.
     */
    ~LoginForm();

signals:
    /*!
     * \brief Signal émis lorsque l'utilisateur est connecté avec succès.
     */
    void userConnected();

    /*!
     * \brief Signal émis pour demander l'affichage du formulaire d'inscription.
     */
    void signUpRequested();

private slots:
    /*!
     * \brief Slot activé lorsque le bouton de connexion est cliqué.
     *
     * Vérifie les informations de connexion et émet userConnected si les identifiants sont valides.
     */
    void login();

    /*!
     * \brief Slot activé lorsque l'utilisateur clique sur "Mot de passe oublié".
     *
     * Affiche un message indiquant la procédure à suivre pour récupérer son mot de passe.
     */
    void mdpOublie();

    /*!
     * \brief Slot activé lorsque l'utilisateur souhaite s'inscrire.
     *
     * Émet le signal signUpRequested pour demander l'affichage du formulaire d'inscription.
     */
    void signInSignal();

private:
    Ui::LoginForm *ui; ///< Pointeur vers l'interface utilisateur générée par uic.
    std::shared_ptr<LoginManager> loginManager; ///< Gestionnaire de connexion pour vérifier les identifiants.
};

#endif // LOGINFORM_H
