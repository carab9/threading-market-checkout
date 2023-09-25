#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <deque>
#include <mutex>
#include <condition_variable>
#include <thread>
#include "FileIO.h"
#include "QueueManager.h"
using namespace std;

mutex coutMu;
bool done;

void Queue::add_cart(string name, const vector<string>& barcodes) {
    unique_lock<mutex> locker(mtx);
    shared_ptr<Cart> cart(new Cart(name, barcodes));
    carts.push_back(cart);
    locker.unlock();
    cv.notify_all();
}

void Queue::run(DataBase& db) {
    while (true) {
        unique_lock<mutex> locker(mtx);
        if (done && carts.size() == 0) {
            break;
        }
        cv.wait(locker, [this]() {return carts.size() > 0; });
        shared_ptr<Cart> cart = carts.front();
        locker.unlock();
        cv.notify_all();
        cart->processing(db);
        locker.lock();
        carts.pop_front();
        locker.unlock();
    }

    /*
    unique_lock<mutex> locker(mtx);
    //locker.lock();
    int size = carts.size();
    locker.unlock();
    while (size > 0) {
        locker.lock();
        shared_ptr<Cart> cart = carts.front();
        locker.unlock();

        cart->processing(db);
        locker.lock();
        carts.pop_front();
        size = carts.size();
        locker.unlock();
    }
    */
}

void Queue_Manager::build_queues(const char* cart_file, int num_queues) {
    FileIO file;

    auto vec = file.read_carts_csv("Carts.csv");
    if (vec) {
        carts = *vec;
    }

    for (int i = 0; i < num_queues; i++) {
        shared_ptr<Queue> queue(new Queue());
        queues.push_back(queue);
    }
}

void Queue_Manager::run_queues(DataBase& db) {
    done = false;
    for (int i = 0; i < queues.size(); i++) {
        shared_ptr<thread> th(new thread(&Queue::run, ref(*queues[i]), ref(db)));
        threads.push_back(th);
    }

    int min_queue;

    int i = 0;
    while (i < carts.size()) {
        min_queue = 0;
        for (int i = 0; i < queues.size(); i++) {
            if (queues[min_queue]->size() <= queues[i]->size()) {}
            else {
                min_queue = i;
            }
        }

        coutMu.lock();
        cout << i << " add cart " << get<0>(carts[i]) << " " << get<1>(carts[i]).size() << endl;
        coutMu.unlock();
        queues[min_queue]->add_cart(get<0>(carts[i]), get<1>(carts[i]));
        i++;
    }

    done = true;
    for (auto& t : threads) {
        t->join();
    }
}
