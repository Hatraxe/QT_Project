/*!
 * \file UserStorage.h
 * \brief Définition de la classe UserStorage pour la gestion du stockage des utilisateurs.
 *
 * La classe UserStorage fournit une abstraction pour la sauvegarde, la validation,
 * et la récupération des informations des utilisateurs. Elle gère également le chemin
 * d'accès aux données persistantes des utilisateurs.
 */

#ifndef USERSTORAGE_H
#define USERSTORAGE_H

#include <QString>
#include <QCryptographicHash>
#include <QFile>
#include <QStandardPaths>
#include <QDir>
#include <QCoreApplication>
#include "User.h"

/*!
 * \class UserStorage
 * \brief Classe pour la gestion du stockage des données utilisateur.
 *
 * Permet de sauvegarder de nouveaux utilisateurs, de valider les informations de connexion,
 * et de récupérer la liste des utilisateurs existants.
 */
class UserStorage {
public:
    /*!
     * \brief Constructeur par défaut de UserStorage.
     *
     * Initialise un nouvel objet UserStorage avec des valeurs par défaut.
     */
    UserStorage();

    /*!
     * \brief Enregistre un nouvel utilisateur dans le stockage persistant.
     * \param user L'utilisateur à sauvegarder.
     */
    void saveUser(const User& user);

    /*!
     * \brief Valide les informations de connexion d'un utilisateur.
     * \param username Le nom d'utilisateur.
     * \param password Le mot de passe.
     * \return True si les informations sont valides, False sinon.
     */
    bool validateUser(const QString &username, const QString &password);

    /*!
     * \brief Obtient le nom du fichier de stockage des utilisateurs.
     * \return Le nom du fichier.
     */
    QString getFilename() const;

    /*!
     * \brief Obtient le chemin complet du fichier de stockage des utilisateurs.
     * \return Le chemin complet du fichier.
     */
    QString getUserFilePath() const;

    /*!
     * \brief Obtient la liste des utilisateurs chargés.
     * \return La liste des utilisateurs.
     */
    QList<User> getUsers() const;

    /*!
     * \brief Définit le nom du fichier de stockage des utilisateurs.
     * \param filename Le nouveau nom du fichier.
     */
    void setFilename(const QString &filename);

    /*!
     * \brief Définit le chemin complet vers le fichier de stockage des utilisateurs.
     * \param userFilePath Le nouveau chemin du fichier.
     */
    void setUserFilePath(const QString &userFilePath);

    /*!
     * \brief Définit la liste des utilisateurs chargés.
     * \param users La nouvelle liste des utilisateurs.
     */
    void setUsers(const QList<User> &users);

private:
    QString filename; ///< Nom du fichier pour stocker les utilisateurs.
    QString userFilePath; ///< Chemin complet vers le fichier des utilisateurs.
    QList<User> users; ///< Liste des utilisateurs chargés.
};

#endif // USERSTORAGE_H
