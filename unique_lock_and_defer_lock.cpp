#include<bits/stdc++.h>
#include<thread>
#include<mutex>
using namespace std;

mutex m;


void work(int id){
    unique_lock<mutex> lock(m,defer_lock);

    cout<<"Read by thread : "<<id<<endl;


    lock.lock();

    cout<<"Write by thread : "<<id<<endl;

    lock.unlock();
}

int main(){
    thread t1(work,1);
    thread t2(work,2);

    t1.join();
    t2.join();
    return 0;
}