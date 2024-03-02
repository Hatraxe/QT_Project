/*!
 * \file Profile.h
 * \brief Définition de la classe Profile qui représente un profil utilisateur.
 *
 * La classe Profile permet de stocker et de manipuler les informations relatives à un profil utilisateur.
 */

#ifndef PROFILE_H
#define PROFILE_H

#include <QString>

/*!
 * \class Profile
 * \brief Classe représentant un profil utilisateur.
 *
 * Cette classe stocke le nom d'un profil utilisateur et fournit les fonctionnalités nécessaires pour accéder
 * et gérer ce nom.
 */
class Profile {
public:
    /*!
     * \brief Constructeur de Profile.
     * \param name Le nom du profil.
     *
     * Initialise un nouveau profil avec un nom spécifié.
     */
    Profile(const QString &name);

    /*!
     * \brief Constructeur de copie de Profile.
     * \param other Un autre profil à copier.
     *
     * Crée une copie d'un profil existant.
     */
    Profile(const Profile& other);

    /*!
     * \brief Destructeur de Profile.
     *
     * Détruit l'instance de Profile, libérant les ressources allouées.
     */
    ~Profile();

    /*!
     * \brief Obtient le nom du profil.
     * \return Le nom du profil.
     *
     * Retourne le nom associé à ce profil.
     */
    QString getName() const;

private:
    QString name; ///< Nom du profil.
    // Ajouter ici des attributs supplémentaires pour les paramètres du profil si nécessaire.
};

#endif // PROFILE_H
