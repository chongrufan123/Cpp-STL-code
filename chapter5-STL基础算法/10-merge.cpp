// 10-merge.cpp
// 实现字典合并工具

#include <iostream>
#include <algorithm>
#include <iterator>
#include <deque>
#include <tuple>
#include <string>
#include <fstream>

using namespace std;

using dict_entry = pair<string, string>;

namespace std {
    ostream& operator<<(ostream &os, const dict_entry p){
        return os << p.first << " " << p.second;
    }
    istream& operator>>(istream &is, dict_entry &p){
        return is >> p.first >> p.second;
    }
}

template <typename IS>
deque<dict_entry> from_instream(IS &&is){   // 接受任何流对象作为输入，构建字典
    deque<dict_entry> d {istream_iterator<dict_entry> {is}, {}};    // 构建一个std::deque来存放一对一的字符串对，并且读取标准输入中的所有字符，在返回字典前，对字典进行排序
    sort(begin(d), end(d));
    return d;
}

int main(){
    const auto dict1 (from_instream(ifstream{"dict.txt"})); // 使用两个不同的输入流，创建两个字典
    const auto dict2 (from_instream(cin));
    // 接受两对begin/end迭代器，进行合并，最后一个参数是输出的迭代器
    merge(begin(dict1), end(dict1), begin(dict2), end(dict2), ostream_iterator<dict_entry>{cout, "\n"});
}