// 10-condition_variable.cpp
// 实现多生产者/多消费者模型--std::condition_variable

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;
using namespace chrono_literals;

struct pcout : public stringstream {    // 同步打印辅助函数，参见06-thread_cout.cpp
    static inline mutex cout_mutex;
    ~pcout() {
        lock_guard<mutex> l {cout_mutex};
        cout << rdbuf();
    }
};

queue<size_t> q;    // 生产商品的队列
mutex q_mutex;      // 互斥量对队列进行保护
bool production_stooped {false};    // 告诉我们生产者是否已经停止生产

condition_variable go_produce;  // 提醒生产者生产
condition_variable go_consume;  // 提醒消费者消费

static void producer(size_t id, size_t items, size_t stock){    // 生产者函数，接受一个生产者id，所要生产的商品数量，囤积商品量的上限
    for (size_t i = 0; i < items; ++i){ // 循环生产
        unique_lock<mutex> lock(q_mutex);   // 对队列互斥量上锁
        go_produce.wait(lock, [&] {return q.size() < stock;});  // 对队列互斥量解锁，数量未达到囤积阈值时满足等待条件
        q.push(id * 100 + i);   // 商品放入队列
        pcout{} << " Producer " << id << " --> item " << setw(3) << q.back() << endl;   // 生产事件打印到终端
        go_consume.notify_all();    // 叫醒消费者
        this_thread::sleep_for(90ms);   // 模拟生产者生产商品时间
    }
    pcout{} << "EXIT: Producer " << id << endl;
}

static void consumer(size_t id){    // 消费者函数，接受消费者id作为参数
    while (!production_stooped || !q.empty()){  // 当消费者停止生产且队列上没有商品时退出循环
        unique_lock<mutex> lock(q_mutex);   // 上锁
        if(go_consume.wait_for(lock, 1s, []{ return !q.empty();})){ // 当解锁之后或者1s都没有解锁之后，我们不会等待，开始从队列消费
            pcout{} << " item " << setw(3) << q.front() << " --> Consumer " << id << endl;  // 获取商品
            q.pop();
            go_produce.notify_all();    // 提醒生产者生产
            this_thread::sleep_for(130ms);  // 模拟消费时间
        }
    }
    pcout{} << "EXIT: Producer " << id << endl;
}

int main(){
    vector<thread> workers; // 生产进程
    vector<thread> consumers;   // 消费进程
    for (size_t i = 0; i < 3; ++i) {    // 创建3个生产者
        workers.emplace_back(producer, i, 15, 5);
    }
    for (size_t i = 0; i < 5; ++i) {    // 创建5个消费者
        consumers.emplace_back(consumer, i);
    }

    for (auto &t : workers) { t.join(); }   // 回收线程，生产完马上回收
    production_stooped = true;  // 设置标志位，停止生产
    for (auto &t : consumers) { t.join(); }
}