// 02-compatible.cpp
// 让自己的迭代器与STL的迭代器兼容

#include <iostream>
#include <algorithm>

class num_iterator{
    int i;
public:
    explicit num_iterator(int position = 0) : i{position} {}
    int operator*() const { return i; }
    num_iterator& operator++(){
        ++i;
        return *this;
    } 
    bool operator!=(const num_iterator &other) const{
        return i != other.i;
    }
    bool operator==(const num_iterator &other) const{
        return !(*this != other);
    }
};

class num_range{
    int a;
    int b;
public:
    num_range(int from, int to) : a{from}, b{to} {}
    num_iterator begin() const { return num_iterator{a};}
    num_iterator end() const { return num_iterator{b};}
};

using namespace std;

int main(){
    num_range r {100, 110};
    auto min_max(minmax_element(r.begin(), r.end()));   // minmax_element()会返回一个pair，其中具有两个迭代器，一个指向最小值，一个指向最大值
    cout << *min_max.first << " - " << *min_max.second << "\n";
}