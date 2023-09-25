// ThreadingMarketCheckout.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "FileIO.h"
#include "DataBase.h"
#include "QueueManager.h"
using namespace std;

int main()
{
    FileIO file;

    /*
    auto vec = file.read_product_xml("ProductPrice.xml");
    for (auto& v : *vec) {
        cout << get<0>(v) << " ";
        cout << get<1>(v) << " ";
        cout << get<2>(v) << " ";
        cout << endl;
    }

    auto vec2 = file.read_carts_csv("Carts.csv");
    for (auto& v : *vec2) {
        cout << get<0>(v) << " ";
        for (auto& v2 : get<1>(v)) {
            cout << v2 << " ";
        }
        cout << endl;
    }
     */

    DataBase db;
    db.build("ProductPrice.xml");

    /*
    vector<string> barcodes;
    barcodes.push_back("016106118109016");
    barcodes.push_back("052109052109190");
    barcodes.push_back("142112043109046");
    barcodes.push_back("052109046016109");
    Cart cart("Cart298", barcodes);
    cart.processing(db);
    */

    /*
    Queue que;
    Queue que2;

    vector<string> barcodes2;
    barcodes2.push_back("046109043109142");
    barcodes2.push_back("14204C091118019");
    barcodes2.push_back("148109013016109");
    barcodes2.push_back("04304C01300D181");
    barcodes2.push_back("142109190112013");


    //que.run(db);

    thread th(&Queue::run, ref(que), ref(db));
    thread th2(&Queue::run, ref(que2), ref(db));

    vector<string> barcodes3;
    barcodes3.push_back("01618104901604C");
    barcodes3.push_back("058043112181013");
    barcodes3.push_back("10C112013118190");
    barcodes3.push_back("14810611204C046");

    que.add_cart("Cart298", barcodes);
    que.add_cart("Cart374", barcodes2);
    que2.add_cart("Cart366", barcodes3);

    th.join();
    th2.join();
    */

    Queue_Manager que_m;
    que_m.build_queues("Carts.csv", 10);
    que_m.run_queues(db);

    return 0;
}
