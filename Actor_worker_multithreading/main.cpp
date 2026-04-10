#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <chrono>
#include "SafeQueue.h"
#include "Restaurant.h"

using namespace std;

void work(vector<Restaurant*>& restaurants, SafeQueue<int>& readyQueue) {
    while (true) {
        int id=readyQueue.pop();
        if(id==-1) break;
        restaurants[id]->delivery();
    }
}

int main() {
    int num_orders = 1000;
    int num_restaurants = 100;

    vector<Restaurant*> restaurants(num_restaurants);
    SafeQueue<int> readyQueue;

    for (int i = 0; i < num_restaurants; i++) {
        restaurants[i] = new Restaurant(i);
    }

    vector<thread> delivery_workers;

    for (int i = 0; i < 4; i++) {
        delivery_workers.push_back(thread(work, ref(restaurants), ref(readyQueue)));
    }

    vector<future<void>> orders;

    for (int i = 0; i < num_orders; i++) {
        orders.push_back(async(launch::async, [&, i]() {
            int restaurant_num = rand() % 100;
            int recipe_num = rand() % 10;
            restaurants[restaurant_num]->placeOrder(recipe_num, readyQueue);
        }));
    }

    for (auto& o : orders) o.get();
    
    for(int i=0;i<4;i++) readyQueue.push(-1);

    for (auto& t : delivery_workers) {
        t.join();
    }

    return 0;
}