#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <thread>
#include <chrono>
#include "DataBase.h"
#include "Cart.h"
using namespace std;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

void Cart::processing(DataBase& db) {
    for (string b : barcodes) {
        shared_ptr<Product_Info> data(new Product_Info());
        thread th(&DataBase::get_product_info, ref(db), b, ref(data));
        th.join();
        products.push_back(make_tuple(data->name, data->price));
    }

    ofstream outfile;
    float total = 0.0;

    uint64_t millisec_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    string filename = cart_name + "_" + to_string(millisec_time) + ".txt";
    outfile.open(filename);
    if (outfile.is_open()) {
        for (tuple<string, float> p : products) {
            //cout << get<0>(p) << " " << get<1>(p) << endl;

            outfile << get<0>(p) << " $" << get<1>(p) << endl;
            total += get<1>(p);
        }
        outfile << "Total: " << total << endl;
        outfile.close();
    }
}
