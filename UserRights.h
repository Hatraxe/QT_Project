#ifndef USERRIGHTS_H
#define USERRIGHTS_H

class UserRights {
public:
    UserRights(bool canView, bool canEdit, bool isAdmin);
    ~UserRights();

    bool canView() const; // Vérifie si l'utilisateur peut visualiser
    bool canEdit() const; // Vérifie si l'utilisateur peut éditer
    bool isAdmin() const; // Vérifie si l'utilisateur est un administrateur

private:
    bool viewPermission;
    bool editPermission;
    bool adminPermission;
};

#endif // USERRIGHTS_H
