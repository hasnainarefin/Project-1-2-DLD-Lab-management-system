#include "FileManager.h"
#include <sstream>

void FileManager::saveEquipment(vector<Equipment>& equipmentList) {
    ofstream file("equipment.txt");

    for (int i = 0; i < (int)equipmentList.size(); i++) {
        file << equipmentList[i].getID() << "|"
             << equipmentList[i].getName() << "|"
             << equipmentList[i].getTotalQuantity() << "|"
             << equipmentList[i].getAvailableQuantity() << endl;
    }

    file.close();
}

void FileManager::loadEquipment(vector<Equipment>& equipmentList) {
    ifstream file("equipment.txt");

    if (!file) {
        // Array of objects
        Equipment defaultEquipments[5] = {
            Equipment(101, "Breadboard", 20, 20),
            Equipment(102, "IC_7408", 50, 50),
            Equipment(103, "Multimeter", 5, 5),
            Equipment(104, "Jumper_Wire", 100, 100),
            Equipment(105, "Logic_Probe", 10, 10)
        };

        for (int i = 0; i < 5; i++) {
            equipmentList.push_back(defaultEquipments[i]);
        }

        return;
    }

    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, total, available;

        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, total, '|');
        getline(ss, available, '|');

        if (!id.empty()) {
            equipmentList.push_back(
                Equipment(stoi(id), name, stoi(total), stoi(available))
            );
        }
    }

    file.close();
}

void FileManager::saveBorrowRecords(vector<BorrowRecord>& records) {
    ofstream file("borrow_records.txt");

    for (int i = 0; i < (int)records.size(); i++) {
        file << records[i].getStudentID() << "|"
             << records[i].getStudentName() << "|";

        vector<int> ids = records[i].getEquipmentIDs();
        vector<int> qty = records[i].getQuantities();

        for (int j = 0; j < (int)ids.size(); j++) {
            file << ids[j] << ":" << qty[j];

            if (j != (int)ids.size() - 1) {
                file << ",";
            }
        }

        file << endl;
    }

    file.close();
}

void FileManager::loadBorrowRecords(vector<BorrowRecord>& records) {
    ifstream file("borrow_records.txt");

    if (!file) {
        return;
    }

    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string studentID, studentName, items;

        getline(ss, studentID, '|');
        getline(ss, studentName, '|');
        getline(ss, items, '|');

        if (studentID.empty()) {
            continue;
        }

        BorrowRecord record(studentID, studentName);

        stringstream itemStream(items);
        string item;

        while (getline(itemStream, item, ',')) {
            stringstream pairStream(item);
            string equipmentID, quantity;

            getline(pairStream, equipmentID, ':');
            getline(pairStream, quantity, ':');

            if (!equipmentID.empty() && !quantity.empty()) {
                record.addItem(stoi(equipmentID), stoi(quantity));
            }
        }

        records.push_back(record);
    }

    file.close();
}

void FileManager::savePassword(string password) {
    ofstream file("password.txt");
    file << password;
    file.close();
}

string FileManager::loadPassword() {
    ifstream file("password.txt");

    if (!file) {
        return "1234";
    }

    string password;
    getline(file, password);

    file.close();

    if (password.empty()) {
        return "1234";
    }

    return password;
}
