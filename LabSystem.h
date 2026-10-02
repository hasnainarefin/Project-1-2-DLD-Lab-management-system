#ifndef LABSYSTEM_H
#define LABSYSTEM_H

#include <iostream>
#include <vector>
#include "Equipment.h"
#include "BorrowRecord.h"
#include "LabAssistant.h"
#include "Student.h"
#include "FileManager.h"
#include "TemplateUtility.h"

using namespace std;

class LabSystem {
private:
    vector<Equipment> equipmentList;       // STL vector of objects
    vector<BorrowRecord> borrowRecords;    // STL vector of objects

    LabAssistant* assistant;               // Dynamic memory allocation

public:
    LabSystem();
    ~LabSystem();

    void start();
    bool login();

    void mainMenu();
    void managementMenu();

    void viewAllEquipment();
    void borrowEquipment();
    void returnEquipment();
    void viewBorrowReport();

    void addNewStock();
    void addNewEquipment();
    void deleteEquipment();
    void changePassword();

    int findEquipmentIndex(int equipmentID);
    int findBorrowRecordIndex(string studentID);
};

#endif
