/*!
 * \file Profile.cpp
 * \brief Implémentation de la classe Profile.
 */

#include "Profile.h"

/*!
 * \brief Constructeur avec un nom de profil.
 * \param name Nom du profil.
 *
 * Initialise un profil avec le nom spécifié.
 */
Profile::Profile(const QString &name) : name(name) {
}

/*!
 * \brief Destructeur de Profile.
 *
 * Libère les ressources allouées par le profil. Pour un QString, cette libération est automatiquement gérée.
 */
Profile::~Profile() {
    // Ici, on pourrait libérer des ressources si nécessaire, mais pour un QString, ce n'est pas requis.
}

/*!
 * \brief Constructeur de recopie.
 * \param other Profil à copier.
 *
 * Crée une copie du profil spécifié en copiant son nom.
 */
Profile::Profile(const Profile& other) : name(other.name) {
    // Le constructeur de recopie copie simplement le nom de l'autre profil
}

/*!
 * \brief Récupère le nom du profil.
 * \return Le nom du profil sous forme de QString.
 *
 * Retourne le nom associé à ce profil.
 */
QString Profile::getName() const {
    return name;
}
