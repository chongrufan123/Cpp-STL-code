// 04-predicate.cpp
// 使用逻辑连接创建复杂谓词
// STL提供的函数类http://zh.cppreference.com/w/cpp/utility/functional

#include <iostream>
#include <functional>
#include <string>
#include <iterator>
#include <algorithm>

static bool begins_with_a (const std::string &s){    // 谓词函数，告诉我们字符串的第一个字母是否为a
    return s.find("a") == 0;
}
static bool ends_with_b (const std::string &s){     // 谓词函数，告诉我们字符串的最后一个字母是否为b
    return s.rfind("b") == s.length() - 1;
}

template<typename A, typename B, typename F>
auto combian(F binary_func, A a, B b){  // 其中binary_func是一个二元函数
    return [=](auto param) {    // 返回一个Lambda表达式，这个表达式会返回两个谓词结合之后的结果
        return binary_func(a(param), b(param));
    };
}

using namespace std;
int main(){
    auto a_xxx_b (combian( logical_and<>{}, begins_with_a, ends_with_b));   // logical_and是一个二元函数，表示and
    copy_if(istream_iterator<string>{cin}, {}, ostream_iterator<string>{cout, ", "}, a_xxx_b);  // 复制谓词为真的序列元素
    cout << endl;
}