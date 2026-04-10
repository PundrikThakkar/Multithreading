#include<bits/stdc++.h>
using namespace std;
#include<mutex>
#include<thread>

mutex m;
int counter=0;


void increment(int id){
    for(int i=0;i<10000;i++){
        lock_guard<mutex> lock(m);
        counter++;
        cout<<"counter upgraded by thread : "<<id<<endl;
    }
}

int main(){
    thread t1(increment,1);
    thread t2(increment,2);
    t1.join();
    t2.join();
}
