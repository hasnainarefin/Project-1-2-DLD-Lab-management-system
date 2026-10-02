#include "BorrowRecord.h"

BorrowRecord::BorrowRecord() {
    studentID = "";
    studentName = "";
}

BorrowRecord::BorrowRecord(string studentID, string studentName) {
    this->studentID = studentID;
    this->studentName = studentName;
}

BorrowRecord::~BorrowRecord() {
}

void BorrowRecord::addItem(int equipmentID, int quantity) {
    for (int i = 0; i < (int)equipmentIDs.size(); i++) {
        if (equipmentIDs[i] == equipmentID) {
            quantities[i] += quantity;
            return;
        }
    }

    equipmentIDs.push_back(equipmentID);
    quantities.push_back(quantity);
}

bool BorrowRecord::hasEnoughItem(int equipmentID, int quantity) {
    for (int i = 0; i < (int)equipmentIDs.size(); i++) {
        if (equipmentIDs[i] == equipmentID && quantities[i] >= quantity) {
            return true;
        }
    }

    return false;
}

void BorrowRecord::returnItem(int equipmentID, int quantity) {
    for (int i = 0; i < (int)equipmentIDs.size(); i++) {
        if (equipmentIDs[i] == equipmentID) {
            quantities[i] -= quantity;

            if (quantities[i] <= 0) {
                equipmentIDs.erase(equipmentIDs.begin() + i);
                quantities.erase(quantities.begin() + i);
            }

            return;
        }
    }
}

void BorrowRecord::display() {
    cout << "Student ID: " << studentID << endl;
    cout << "Student Name: " << studentName << endl;

    cout << "Borrowed Equipment: ";

    for (int i = 0; i < (int)equipmentIDs.size(); i++) {
        cout << "[Equipment ID: " << equipmentIDs[i]
             << ", Quantity: " << quantities[i] << "] ";
    }

    cout << endl;
}

string BorrowRecord::getStudentID() {
    return studentID;
}

string BorrowRecord::getStudentName() {
    return studentName;
}

vector<int> BorrowRecord::getEquipmentIDs() {
    return equipmentIDs;
}

vector<int> BorrowRecord::getQuantities() {
    return quantities;
}

bool BorrowRecord::isEmpty() {
    return equipmentIDs.empty();
}
