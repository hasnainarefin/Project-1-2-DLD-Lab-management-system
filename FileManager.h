#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <fstream>
#include <vector>
#include "Equipment.h"
#include "BorrowRecord.h"

using namespace std;

class FileManager {
public:
    static void saveEquipment(vector<Equipment>& equipmentList);
    static void loadEquipment(vector<Equipment>& equipmentList);

    static void saveBorrowRecords(vector<BorrowRecord>& records);
    static void loadBorrowRecords(vector<BorrowRecord>& records);

    static void savePassword(string password);
    static string loadPassword();
};

#endif
