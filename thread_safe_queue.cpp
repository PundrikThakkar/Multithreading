#include<bits/stdc++.h>
using namespace std;


template<typename T>
class SafeQueue{
    private :
        mutex m_;
        queue<T> q_;
        condition_variable cv_;

    public:
        void push(T element){
            {
                lock_guard<mutex> lock(m_);
                q_.push(element);
            }
            cv.notify_one();
        }

        T pop(){
            unique_lock<mutex> lock(m_);
            cv_.wait(lock,[this]{return !q_.empty();});
            T element=move(q_.front());
            q_.pop();
            return element;
        }
};