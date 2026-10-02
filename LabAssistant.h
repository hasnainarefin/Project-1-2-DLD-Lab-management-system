#ifndef LABASSISTANT_H
#define LABASSISTANT_H

#include "Staff.h"

class LabAssistant : public Staff {
private:
    string password;

public:
    LabAssistant();
    LabAssistant(string id, string name, string password);
    ~LabAssistant();

    bool login(string inputPassword);
    void changePassword(string newPassword);
    string getPassword();

    void displayInfo();
};

#endif
