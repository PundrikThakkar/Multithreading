// single write , multiple read operation 
// reader - writer starvation issue
// can use shared_lock only with shared_mutex

#include<bits/stdc++.h>
using namespace std;

shared_mutex sm;
int d=0;

void reader(){
    shared_lock<shared_mutex> lock(sm);
    cout<<"Data : "<<d<<endl;
    return;
}

void writer(){
    unique_lock<shared_mutex> lock(sm);
    d++;
    cout<<"Write : "<<d<<endl;
    return;
}

int main(){
    thread t1(reader);
    thread t2(reader);
    thread t3(writer);
    thread t4(reader);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}