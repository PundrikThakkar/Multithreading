#include <bits/stdc++.h>
#include "Restaurant.h"
using namespace std;


void worker(vector<Restaurant*>& restaurants, SafeQueue<int>& ready_queue) {
    int orders=1000;
    while (orders--) {
        int r_id = ready_queue.pop();
        restaurants[r_id]->process_one(ready_queue);
    }
}

int main() {
    int num_restaurants = 100;
    int num_orders = 1000;

    SafeQueue<int> ready_queue;

    vector<Restaurant*> restaurants(num_restaurants);
    for (int i = 0; i < num_restaurants; i++) {
        restaurants[i] = new Restaurant(i);
    }


    vector<thread> workers;
    for (int i = 0; i < 4; i++) {
        workers.emplace_back(worker, ref(restaurants), ref(ready_queue));
    }


    vector<future<void>> customers;

    for (int i = 0; i < num_orders; i++) {
        customers.push_back(async(launch::async, [&, i]() {
            int r = rand() % num_restaurants;
            int recipe = rand() % 10;

            restaurants[r]->order(recipe, ready_queue);
        }));
    }


    for (auto &c : customers) c.get();


    this_thread::sleep_for(chrono::seconds(3));

    for(auto &t:workers) t.join();
    return 0;
}