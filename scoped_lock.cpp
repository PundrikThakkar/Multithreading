// change to c++17 
// scoped_lock : deadlock avoidance.
#include<bits/stdc++.h>
using namespace std;

mutex m1,m2;

void work1(){
    scoped_lock l1(m1,m2);
    cout<<"Work 1 is done"<<endl;
}

void work2(){
    scoped_lock l1(m1,m2);
    cout<<"Work 2 is done"<<endl;
}

int main(){
    thread t1(work1);
    thread t2(work2);

    t1.join();
    t2.join();
    return 0;
}