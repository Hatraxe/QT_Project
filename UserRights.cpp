/*!
 * \file UserRights.cpp
 * \brief Implémentation de la classe UserRights.
 *
 * Fournit les définitions des constructeurs, du destructeur, et des méthodes
 * pour vérifier les droits d'un utilisateur.
 */

#include "UserRights.h"

/*!
 * \brief Constructeur paramétrique de UserRights qui initialise les droits de l'utilisateur.
 * \param canView Booléen indiquant si l'utilisateur peut visualiser des éléments.
 * \param canEdit Booléen indiquant si l'utilisateur peut modifier des éléments.
 * \param isAdmin Booléen indiquant si l'utilisateur possède des droits d'administrateur.
 *
 * Initialise un objet UserRights avec les droits spécifiés.
 */
UserRights::UserRights(bool canView, bool canEdit, bool isAdmin)
    : viewPermission(canView), editPermission(canEdit), adminPermission(isAdmin) {
}

/*!
 * \brief Constructeur par défaut de UserRights.
 *
 * Initialise un objet UserRights sans droits, c'est-à-dire tous les droits à false.
 */
UserRights::UserRights()
    : viewPermission(false), editPermission(false), adminPermission(false) {
}

/*!
 * \brief Destructeur de UserRights.
 *
 * Destruction d'un objet UserRights. Aucune logique spécifique de nettoyage n'est nécessaire
 * car UserRights utilise uniquement des types primitifs.
 */
UserRights::~UserRights() {
    // Pas de logique spécifique de nettoyage nécessaire.
}

/*!
 * \brief Vérifie si l'utilisateur peut visualiser des éléments.
 * \return True si l'utilisateur a le droit de visualisation, false sinon.
 *
 * Accesseur pour le droit de visualisation.
 */
bool UserRights::canView() const {
    return viewPermission;
}

/*!
 * \brief Vérifie si l'utilisateur peut éditer des éléments.
 * \return True si l'utilisateur a le droit d'édition, false sinon.
 *
 * Accesseur pour le droit d'édition.
 */
bool UserRights::canEdit() const {
    return editPermission;
}

/*!
 * \brief Vérifie si l'utilisateur est un administrateur.
 * \return True si l'utilisateur a des droits d'administrateur, false sinon.
 *
 * Accesseur pour vérifier si l'utilisateur est un administrateur.
 */
bool UserRights::isAdmin() const {
    return adminPermission;
}
