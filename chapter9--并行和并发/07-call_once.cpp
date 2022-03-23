// 07-call_once.cpp
// 进行延迟初始化--std::call_once
// call_once()：一个线程达到call_once之后，其他线程都会被阻塞，第一个线程从准备函数返回之后，其他线程就结束了阻塞，用做当一个变量决定其他线程的运行的时候，线程必须对这个变量进行等待，如果call_once执行失败，下个线程会再次尝试执行，
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

once_flag callflag; // 对once_flag进行实例化
static void once_print(){   // 一个只需要执行一次的可怜函数
    cout << "!";
}

static void print(size_t x){    // 通过call_once调用once_print
    std::call_once(callflag, once_print);   
    cout << x;
}

int main(){
    vector<thread> v;
    for(size_t i {0}; i < 10; ++i){ // 启动10个线程
        v.emplace_back(print, i);   // 执行print函数
    }

    for(auto &t : v) {t.join();}
    cout << endl;
}

