// 02-sleep.cpp
// 让程序在特定时间休眠

#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace chrono_literals;    // 包含一段时间的缩略值

int main(){
    cout << "Going to sleep for 5 seconds and 300 milli seconds" << endl;   
    this_thread::sleep_for(5s + 200ms); // sleep_for()对当前线程进行限时阻塞，接受一个相对的值，如此简洁的时间表达方式在std::chrono_literals命名空间中
    cout << "Going to sleep for another 3 seconds" << endl; 
    this_thread::sleep_until(chrono::high_resolution_clock::now() + 3s);    // sleep_until接受用绝对时间来表示

    cout << "That's it" << endl;
}