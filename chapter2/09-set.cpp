// 09-set.cpp
// 过滤用户的重复输入，并以字母序将重复信息打印出--std::set
#include <iostream>
#include <set>
#include <string>
#include <iterator>

using namespace std;

int main(){
    set<string> s;  // 实例化一个set
    // istream_iterator输入一个模板类型参数
    istream_iterator<string> it {cin};      // 得到begin迭代器
    istream_iterator<string> end;           // 得到end迭代器
    copy(it, end, inserter(s, s.end()));    // 填满set实例，其中第一二个参数是输入迭代器，第三个参数是输出迭代器
    for(const auto word : s){   // 输出set
        cout << word << ", ";
    }
    cout << endl;
}