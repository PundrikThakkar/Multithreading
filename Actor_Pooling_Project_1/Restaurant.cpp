#include "Restaurant.h"
#include <iostream>
using namespace std;

Restaurant::Restaurant(int id)
    : id_(id), in_ready_queue_(false) {}

void Restaurant::order(int recipe, SafeQueue<int>& ready_queue) {
    orders_.push(recipe);

    bool expected = false;
    if (in_ready_queue_.compare_exchange_strong(expected, true)) {
        ready_queue.push(id_);
    }
}

void Restaurant::process_one(SafeQueue<int>& ready_queue) {
    int recipe;

    if (!orders_.try_pop(recipe)) {
        in_ready_queue_ = false;
        return;
    }

    cout << "Restaurant " << id_
         << " processing recipe " << recipe << "\n";


    std::this_thread::sleep_for(std::chrono::milliseconds(10));


    if (!orders_.empty()) {
        ready_queue.push(id_);
    } else {
        in_ready_queue_ = false;
    }
}