// 13-number.cpp
// 简单打印不同格式的数字

#include <iostream>
#include <iomanip>

using namespace std;

class format_guard {    // 对输出流的格式进行清理，构造函数保存格式，析构函数去除格式
    decltype(cout.flags()) f {cout.flags()};
public:
    ~format_guard() { cout.flags(f);}
};

template <typename T>
struct scientific_type  // 模板类，拥有任意类型的成员变量
{
    T value;

    explicit scientific_type(T val) : value(val) {}
};

template <typename T>
ostream& operator<<(ostream &os, const scientific_type<T> &w){
    format_guard _;
    os << scientific << uppercase << showpos;
    return os << w.value;
}

int main(){
    {
        format_guard _; // 前两行安装设定格式打印
        cout << hex << scientific << showbase << uppercase;
        cout << "Numbers with special formatting: " << endl;
        cout << 0x123abc << endl;
        cout << 0.123456789 << endl;
    }
    cout << "Same numbers, but normal formatting again:" << endl;   // 下面两行默认格式打印
    cout << 0x123abc << endl;
    cout << 0.123456789 << endl;

    // scientific_type将三个浮点数打印在同一行，避免了冗长的格式设置代码
    cout << "Mixed formatting: " << 123.0 << " " << scientific_type{123.0} << " " << 123.456 << endl;
}