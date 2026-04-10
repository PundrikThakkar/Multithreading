#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <chrono>
using namespace std;

template <typename T>
class SafeQueue {
private:
    queue<T> q_;
    mutex m_;
    condition_variable cv_;

public:
    void push(T val) {
        {
            lock_guard<mutex> lock(m_);
            q_.push(val);
        }
        cv_.notify_one();
    }

    T pop() {
        unique_lock<mutex> lock(m_);
        cv_.wait(lock, [this]() { return !q_.empty(); });
        T val = move(q_.front());
        q_.pop();
        return val;
    }
};