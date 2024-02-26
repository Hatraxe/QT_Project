// UserDeserializer.h
#ifndef USERDESERIALIZER_H
#define USERDESERIALIZER_H

#include <QList>
#include "User.h"

class UserDeserializer {
public:
    static QList<User> deserializeFromFile(const QString& filename);
};

#endif // USERDESERIALIZER_H
