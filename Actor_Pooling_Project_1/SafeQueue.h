#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class SafeQueue {
private:
    std::mutex m_;
    std::queue<T> q_;
    std::condition_variable cv_;

public:
    void push(T value) {
        {
            std::lock_guard<std::mutex> lock(m_);
            q_.push(value);
        }
        cv_.notify_one();
    }

    // blocking pop
    T pop() {
        std::unique_lock<std::mutex> lock(m_);
        cv_.wait(lock, [this] { return !q_.empty(); });
        T value = q_.front();
        q_.pop();
        return value;
    }

    // non-blocking
    bool try_pop(T &value) {
        std::lock_guard<std::mutex> lock(m_);
        if (q_.empty()) return false;
        value = q_.front();
        q_.pop();
        return true;
    }

    bool empty() {
        std::lock_guard<std::mutex> lock(m_);
        return q_.empty();
    }
};