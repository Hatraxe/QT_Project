#ifndef PROFILE_H
#define PROFILE_H

#include <QString>

class Profile {
public:
    Profile(const QString &name);
    ~Profile();

    QString getName() const; // Renvoie le nom du profil

private:
    QString name; // Nom du profil
    // Ajoutez ici des attributs supplémentaires pour les paramètres du profil
};

#endif // PROFILE_H
