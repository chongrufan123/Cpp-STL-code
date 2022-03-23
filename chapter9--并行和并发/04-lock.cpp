// 04-lock.cpp
// 打造异常安全的共享锁--std::unique_lock和std::shared_lock

#include <iostream>
#include <shared_mutex>
#include <thread>
#include <vector>

using namespace std;
using namespace chrono_literals;

shared_mutex shared_mut;    // 定义一个全局实例

using shrd_lck = shared_lock<shared_mutex>; // 两个RAII辅助者
using uniq_lck = unique_lock<shared_mutex>;

static void print_exclusive(){
    uniq_lck l {shared_mut, defer_lock};    // unique_lock实例作为共享互斥锁，第二个参数告诉对象让锁处在解锁状态，否则互斥量上锁
    if(l.try_lock()){   // bool互斥量
        cout << "Got exclusive lock." << endl;
    }
    else{
        cout << "Unable to lock exclusively." << endl;
    }
}

static void exclusive_throw(){  // 将程序阻塞，直到获得相应的锁，抛出异常模拟发生错误
    uniq_lck l {shared_mut};
    throw 123;
}

int main(){
    {
        shrd_lck sl1 {shared_mut};  // 实例化一个shared_lock实例，对共享模式下的互斥量上锁

        cout << "shared lock once." << endl;
    }
    {
        shrd_lck sl2 {shared_mut};  // 实例化第二个shared_lock实例，使用同一个互斥量
        cout << "shared lock twice." << endl;
        print_exclusive();
    }   // 离开代码段，析构函数释放互斥量的共享锁
    cout << "lock is free" << endl;
    // 此时所有的shared_lock对象被销毁，互斥量解锁
    try {
        exclusive_throw();
    }
    catch(int e){
        cout << "Got exception " << e << endl;
    }
    print_exclusive();
}

