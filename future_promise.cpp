#include<bits/stdc++.h>
using namespace std;

void work(promise<int> p){
    p.set_value(10);
}

int main(){
    promise<int> p;
    future<int> f=p.get_future();
    
    thread t(work,move(p));
    cout<<f.get()<<endl;
    t.join();
    return 0;
}