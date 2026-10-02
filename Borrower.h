#ifndef BORROWER_H
#define BORROWER_H

#include "User.h"

// Virtual Base Class Example
class Borrower : virtual public User {
public:
    Borrower();
    virtual ~Borrower();
};

#endif
