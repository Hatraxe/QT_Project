#ifndef USERSERIALIZER_H
#define USERSERIALIZER_H

#include <QList>
#include "User.h"

class UserSerializer {
public:
    static bool serializeToFile(const QList<User>& users, const QString& filename);
};

#endif // USERSERIALIZER_H
