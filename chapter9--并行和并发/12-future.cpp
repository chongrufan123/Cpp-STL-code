// 12-future.cpp
// 实现一个小型自动化并行库--std::future

#include <iostream>
#include <iomanip>
#include <thread>
#include <string>
#include <sstream>
#include <future>

using namespace std;
using namespace chrono_literals;

struct pcout : public stringstream {    // 输出同步辅助函数
    static inline mutex cout_mutex;
    ~pcout() {
        lock_guard<mutex> l {cout_mutex};
        cout << rdbuf();
        cout.flush();
    }
};

static string create(const char *s){    // 创建一个string对象，休眠3s，模拟计算复杂性
    pcout{} << "3s CREATE " << quoted(s) << endl;
    this_thread::sleep_for(3s);
    return {s};
}

static string concat(const string &a, const string &b){ // 两个字符串对象拼接，5s
    pcout{} << "5s CONCAT " << quoted(a) << " " << quoted(b) << "\n";
    this_thread::sleep_for(5s);
    return a + b;
}

static string twice(const string &s){   // 返回自己拼接，3s
    pcout{} << "3s TWICE " << quoted(s) < endl;
    this_thread::sleep_for(3s);
    return s + s;
}

template<typename F>
static auto asynchronize(F f){  // 接受函数f，返回一个捕获到的可调用对象
    return [f](auto ... xs){
        return [=] (){
            return async(launch::async, f, xs...);
        };
    };
}

template<typename F>
static auto fut_unwrap(F f){    // 将函数捕获到的一个可调用的对象返回
    return [f](auto ...xs){
        return f(sx.get()...);
    };
}

template <typename F>
static auto async_adapter(F f)
{
    return [f](auto ... xs) {
        return [=] () {
            return async(launch::async,
            fut_unwrap(f), xs()...);
        };
    };
}

int main(){
    auto pcreate (asynchronize(create));    // asynchronize()会返回一个future
    auto pconcat (async_adapter(concat));   // async_adapter()等待future的参数，返回一个future的结果，将同步世界转换为异步世界
    auto ptwice (async_adapter(twice));

    auto result (
        pconcat(
            ptwice(
            pconcat(
                pcreate("foo "),
                pcreate("bar "))),
            pconcat(
                pcreate("this "),
                pcreate("that "))));
    cout << "Setup done. Nothing executed yet.\n";
    cout << result().get() << '\n';
}