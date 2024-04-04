// UserRights.h

#ifndef USERRIGHTS_H
#define USERRIGHTS_H

class UserRights {
public:
    UserRights(bool canView = false, bool canEdit = false, bool isAdmin = false)
        : viewPermission(canView), editPermission(canEdit), adminPermission(isAdmin) {}



    ~UserRights() {}

    bool canView() const { return viewPermission; }
    bool canEdit() const { return editPermission; }
    bool isAdmin() const { return adminPermission; }

    // Setters
    void setCanView(bool canView) { viewPermission = canView; }
    void setCanEdit(bool canEdit) { editPermission = canEdit; }
    void setIsAdmin(bool isAdmin) { adminPermission = isAdmin; }

private:
    bool viewPermission;
    bool editPermission;
    bool adminPermission;
};

#endif // USERRIGHTS_H
