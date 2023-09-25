#ifndef CART_H
#define CART_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <tuple>
#include "DataBase.h"
#include <chrono>
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;
using namespace std;

class Cart {
private:
    string cart_name;
    vector<string> barcodes;
    vector<tuple<string, float>> products;

public:
    Cart(const string& name, const vector<string>& codes) {
        cart_name = name;
        barcodes = codes;
    }
    ~Cart() {
        //cout << "Cart destructor called " << cart_name << endl;
    }

    void processing(DataBase& db);
};

#endif // CART_H
