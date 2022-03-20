// 02-polymorphic.cpp
// 使用Lambda 为 std::function 添加多态性

#include <iostream>
#include <deque>
#include <list>
#include <vector>
#include <functional>

template <typename C>
static auto consumer (C &container) {   // 返回一个Lambda表达式，当向函数对象传入一个整型时，表达式会把传入的整型添加到捕获容器底部
    return [&] (auto value) {
        container.push_back(value);
    };
}

template <typename C>           // 打印传入容器的所有内容
static void print (const C &c){
    for(auto i : c){
        std::cout << i << ", ";
    }
    std::cout << "\n";
}

int main(){
    using namespace std;
    deque<int> d;
    list<int> l;
    vector<int> v;
    const std::vector<std::function<void(int)>> consumers{  // 在vector中储存生成自定义的函数对象，然后用一个vector存放三个函数对象
    // vector中的实例类型是function，所有对象都隐式转换成一个std::function对象，可以存储在vector中
    // std::function<void(int)>可以存储函数对象或传统函数，接受只有一个整型参数和返回为空的函数类型
    // std::function<void(int)>实质是多态，而不是Lambda表达式
        consumer(d), consumer(l), consumer(v)
    };
    for (size_t i {0}; i < 10; ++i){    // 将10个整型传入自定义函数对象
        for(auto &&consume : consumers){
            consume(i);
        }
    }
    print(d);   // 打印容器中的值
    print(l);
    print(v);

    return 0;
}