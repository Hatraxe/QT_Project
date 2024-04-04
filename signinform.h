/*!
 * \file SignInForm.h
 * \brief Définition de la classe SignInForm pour la gestion du formulaire d'inscription.
 *
 * SignInForm permet de créer un nouveau compte utilisateur en interagissant avec UserStorage.
 */

#ifndef SIGNINFORM_H
#define SIGNINFORM_H

#include <QWidget>
#include <QMessageBox>
#include "UserStorage.h"
using namespace std;

/*!
 * Espace de noms Ui. Utilisé par le système UIC de Qt pour gérer l'interface utilisateur.
 */
namespace Ui {
class SignInForm;
}

/*!
 * \class SignInForm
 * \brief Classe représentant le formulaire d'inscription dans l'application.
 *
 * SignInForm fournit une interface permettant à l'utilisateur de s'inscrire en entrant
 * ses informations personnelles. L'inscription est traitée par UserStorage.
 */
class SignInForm : public QWidget {
    Q_OBJECT

public:
    /*!
     * \brief Constructeur de SignInForm.
     * \param parent Le widget parent de ce formulaire.
     * \param storage Le stockage des utilisateurs pour gérer l'inscription.
     *
     * Initialise un nouveau formulaire d'inscription avec un accès au stockage des utilisateurs.
     */
    explicit SignInForm(QWidget *parent, shared_ptr<UserStorage> storage);

    /*!
     * \brief Destructeur de SignInForm.
     *
     * Nettoie les ressources utilisées par le formulaire d'inscription.
     */
    ~SignInForm();

signals:
    /*!
     * \brief Signal émis après la création réussie d'un utilisateur.
     *
     * Ce signal peut être utilisé pour effectuer des actions post-inscription, comme naviguer
     * vers un autre écran ou afficher un message de succès.
     */
    void userCreated();

private slots:
    /*!
     * \brief Gère le clic sur le bouton d'inscription.
     *
     * Vérifie les informations fournies et crée un nouveau compte utilisateur si elles sont valides.
     */
    void signIn();

private:
    Ui::SignInForm *ui; ///< Pointeur vers l'interface utilisateur générée par uic.
    shared_ptr<UserStorage> userStorage; ///< Stockage des utilisateurs pour gérer l'inscription.
};

#endif // SIGNINFORM_H
