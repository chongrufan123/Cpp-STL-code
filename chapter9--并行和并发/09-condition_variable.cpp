// 09-condition_variable.cpp
// 实现生产者/消费者模型--std::condition_variable

#include <iostream>
#include <queue>
#include <tuple>
#include <condition_variable>
#include <thread>

using namespace std;
using namespace chrono_literals;

queue<size_t> q;
mutex mut;
condition_variable cv;
bool finished {false};  // 告诉生产者无须再生产

static void producer(size_t items){ // 生产者函数，接受参数items，生产者生产的最大数量
    for(size_t i {0}; i < items; ++i){
        // this_thread::sleep_for(100ms);  // 隔100ms生产一个商品
        {
            cout << "Produce " << i << " at queue." << endl;
            lock_guard<mutex> lk {mut}; // 上锁
            q.push(i);
        }
        cv.notify_all();    // 叫醒消费线程
    }
    {
        lock_guard<mutex> lk {mut}; // 生产完商品之后再度上锁
        finished = true;    // 表示生产结束
    }
    cv.notify_all();    // 叫醒消费线程

}

static void consumer() {    // 消费者函数，对队列上的数值进行消费
    while(!finished){   // 当还没有生产结束
        unique_lock<mutex> l {mut}; // 对保护队列互斥量上锁
        cv.wait(l, [] {return !q.empty() || finished;});    // 如果生产者线程还在工作，并还有商品的话，消费者线程就不能停下来
        while (!q.empty()){ // 取得商品
            cout << "Got " << q.front() << " from queue.\n";
            q.pop();
        }
    }
}

int main(){
    thread t1 {producer, 5000000000};
    thread t2 {consumer};
    t1.join();
    t2.join();
    cout << "finished!\n";
}



