#ifndef QUEUE_MANAGER_H
#define QUEUE_MANAGER_H

#include <string>
#include <vector>
#include <tuple>
#include <deque>
#include <mutex>
#include <condition_variable>
#include <thread>
#include "DataBase.h"
#include "Cart.h"
using namespace std;

class Queue {
private:
    deque<shared_ptr<Cart>> carts;
    mutex mtx;
    condition_variable cv;

public:
    Queue() {}

    void run(DataBase& db);

    void add_cart(string name, const vector<string>& barcodes);

    int size() {
        lock_guard<mutex> locker(mtx);
        return carts.size();
    }
};

class Queue_Manager {
private:
    vector<shared_ptr<Queue>> queues;
    vector<tuple<string, vector<string>>> carts;
    vector<shared_ptr<thread>> threads;

public:
    Queue_Manager() {}

    void build_queues(const char* cart_file, int num_queues);

    void run_queues(DataBase& db);
};

#endif // QUEUE_MANAGER_H
