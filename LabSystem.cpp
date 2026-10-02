#include "LabSystem.h"
#include <cstdlib>
#include <limits>

// Clears terminal screen
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Waits until user presses Enter
void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

LabSystem::LabSystem() {
    FileManager::loadEquipment(equipmentList);
    FileManager::loadBorrowRecords(borrowRecords);

    string password = FileManager::loadPassword();

    // Memory allocation of object
    assistant = new LabAssistant("A101", "Lab Assistant", password);
}

LabSystem::~LabSystem() {
    FileManager::saveEquipment(equipmentList);
    FileManager::saveBorrowRecords(borrowRecords);
    FileManager::savePassword(assistant->getPassword());

    delete assistant;
}

void LabSystem::start() {
    clearScreen();

    if (login()) {
        clearScreen();
        mainMenu();
    } else {
        cout << "Access denied!" << endl;
    }
}

bool LabSystem::login() {
    string password;

    cout << "DLD LAB EQUIPMENT MANAGEMENT SYSTEM\n";
    cout << "-----------------------------------\n";
    cout << "Enter Lab Assistant Password: ";
    cin >> password;

    return assistant->login(password);
}

void LabSystem::mainMenu() {
    int choice;

    do {
        clearScreen();

        cout << "DLD LAB EQUIPMENT MANAGEMENT SYSTEM\n\n";
        cout << "1. View All Equipment\n";
        cout << "2. Borrow Equipment\n";
        cout << "3. Return Equipment\n";
        cout << "4. View Borrow Report\n";
        cout << "5. Management\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        clearScreen();

        switch (choice) {
        case 1:
            viewAllEquipment();
            pauseScreen();
            break;
        case 2:
            borrowEquipment();
            pauseScreen();
            break;
        case 3:
            returnEquipment();
            pauseScreen();
            break;
        case 4:
            viewBorrowReport();
            pauseScreen();
            break;
        case 5:
            managementMenu();
            break;
        case 6:
            cout << "Exiting system..." << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
            pauseScreen();
        }

    } while (choice != 6);
}

void LabSystem::managementMenu() {
    int choice;

    do {
        clearScreen();

        cout << "MANAGEMENT MENU\n\n";
        cout << "1. Add New Stock\n";
        cout << "2. Add New Equipment\n";
        cout << "3. Delete Equipment\n";
        cout << "4. Change Password\n";
        cout << "5. Back to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;

        clearScreen();

        switch (choice) {
        case 1:
            addNewStock();
            pauseScreen();
            break;
        case 2:
            addNewEquipment();
            pauseScreen();
            break;
        case 3:
            deleteEquipment();
            pauseScreen();
            break;
        case 4:
            changePassword();
            pauseScreen();
            break;
        case 5:
            break;
        default:
            cout << "Invalid choice!" << endl;
            pauseScreen();
        }

    } while (choice != 5);
}

void LabSystem::viewAllEquipment() {
    cout << "ID\tName\t\tTotal\tAvailable\n";
    cout << "----------------------------------------\n";

    // Template function
    displayList(equipmentList);
}

void LabSystem::borrowEquipment() {
    string studentID, studentName;
    int n;

    cout << "BORROW EQUIPMENT\n";
    cout << "----------------\n";

    cout << "Enter Student ID: ";
    cin >> studentID;

    cout << "Enter Student Name: ";
    cin >> studentName;

    Student student(studentID, studentName);

    // Pointer to derived class and runtime polymorphism
    User* userPtr = &student;
    userPtr->displayInfo();

    cout << "\nHow many types of equipment to borrow? ";
    cin >> n;

    int recordIndex = findBorrowRecordIndex(studentID);

    if (recordIndex == -1) {
        borrowRecords.push_back(BorrowRecord(studentID, studentName));
        recordIndex = (int)borrowRecords.size() - 1;
    }

    for (int i = 0; i < n; i++) {
        int equipmentID, quantity;

        cout << "\nEnter Equipment ID: ";
        cin >> equipmentID;

        cout << "Enter Quantity: ";
        cin >> quantity;

        int equipmentIndex = findEquipmentIndex(equipmentID);

        if (equipmentIndex == -1) {
            cout << "Equipment not found!" << endl;
        } else {
            if (equipmentList[equipmentIndex].borrowItem(quantity)) {
                borrowRecords[recordIndex].addItem(equipmentID, quantity);
                cout << "Borrow successful!" << endl;
            } else {
                cout << "Not enough available stock!" << endl;
            }
        }
    }
}

void LabSystem::returnEquipment() {
    string studentID;
    int n;

    cout << "RETURN EQUIPMENT\n";
    cout << "----------------\n";

    cout << "Enter Student ID: ";
    cin >> studentID;

    int recordIndex = findBorrowRecordIndex(studentID);

    if (recordIndex == -1) {
        cout << "No borrow record found!" << endl;
        return;
    }

    cout << "How many types of equipment to return? ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        int equipmentID, quantity;

        cout << "\nEnter Equipment ID: ";
        cin >> equipmentID;

        cout << "Enter Quantity: ";
        cin >> quantity;

        int equipmentIndex = findEquipmentIndex(equipmentID);

        if (equipmentIndex == -1) {
            cout << "Equipment not found!" << endl;
        } else if (!borrowRecords[recordIndex].hasEnoughItem(equipmentID, quantity)) {
            cout << "This student did not borrow this quantity!" << endl;
        } else {
            equipmentList[equipmentIndex].returnItem(quantity);
            borrowRecords[recordIndex].returnItem(equipmentID, quantity);
            cout << "Return successful!" << endl;
        }
    }

    if (borrowRecords[recordIndex].isEmpty()) {
        borrowRecords.erase(borrowRecords.begin() + recordIndex);
    }
}

void LabSystem::viewBorrowReport() {
    if (borrowRecords.empty()) {
        cout << "No equipment is currently borrowed." << endl;
        return;
    }

    cout << "BORROW REPORT\n";
    cout << "---------------------------\n";

    for (int i = 0; i < (int)borrowRecords.size(); i++) {
        borrowRecords[i].display();
        cout << "---------------------------\n";
    }
}

void LabSystem::addNewStock() {
    int equipmentID, quantity;

    cout << "ADD NEW STOCK\n";
    cout << "-------------\n";

    cout << "Enter Equipment ID: ";
    cin >> equipmentID;

    int index = findEquipmentIndex(equipmentID);

    if (index == -1) {
        cout << "Equipment not found!" << endl;
        return;
    }

    cout << "Enter Quantity to Add: ";
    cin >> quantity;

    equipmentList[index].addStock(quantity, "Stock updated by lab assistant");

    cout << "Stock added successfully!" << endl;
}

void LabSystem::addNewEquipment() {
    int id, total;
    string name;

    cout << "ADD NEW EQUIPMENT\n";
    cout << "-----------------\n";

    cout << "Enter New Equipment ID: ";
    cin >> id;

    if (findEquipmentIndex(id) != -1) {
        cout << "Equipment already exists!" << endl;
        return;
    }

    cout << "Enter Equipment Name: ";
    cin >> name;

    cout << "Enter Total Quantity: ";
    cin >> total;

    Equipment newEquipment(id, name, total, total);

    // Operator overloading example
    for (int i = 0; i < (int)equipmentList.size(); i++) {
        if (equipmentList[i] == newEquipment) {
            cout << "Equipment already exists!" << endl;
            return;
        }
    }

    equipmentList.push_back(newEquipment);

    cout << "New equipment added successfully!" << endl;

    // Friend function example
    showEquipmentDetails(newEquipment);
}

void LabSystem::deleteEquipment() {
    int id;

    cout << "DELETE EQUIPMENT\n";
    cout << "----------------\n";

    cout << "Enter Equipment ID to Delete: ";
    cin >> id;

    for (int i = 0; i < (int)equipmentList.size(); i++) {
        if (equipmentList[i].getID() == id) {
            equipmentList.erase(equipmentList.begin() + i);
            cout << "Equipment deleted successfully!" << endl;
            return;
        }
    }

    cout << "Equipment not found!" << endl;
}

void LabSystem::changePassword() {
    string newPassword;

    cout << "CHANGE PASSWORD\n";
    cout << "---------------\n";

    cout << "Enter New Password: ";
    cin >> newPassword;

    assistant->changePassword(newPassword);

    cout << "Password changed successfully!" << endl;
}

int LabSystem::findEquipmentIndex(int equipmentID) {
    for (int i = 0; i < (int)equipmentList.size(); i++) {
        if (equipmentList[i].getID() == equipmentID) {
            return i;
        }
    }

    return -1;
}

int LabSystem::findBorrowRecordIndex(string studentID) {
    for (int i = 0; i < (int)borrowRecords.size(); i++) {
        if (borrowRecords[i].getStudentID() == studentID) {
            return i;
        }
    }

    return -1;
}
