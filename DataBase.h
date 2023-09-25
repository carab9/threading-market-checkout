#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <string>
#include <map>
#include <mutex>
using namespace std;

struct Product_Info {
    string name;
    float price;
};

class DataBase {
private:
    map<string, tuple<string, float>> db;

    mutex mtx;

    string _hex_to_binary(const string& hex);

    string _hex_char_to_bin(char hex);

public:
    DataBase() {}

    void build(const char* data_file);

    void get_product_info(string barcode, shared_ptr<Product_Info>);
};

#endif // DATABASE_H