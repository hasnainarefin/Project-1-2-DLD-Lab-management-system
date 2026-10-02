#include "Student.h"

Student::Student() : User() {
}

Student::Student(string id, string name) : User(id, name) {
}

Student::~Student() {
}

void Student::displayInfo() {
    cout << "Student ID: " << id << endl;
    cout << "Student Name: " << name << endl;
}
