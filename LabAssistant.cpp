#include "LabAssistant.h"

LabAssistant::LabAssistant() : User() {
    password = "1234";
}

LabAssistant::LabAssistant(string id, string name, string password)
    : User(id, name) {
    this->password = password;
}

LabAssistant::~LabAssistant() {
}

bool LabAssistant::login(string inputPassword) {
    return password == inputPassword;
}

void LabAssistant::changePassword(string newPassword) {
    password = newPassword;
}

string LabAssistant::getPassword() {
    return password;
}

void LabAssistant::displayInfo() {
    cout << "Lab Assistant ID: " << id << endl;
    cout << "Name: " << name << endl;
}
