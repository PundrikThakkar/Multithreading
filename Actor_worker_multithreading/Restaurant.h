#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <chrono>
#include "SafeQueue.h"

using namespace std;

class Restaurant {
private:
    SafeQueue<int> orders_;
    int id_;
    mutex m_;

public:
    Restaurant(int id) {
        id_ = id;
    }

    void placeOrder(int recipe, SafeQueue<int>& readyRestaurants) {
        orders_.push(recipe);
        readyRestaurants.push(id_);
    }

    void delivery() {
        int item;
        {
            unique_lock<mutex> lock(m_);
            item = orders_.pop();
            cout << "Delivery from restaurant : " << id_
                 << " with order: " << item << " Started." << endl;
        }

        this_thread::sleep_for(chrono::seconds(1));

        {
            unique_lock<mutex> lock(m_);
            cout << "Delivery of restaurant : " << id_
                 << " with order: " << item << " Completed." << endl;
        }
    }
};