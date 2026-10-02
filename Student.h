#ifndef STUDENT_H
#define STUDENT_H

#include "Borrower.h"

class Student : public Borrower {
public:
    Student();
    Student(string id, string name);
    ~Student();

    void displayInfo(); // Runtime polymorphism
};

#endif
