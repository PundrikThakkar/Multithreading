#include<bits/stdc++.h>
using namespace std;

mutex m1,m2;

void work1(){
    lock_guard<mutex> l1(m1);
    this_thread::sleep_for(chrono::milliseconds(100)); // making sleep thread for 1 sec
    lock_guard<mutex> l2(m2);

    cout<<"work 1 done"<<endl;
}

void work2(){
    lock_guard<mutex> l1(m2);
    this_thread::sleep_for(chrono::milliseconds(100)); // making sleep thread for 1 sec
    lock_guard<mutex> l2(m1);

    cout<<"work 2 done"<<endl;
}

int main(){
    thread t1(work1);
    thread t2(work2);

    t1.join();
    t2.join();

    return 0;
}