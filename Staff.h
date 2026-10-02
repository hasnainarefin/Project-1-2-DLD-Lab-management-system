#ifndef STAFF_H
#define STAFF_H

#include "User.h"

// Virtual Base Class Example
class Staff : virtual public User {
public:
    Staff();
    virtual ~Staff();
};

#endif
