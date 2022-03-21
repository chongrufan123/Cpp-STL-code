// 02-space.cpp
// 消除字符串开始和结束处的空格

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

string trim_whitespace_surrounding(const string &s){    // 进行首尾空格的去除，返回首尾没有空格的新字符串
    const char whitespace[] {" \t\n"};
    const size_t first(s.find_first_not_of(whitespace));
    if (string::npos == first) {
        return {};
    }
    const size_t last(s.find_last_not_of(whitespace));
    return s.substr(first, (last - first + 1));
}

int main(){
    string s {" \t \n string surrounded by ugly"
                " whitespace \t\n"};
    cout << "{" << s << "}\n";
    cout << "{" << trim_whitespace_surrounding(s) << "}\n";
}