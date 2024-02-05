#include "UserRights.h"

UserRights::UserRights(bool canView, bool canEdit, bool isAdmin)
    : viewPermission(canView), editPermission(canEdit), adminPermission(isAdmin) {
}

UserRights::~UserRights() {
    // Le destructeur est ici pour compléter l'implémentation, mais n'a pas besoin de logique spécifique
    // puisque nous utilisons uniquement des types de base qui ne nécessitent pas de nettoyage manuel.
}

bool UserRights::canView() const {
    return viewPermission;
}

bool UserRights::canEdit() const {
    return editPermission;
}

bool UserRights::isAdmin() const {
    return adminPermission;
}
