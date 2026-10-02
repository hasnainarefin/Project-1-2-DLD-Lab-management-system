#ifndef USER_H
#define USER_H

#include <iostream>
using namespace std;

// Abstract Base Class
class User {
protected:
    string id;
    string name;

public:
    User();
    User(string id, string name);
    virtual ~User();

    virtual void displayInfo() = 0; // Pure virtual function
};

#endif
