#include<iostream>
using namespace std;

template<typename T>
class uniqueptr{
private:
    T* ptr_;

public:

    uniqueptr(T* ptr=nullptr):ptr_(ptr){
        cout<<"constructor is called\n";
    }

    uniqueptr(const uniqueptr<T>& ptr)=delete;

    uniqueptr(uniqueptr<T>&& ptr){
        cout<<"constructor is called\n";
        ptr_=ptr.ptr_;
        ptr.ptr_=nullptr;
    }

    uniqueptr<T>& operator= (uniqueptr<T>& ptr) = delete;

    uniqueptr<T>& operator= (uniqueptr<T>&& ptr){
        if(this != &ptr){
            if(ptr_){
                delete ptr_;
            }
            ptr_=ptr.ptr_;
            ptr.ptr_=nullptr;
        }
        return *this;
    }

    
    T* operator-> () const{
        return ptr_;
    }
    
    T& operator* () const{
        return *ptr_;
    }
    
    T* get() const{
        return ptr_;
    }
    
    void reset(T* ptr=nullptr){
        if(ptr_){
            delete ptr_;
        }
        ptr_=ptr;
    }

    ~uniqueptr(){
        if(ptr_){
            delete ptr_;
        }
        ptr_=nullptr;
    }
};


int main(){

    uniqueptr<int> ptr1;// default constructor

    uniqueptr<int> ptr2(new int(5));// parameterized constructor;

    // uniqueptr<int> ptr3(ptr1);// copy constructor : compilation error
    uniqueptr<int> ptr4(move(ptr2));// move copy constructor

    // uniqueptr<int> ptr3=ptr1;// copy assignment constructor : compilation error
    // ptr1=ptr2;// copy assignment operator : compilation error
    uniqueptr<int> ptr5;

    ptr5=move(ptr4);// move copy assignment operator

    // ptr5->func(); // if there is any function exist (user define datatypes);

    cout<<(*ptr5)<<endl;

    cout<<"ran successfully!."<<endl;

    return 0;

}