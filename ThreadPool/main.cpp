#include<iostream> 
#include<vector>
#include<queue>
#include<mutex>
#include<thread>
#include<chrono>
#include<condition_variable>
#include<functional>
#include<atomic>
#include<future>
#include<shared_mutex>
using namespace std;

int func(int x){
    this_thread::sleep_for(chrono::seconds(2));
    cout<<"This is a time taking function with value : "<<endl;
    return x;
}

class ThreadPool{
private:
    int num_threads_;
    mutex m_;
    atomic<bool> stop_;
    condition_variable cv_;
    vector<thread> threads_;
    queue<function<void()> > tasks_;

public:
    ThreadPool(int num_threads){
        num_threads_=num_threads;
        stop_=false;
        for(int i=0;i<num_threads_;i++){
            threads_.emplace_back([this]{
                function<void()> task;
                while(1){
                    unique_lock<mutex> lock(m_);
                    cv_.wait(lock,[this](){return (!tasks_.empty()) || (stop_ ); });
                    if(stop_){
                        return;
                    }
                    task=move(tasks_.front());
                    tasks_.pop();
                    lock.unlock();
                    task();
                }
            });
        }
    }

    template<class F,class... Args>
    auto Execute(F&& f,Args&&... args) -> future<decltype(f(args...))> {
        using return_type=decltype(f(args...));

        auto task=make_shared<packaged_task<return_type()>>(bind(forward<F>(f),forward<Args>(args)...));

        future<return_type> res=task->get_future();

        unique_lock<mutex> lock(m_);

        tasks_.push([task]()->void{
            (*task)();
        });

        lock.unlock();

        cv_.notify_one();

        return res;
    }

    ~ThreadPool(){
        stop_=true;
        cv_.notify_all();

        for(auto &t:threads_){
            if(t.joinable()) t.join();
        }

    }
};


int main(){
    ThreadPool pool(8);
    future<int> res=pool.Execute(func,2);
    cout<<"Result is : "<<res.get()<<endl;
    return 0;
}