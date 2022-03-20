// 01-range.cpp
// 建立可迭代区域

#include <iostream>

class num_iterator{ // 迭代器类
    int i;
public:
    explicit num_iterator(int position = 0) : i{position} {}    // 构造函数，使用position初始化i
    int operator*() const {return i;}   // 当迭代器解引用时得到一个整数
    num_iterator& operator++(){ // 重载迭代器++
        ++i;
        return *this;
    }
    bool operator!=(const num_iterator &other) const{   // 迭代器之间的比较，如果不相等，继续迭代
        return i != other.i;
    }
};

class num_range{    // 实现从头到尾的遍历
    int a;
    int b;
public:
    num_range(int from, int to) : a{from}, b{to} {}
    num_iterator begin() const { return num_iterator{a};}
    num_iterator end() const { return num_iterator{b};}
};

int main(){
    for (int i: num_range{100, 110}){
        std::cout << i << ", ";
    }
    std::cout << std::endl;
}