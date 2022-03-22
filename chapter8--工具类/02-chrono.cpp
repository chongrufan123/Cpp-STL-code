// 02-chrono.cpp
// 转换绝对时间和相对时间--std::chrono

#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std;

ostream &operator<<(ostream &os, const chrono::time_point<chrono::system_clock> &t){    // 打印绝对时间点，重载输出流
    const auto tt(chrono::system_clock::to_time_t(t));
    const auto loct (std::localtime(&tt));
    return os << put_time(loct, "%c");
}

using days = chrono::duration<chrono::hours::rep, ratio_multiply<chrono::hours::period, ratio<24>>>;    // 添加days类型

constexpr days operator ""_days(unsigned long long d){  // 定义days类型的字面操作符
    return days{d};
}

int main(){
    auto now(chrono::system_clock::now());  // now获得当前的时间点

    cout << "The current date and time is " << now << endl;

    chrono::hours chrono_12h {12};  // 为时间增加一个12h的偏移
    cout << "In 12 hours, it will be " << (now + chrono_12h) << endl;

    using namespace chrono_literals;
    cout << "12 hours and 15 minutes ago, it was " << (now - 12h - 15min) << endl << "1 week ago, it was " << (now - 7_days) << endl;

}