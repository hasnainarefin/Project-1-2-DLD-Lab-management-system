#ifndef BORROWRECORD_H
#define BORROWRECORD_H

#include <iostream>
#include <vector>
using namespace std;

class BorrowRecord {
private:
    string studentID;
    string studentName;
    vector<int> equipmentIDs;
    vector<int> quantities;

public:
    BorrowRecord();
    BorrowRecord(string studentID, string studentName);
    ~BorrowRecord();

    void addItem(int equipmentID, int quantity);
    bool hasEnoughItem(int equipmentID, int quantity);
    void returnItem(int equipmentID, int quantity);

    void display();

    string getStudentID();
    string getStudentName();

    vector<int> getEquipmentIDs();
    vector<int> getQuantities();

    bool isEmpty();
};

#endif
