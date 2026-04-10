#include<bits/stdc++.h>
#include "thread_safe_queue.cpp"
using namespace std;

class Actor{

public:    
    Actor():running_(true),worker_([this]{loop();}){}

    void send(int msg){
        queue_.push(msg);
    }

    ~Actor(){
        running_=false;
        queue_.push(-1);
        worker.join();
    }

private:

    void loop(){
        while(running_){
            int msg=queue_.pop();

            if(msg==-1) break;

            cout<<"Processing "<<msg<<"\n";
        }
    }

    SafeQueue<int> queue_;
    thread worker_;
    atomic<bool> running_;

};