// 09-ostream.cpp
// 迭代器进行打印--std::ostream

#include <iostream>
#include <vector>
#include <iterator>
#include <unordered_map>
#include <algorithm>

using namespace std;
using namespace std::string_literals;

string word_num(int i){
    unordered_map<int, string> m{
        {1, "one"}, {2, "two"}, {3, "three"},
        {4, "four"}, {5, "five"},
    };
    const auto match (m.find(i));
    if(match == end(m)) { return "unknown"; }
    return match->second;
};

struct bork{
    int borks;
    bork(int i) : borks{i} {}   // 构造函数
    void print(ostream& os) const{fill_n(ostream_iterator<string>{os, " "}, borks, "bork!"s);   // 通过一个输出流引用重复打印bork!
    }
};

ostream& operator<<(ostream& os, const bork &b){    // 对>>进行重载
    b.print(os);
    return os;
}

int main(){
    const vector<int> v{1, 2, 3, 4, 5};
    ostream_iterator<int> oit {cout};   // 创建int模板类
    for(int i : v) { *oit = i;} // 使用循环对vector访问，并且对每个输出迭代器i解引用，标准用法
    cout << endl;
    ostream_iterator<int> oit_comma {cout, ", "};   // 重新创建并输出，这次加上逗号和空格
    for(int i : v) { *oit_comma = i;}
    cout << endl;

    copy(begin(v), end(v), oit);    // 也可以用这种方法将值赋给输出流迭代器
    cout << "\n";

    copy(begin(v), end(v), oit_comma);
    cout << endl;

    transform(begin(v), end(v), ostream_iterator<string>{cout, " "}, word_num); // word_num是一个转换函数，可以将整型转换为字符串，然后将转换后的字符串输出到输出流迭代器
    cout << endl;
    copy(begin(v), end(v), ostream_iterator<bork>{cout, "\n"}); // 对bork结构体进行打印
}