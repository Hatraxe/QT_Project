/*!
 * \file UserRights.h
 * \brief Définition de la classe UserRights qui gère les droits d'accès des utilisateurs.
 *
 * La classe UserRights encapsule les droits d'accès attribués à un utilisateur,
 * tels que la possibilité de visualiser, d'éditer ou d'avoir des privilèges d'administration.
 */

#ifndef USERRIGHTS_H
#define USERRIGHTS_H

/*!
 * \class UserRights
 * \brief Classe représentant les droits d'accès d'un utilisateur.
 *
 * Permet de définir et de vérifier les différents droits d'accès attribués à un utilisateur,
 * comme la visualisation, l'édition, ou les droits administratifs.
 */
class UserRights {
public:
    /*!
     * \brief Constructeur de UserRights avec spécification des droits.
     * \param canView Indique si l'utilisateur peut visualiser des données.
     * \param canEdit Indique si l'utilisateur peut éditer des données.
     * \param isAdmin Indique si l'utilisateur a des droits d'administrateur.
     *
     * Initialise un objet UserRights avec les droits spécifiés.
     */
    UserRights(bool canView, bool canEdit, bool isAdmin);

    /*!
     * \brief Constructeur par défaut de UserRights.
     *
     * Initialise un objet UserRights sans aucun droit attribué.
     */
    UserRights();

    /*!
     * \brief Destructeur de UserRights.
     */
    ~UserRights();

    /*!
     * \brief Vérifie si l'utilisateur peut visualiser des données.
     * \return true si l'utilisateur a le droit de visualisation, false sinon.
     */
    bool canView() const;

    /*!
     * \brief Vérifie si l'utilisateur peut éditer des données.
     * \return true si l'utilisateur a le droit d'édition, false sinon.
     */
    bool canEdit() const;

    /*!
     * \brief Vérifie si l'utilisateur est un administrateur.
     * \return true si l'utilisateur a des droits d'administrateur, false sinon.
     */
    bool isAdmin() const;

private:
    bool viewPermission; ///< Indique si l'utilisateur peut visualiser des données.
    bool editPermission; ///< Indique si l'utilisateur peut éditer des données.
    bool adminPermission; ///< Indique si l'utilisateur a des droits d'administrateur.
};

#endif // USERRIGHTS_H
