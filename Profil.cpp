#include "Profile.h"

Profile::Profile(const QString &name) : name(name) {
}

Profile::~Profile() {
    // Ici, on pourrait libérer des ressources si nécessaire, mais pour un QString, ce n'est pas requis.
}

Profile::Profile(const Profile& other) : name(other.name) {
    // Le constructeur de recopie copie simplement le nom de l'autre profil
}

QString Profile::getName() const {
    return name;
}
