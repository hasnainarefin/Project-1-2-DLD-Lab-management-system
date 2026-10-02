#include "Equipment.h"

int Equipment::equipmentCount = 0;

Equipment::Equipment() {
    equipmentID = 0;
    name = "";
    totalQuantity = 0;
    availableQuantity = 0;
    equipmentCount++;
}

Equipment::Equipment(int id, string name, int total, int available) {
    equipmentID = id;
    this->name = name;
    totalQuantity = total;
    availableQuantity = available;
    equipmentCount++;
}

Equipment::~Equipment() {
}

void Equipment::display() {
    cout << equipmentID << "\t"
         << name << "\t\t"
         << totalQuantity << "\t"
         << availableQuantity << endl;
}

void Equipment::addStock(int quantity) {
    totalQuantity += quantity;
    availableQuantity += quantity;
}

void Equipment::addStock(int quantity, string note) {
    totalQuantity += quantity;
    availableQuantity += quantity;
    cout << "Note: " << note << endl;
}

bool Equipment::borrowItem(int quantity) {
    if (quantity <= 0) {
        return false;
    }

    if (quantity <= availableQuantity) {
        availableQuantity -= quantity;
        return true;
    }

    return false;
}

void Equipment::returnItem(int quantity) {
    if (quantity <= 0) {
        return;
    }

    availableQuantity += quantity;

    if (availableQuantity > totalQuantity) {
        availableQuantity = totalQuantity;
    }
}

int Equipment::getID() {
    return equipmentID;
}

string Equipment::getName() {
    return name;
}

int Equipment::getTotalQuantity() {
    return totalQuantity;
}

int Equipment::getAvailableQuantity() {
    return availableQuantity;
}

int Equipment::getEquipmentCount() {
    return equipmentCount;
}

bool Equipment::operator==(const Equipment& other) {
    return equipmentID == other.equipmentID;
}

void showEquipmentDetails(Equipment e) {
    cout << "Equipment ID: " << e.equipmentID << endl;
    cout << "Name: " << e.name << endl;
    cout << "Total Quantity: " << e.totalQuantity << endl;
    cout << "Available Quantity: " << e.availableQuantity << endl;
}
