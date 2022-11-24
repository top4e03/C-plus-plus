#include <iostream>

using namespace std;

#include "day5.h"

int main() {

    NodeList<int> list;
    list.insert_back(1);
    list.insert_back(2);
    list.insert_back(3);
    list.insert_front(0);
    list.insert_front(-1);

    cout << list.size() << endl;

    NodeList<int>::Iterator it = list.begin();
    cout << *(it) << endl;
    cout << *(++it) << endl;

    for(NodeList<int>::Iterator it = list.begin(); it != list.end(); ++it){

      cout << *(it) << endl;

    };

    cout << "-----" << endl;
    NodeList<int>::Iterator it2 = list.begin();
    ++it2;
    ++it2;
    ++it2;
    ++it2;

    return 0;
}
