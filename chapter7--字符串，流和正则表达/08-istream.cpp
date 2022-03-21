// 08-istream.cpp
// 迭代器填充容器--std::istream

#include <iostream>
#include <iomanip>
#include <map>
#include <iterator>
#include <algorithm>
#include <numeric>

using namespace std;

struct meme
{
    string description;
    size_t year;
};

istream& operator>>(istream &is, meme &m){  // 对结构体的>>操作符
    return is >> quoted(m.description) >> m.year;   // 使用quoted()，引号会认为是限定符，直接丢弃
}

istream& operator>>(istream &is, pair<string, meme> &p){    // 对map的>>进行重载
    return is >> quoted(p.first) >> p.second;
}

int main(){
    map<string, meme> m;
    copy(istream_iterator<pair<string, meme>>{cin}, {}, inserter(m, end(m)));   // 将输入流放到map中

    auto max_func([](size_t old_max, const auto &b){    // 在map中找到名称最长的梗，与当前最大的变量进行比较
        return max(old_max, b.first.length());
    });
    size_t width{accumulate(begin(m), end(m), 0u, max_func)};   // 对最长字符串的长度进行累加，返回当前梗中名称最长的梗

    for(const auto &[meme_name, meme_desc] : m){
        const auto &[desc, year] = meme_desc;
        cout << left << setw(width) << meme_name << " : " << desc << ", " << year << endl;
    }
}
