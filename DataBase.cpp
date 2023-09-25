#include <iostream>
#include <string>
#include <map>
#include <mutex>
#include "FileIO.h"
#include "DataBase.h"
using namespace std;

void DataBase::build(const char* data_file) {
    FileIO file;
    auto vec = file.read_product_xml("ProductPrice.xml");
    if (vec) {
        for (auto& v : *vec) {
            //cout << get<0>(v) << " ";
            //cout << get<1>(v) << " ";
            //cout << get<2>(v) << " ";
            //cout << endl;
            db.insert({ get<1>(v), make_tuple(get<0>(v), get<2>(v)) });
        }
    }
}

string DataBase::_hex_char_to_bin(char hex) {
    string bin;
    switch (hex) {
    case '0':
        bin = "0000";
        break;
    case '1':
        bin = "0001";
        break;
    case '2':
        bin = "0010";
        break;
    case '3':
        bin = "0011";
        break;
    case '4':
        bin = "0100";
        break;
    case '5':
        bin = "0101";
        break;
    case '6':
        bin = "0110";
        break;
    case '7':
        bin = "0111";
        break;
    case '8':
        bin = "1000";
        break;
    case '9':
        bin = "1001";
        break;
    case 'A':
    case 'a':
        bin = "1010";
        break;
    case 'B':
    case 'b':
        bin = "1011";
        break;
    case 'C':
    case 'c':
        bin = "1100";
        break;
    case 'D':
    case 'd':
        bin = "1101";
        break;
    case 'E':
    case 'e':
        bin = "1110";
        break;
    case 'F':
    case 'f':
        bin = "1111";
        break;
    }

    return bin;
}

string DataBase::_hex_to_binary(const string& hex) {
    string binary;

    for (int i = 0; i < hex.size(); i += 3) {
        binary += hex[i];
        //cout << binary << endl;
        binary += _hex_char_to_bin(hex[i + 1]);
        //cout << binary << endl;
        binary += _hex_char_to_bin(hex[i + 2]);
        //cout << binary << endl;
    }

    return binary;
}

void DataBase::get_product_info(string barcode, shared_ptr<Product_Info> data) {
    tuple<string, float> product_info;
    string bin_barcode = _hex_to_binary(barcode);

    lock_guard<mutex> locker(mtx);
    //mtx.lock();
    map<string, tuple<string, float>>::iterator it;
    it = db.find(bin_barcode);
    if (it == db.end())
        cout << "Product " << barcode << " " << bin_barcode << " not found" << endl;
    else {
        product_info = it->second;
        //cout << "Barcode: " << bin_barcode << endl;
        //cout << get<0>(product_info) << "   " << get<1>(product_info) << endl;
        data->name = get<0>(product_info);
        data->price = get<1>(product_info);
    }
    //mtx.unlock();
}
