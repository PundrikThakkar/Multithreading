#include<iostream>
#include<thread>
using namespace std;

void work(int id){
    cout<<"Thread : "<<id<<endl;
    return;
}

int main(){
    thread t1(work,1);
    thread t2(work,2);
    cout<<"currently running : "<<thread::hardware_concurrency()<<endl;
    t1.detach();
    // t2.join();


    return 0;
}