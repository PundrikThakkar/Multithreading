#pragma once
#include "SafeQueue.h"
#include <atomic>

class Restaurant {
private:
    int id_;
    SafeQueue<int> orders_;
    std::atomic<bool> in_ready_queue_;

public:
    Restaurant(int id);

    void order(int recipe, SafeQueue<int>& ready_queue);

    void process_one(SafeQueue<int>& ready_queue);
};