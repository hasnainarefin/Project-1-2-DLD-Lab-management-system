#ifndef TEMPLATEUTILITY_H
#define TEMPLATEUTILITY_H

#include <vector>
using namespace std;

// Template function
template <class T>
void displayList(vector<T>& list) {
    for (int i = 0; i < (int)list.size(); i++) {
        list[i].display();
    }
}

#endif
