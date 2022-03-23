// 06-thread_cout.cpp
// 同步并行中使用std::cout

#include <iostream>
#include <thread>
#include <mutex>
#include <sstream>
#include <vector>

using namespace std;

struct pcout : public stringstream{ // pcout继承自stringstream，以便可以使用<<运算符
    static inline mutex cout_mutex;
    ~pcout(){   // 析构时对一个互斥量加锁，然后将stringstream缓冲区中的内容打印
        lock_guard<mutex> l {cout_mutex};   // 对全局进行锁定
        cout << rdbuf();    // 打印缓冲区的内容
        cout.flush();   // 立即打印内容
    }
};

static void print_cout(int id){ // 使用cout进行打印
    cout << "cout hello from " << id << endl;
}

static void print_pcout(int id){
    pcout{} << "pcout hello from " << id << endl;
}

int main(){
    vector<thread> v;
    for(size_t i {0}; i < 10; ++i){ // 并发启动10个线程
        v.emplace_back(print_cout, i);  // 使用cout打印
    }
    for(auto &t : v) {t.join();}    // 等待所有线程执行结束
    cout << "========================" << endl;
    v.clear();
    for(size_t i{0}; i < 10; ++i){  // 并发启动10个线程
        v.emplace_back(print_pcout, i); // 使用pcout打印
    }
    for(auto &t : v) { t.join();}   // 等待所有线程执行结束
}
