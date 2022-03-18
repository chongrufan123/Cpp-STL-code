// 06-pointer.cpp
// 使用哨兵终止迭代
// 用到了C++17的内容，编译时需要加"--std=c++17"

#include <iostream>

class cstring_iterator_sentinel {}; // 迭代器哨兵
class cstring_iterator{
    const char *s {nullptr};
public:
    explicit cstring_iterator(const char *str) : s{str} {}
    char operator*() const { return *s;}    // 解引用
    cstring_iterator& operator++() {
        ++s;
        return *this;
    }
    bool operator!=(const cstring_iterator_sentinel) const {
        return s != nullptr && *s != '\0';  // 迭代器和哨兵比较
    }
};

class cstring_range{    // 使用基于范围的for循环
    const char *s {nullptr};
public:
    cstring_range(const char *str): s{str} {}
    cstring_iterator begin() const {    // 返回迭代器，指向字符串的起始位置
        return cstring_iterator{s};
    }
    cstring_iterator_sentinel end() const{  // 返回一个哨兵类型
        return {};      
    }
};

int main(int argc, char *argv[]){
    if(argc < 2){   // 判断是否输入参数
        std::cout << "Please provide one parameter.\n";
        return 1;
    }
    for(char c : cstring_range(argv[1])){
        std::cout << c;
    }
    std::cout << '\n';
}