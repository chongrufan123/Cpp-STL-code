// 07-search.cpp
// 在字符串中定位模式并选择最佳实现--std::search

#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <functional>

using namespace std;

template <typename Itr>
static void print(Itr it, size_t chars){    // 辅助函数，用于打印查找算法所范围的位置，输出子字符串
    copy_n(it, chars, ostream_iterator<char>{cout});    
    cout << endl;
}

int main(){
    const string long_string{
        "Lorem ipsum dolor sit amet, consetetur"
        " sadipscing elitr, sed diam nonumy eirmod"
    };
    const string needle {"elitr"};
    {
        auto match (search(begin(long_string), end(long_string), begin(needle), end(needle)));  // 旧search，返回迭代器指向所查找到的子字符串，如果没有找到，返回end迭代器
        print(match, 10);
    }
    {
        auto match (search(begin(long_string), end(long_string), default_searcher(begin(needle), end(needle))));// 新search，default_searcher能接受一组子字符串的begin和end，然后在一个更大的子字符串中查找，这样比较方便搜索
        print(match, 5);
    }
    {
        auto match (search(begin(long_string), end(long_string), boyer_moore_searcher(begin(needle), end(needle))));
        // boyer_moore_searcher使用boyer-moore查找算法进行快速的查找
        print(match, 5);
    }
    {
        // Boyer-Moore-Horspool查找算法
        auto match (search(begin(long_string),end(long_string),boyer_moore_horspool_searcher(begin(needle),end(needle))));
        print(match, 5);
    }
}