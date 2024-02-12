#ifndef USERSTORAGE_H
#define USERSTORAGE_H

#include <QString>

class UserStorage {
public:
    UserStorage(const QString &filename);
    bool userExists(const QString &username); // Vérifie si un utilisateur existe
    bool userFileExists(); //Verifie si un user file exist
    void saveUser(const QString &username, const QString &password); // Enregistre un nouvel utilisateur
    bool validateUser(const QString &username, const QString &password); // Valide les informations de connexion
    void initializeStorage();
    bool nonSuperUserExists(); // Vérifie si un utilisateur autre que le super utilisateur existe

private:
    QString filename; // Nom du fichier de stockage des utilisateurs
    QString userFilePath; // Chemin vers le fichier utilisateur
    // Ajoutez ici des méthodes et attributs supplémentaires nécessaires pour la gestion des fichiers
};

#endif // USERSTORAGE_H
