// 10-stack.cpp
// 实现简单的逆波兰表示法计算器--std::stack

// 逆波兰表示法(RPN)，也就是算数时候用的表示法

#include <iostream>
#include <stack>
#include <iterator>
#include <map>
#include <sstream>
#include <cassert>
#include <vector>
#include <stdexcept>
#include <cmath>

using namespace std;

template <typename IT>
double evaluate_rpn(IT it, IT end){ // RPN解析器，两个迭代器分别指定数学表达式的开始和结尾
    stack<double> val_stack;

    auto pop_stack([&](){       // 实现一个辅助函数，修改栈中的内容，弹出最顶部的元素，并返回这个元素
        auto r (val_stack.top());   // 获得栈顶元素副本
        val_stack.pop();    // 从栈中移除顶部元素
        return r;   // 返回顶部元素副本
    });
    map<string, double (*) (double, double) > ops { // 定义所支持的数学操作符，使用map保存相关数学操作符的作用，每个操作符用Lambda函数实现
        {"+", [](double a, double b) {return a + b;}},
        {"-", [](double a, double b) {return a - b;}},
        {"*", [](double a, double b) {return a * b;}},
        {"/", [](double a, double b) {return a / b;}},
        {"^", [](double a, double b) {return pow(a, b);}},
        {"%", [](double a, double b) {return fmod(a, b);}},
    };
    for(; it != end; ++it){ // 对输入进行遍历，假设输入是字符串，使用stringstream获取每个单词
        stringstream ss {*it};
        if(double val; ss >> val){  // 获得的每个操作数转换成double类型，转换类型之后推入栈中
            val_stack.push(val);    // 将元素推入栈中
        }
        else{   // 如果不是操作数，就是操作符，从栈中弹出两个操作数
            const auto r {pop_stack()}; 
            const auto l {pop_stack()};
            try {   // 解引用迭代器it获得操作数，查询map表，可以获得计算的l和r值
                const auto & op (ops.at(*it));
                const double result {op(l, r)};
                val_stack.push(result);
            }   
            catch (const out_of_range &){
                throw invalid_argument(*it);    // 抛出invalid_argument异常，并返回程序未知的操作符
            }
        }

    }
    return val_stack.top();
}

int main(){
    try{
        cout << evaluate_rpn(istream_iterator<string> {cin}, {})    // 将标准输入包装为一个std::istream_iterator迭代器对
        << "\n";
    }
    catch(const invalid_argument &e){
        cout << "Invalid operator: " << e.what() << endl;
    }
    return 0;
}