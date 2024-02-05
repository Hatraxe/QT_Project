#include "Profile.h"

Profile::Profile(const QString &name) : name(name) {
}

Profile::~Profile() {
    // Ici, vous pourriez libérer des ressources si nécessaire, mais pour un QString, ce n'est pas requis.
}

QString Profile::getName() const {
    return name;
}
