#include "User.h"

User::User() {
    id = "";
    name = "";
}

User::User(string id, string name) {
    this->id = id;
    this->name = name;
}

User::~User() {
}
