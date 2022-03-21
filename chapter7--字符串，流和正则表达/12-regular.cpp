// 12-regular.cpp
// 使用正则表达式库标记输入
// 正则表达式在C++11标准中正式加入C++STL

#include <iostream>
#include <iterator>
#include <regex>
#include <algorithm>
#include <iomanip>

using namespace std;

template <typename InputIt>
void print(InputIt it, InputIt end_it){ // 打印辅助函数
    while (it != end_it){
        const string link {*it++};
        if( it == end_it) {break;}
        const string desc{*it++};
        cout << left << setw(28) << desc << " : " << link << endl;
    }
}

int main(){
    cin >> noskipws;
    const std::string in {
        istream_iterator<char>{cin}, {}
    };
    const regex link_re{ "<a href=\"([^\"]*)\"[^<]*>([^<]*)</a>"};  // 获取url地址的描述
    sregex_token_iterator it {  // sregex_token_iterator可以对istream_iterator直接操作，第三个参数表示想要表达式组1和组2的结果
        begin(in), end(in), link_re, {1, 2}
    };
    print(it, {});

}