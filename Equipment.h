#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <iostream>
using namespace std;

class Equipment {
private:
    int equipmentID;
    string name;
    int totalQuantity;
    int availableQuantity;

    static int equipmentCount; // Static member

public:
    Equipment();
    Equipment(int id, string name, int total, int available);
    ~Equipment();

    void display();

    void addStock(int quantity);
    void addStock(int quantity, string note); // Function overloading

    bool borrowItem(int quantity);
    void returnItem(int quantity);

    int getID();
    string getName();
    int getTotalQuantity();
    int getAvailableQuantity();

    static int getEquipmentCount();

    bool operator==(const Equipment& other); // Operator overloading

    friend void showEquipmentDetails(Equipment e); // Friend function
};

#endif
