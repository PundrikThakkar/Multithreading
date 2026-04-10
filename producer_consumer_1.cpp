// 2 producer , 1 queue, 3 consumer, whenever anyone access the queue other 4 will stop.

#include<bits/stdc++.h>
using namespace std;

mutex m;
condition_variable cv;

queue<pair<int,int> > q;

int limit=10;
bool finished=false;
int done=0;
void producer(int id){
    for(int i=0;i<limit;i++){
        {
            lock_guard<mutex> lock(m);
            cout<<"Thread : "<<id<<" , produced item : "<<i<<endl;
            q.push({id,i});
        }
        cv.notify_one();
    }

    {
        lock_guard<mutex> lock(m);
        done++;
        cout<<"Thread : "<<id<<"'s work done !"<<endl;
        if(done==2){
            finished=true;
            cv.notify_all();
        }
    }


}

void consumer(int id){
    while(true){
        {
            unique_lock<mutex> lock(m);
            cv.wait(lock,[]{return !q.empty()||finished;});
            if(!q.empty()){
                cout<<"consumer : "<<id<<" consumes item produced by "<<q.front().first<<" , Item : "<<q.front().second<<endl;
                q.pop();
            }else if(finished){
                break;
            }
        }
    }
}


int main(){
    thread t1(producer,1);
    thread t2(producer,2);
    thread t3(consumer,1);
    thread t4(consumer,2);
    thread t5(consumer,3);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    return 0;
}