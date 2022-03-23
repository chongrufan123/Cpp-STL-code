// 03-thread.cpp
// 启动和停止线程
// 编译时加入"-pthread"

#include <iostream>
#include <thread>

using namespace std;
using namespace chrono_literals;

static void thread_with_param(int i){   // 接受一个整型i，当做线程的id
    this_thread::sleep_for(1ms * i);    // 休眠时间，防止输出混乱
    cout << "Hello from thread " << i << endl;
    this_thread::sleep_for(1s * i);    // 假装工作一段时间
    cout << "Bye from thread " << i << endl;
}

int main(){
    cout << thread::hardware_concurrency() << " concurrent threads are supported.\n";    // 展示可以最多同时运行几个线程,16

    thread t1 {thread_with_param, 1};   // 启动线程
    thread t2 {thread_with_param, 2};
    thread t3 {thread_with_param, 3};
    thread t4 {thread_with_param, 4};
    thread t5 {thread_with_param, 5};
    thread t6 {thread_with_param, 6};
    thread t7 {thread_with_param, 7};
    thread t8 {thread_with_param, 8};
    thread t9 {thread_with_param, 9};
    thread t10 {thread_with_param, 10};
    thread t11 {thread_with_param, 11};
    thread t12 {thread_with_param, 12};

    t1.join();  // 等待t1线程结束之后才会继续往下走
    t2.join();

    t3.detach();    // 当主线程已经结束了，但是这个线程依然存活，但是操作系统当主线程终止之后就会之间把程序终止
    t12.join();

    cout << "Threads joined" << endl;

}