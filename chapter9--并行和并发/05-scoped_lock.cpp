// 05-scoped_lock.cpp
// 避免死锁--std::scoped_lock

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
using namespace chrono_literals;

mutex mut_a;    // 实例化两个互斥量对象，制造死锁
mutex mut_b;

// 会死锁，一个要了a，一个要了b，然后都缺少互斥量，都阻塞
static void deadlock_func_1(){  // 先上锁a，后上锁b
    cout << "bad f1 acquiring mutex A..." << endl;
    lock_guard<mutex> la {mut_a};   // 上锁a
    this_thread::sleep_for(100ms);  // 休眠100ms
    cout << "bad f1 acquiring mutex B..." << endl;
    lock_guard<mutex> lb {mut_b};   // 上锁b
    cout << "bad f1 got both mutexes." << endl;
}

static void deadlock_func_2(){  // 先上锁b，后上锁a
    cout << "bad f2 acquiring mutex B..." << endl;
    lock_guard<mutex> lb {mut_b};   // 上锁b
    this_thread::sleep_for(100ms);  // 休眠100ms
    cout << "bad f2 acquiring mutex A..." << endl;
    lock_guard<mutex> la {mut_a};   // 上锁a
    cout << "bad f2 got both mutexes." << endl;
}

static void sane_func_1(){  // 无死锁版本函数，scoped_lock()构造函数会给所有互斥量上锁，析构函数会解锁
    scoped_lock l {mut_a, mut_b};
    cout << "sane f1 got both mutexes." << endl;
}

static void sane_func_2(){
    scoped_lock l {mut_b, mut_a};
    cout << "sane f1 got both mutexes." << endl;
}

int main(){
    {   // 使用不会死锁的函数
        thread t1 {sane_func_1};
        thread t2 {sane_func_2};

        t1.join();
        t2.join();
    }

    {   // 使用会死锁的函数
        thread t1 {deadlock_func_1};
        thread t2 {deadlock_func_2};

        t1.join();
        t2.join();
    }
}