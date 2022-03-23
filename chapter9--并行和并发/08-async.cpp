// 08-async.cpp
// 将执行的程序推到后台--std::async

#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include <future>

using namespace std;

static map<char, size_t> histogram(const string &s){    // 接收一个字符串，创建一个对于字符串中的字符进行统计的直方图
    map<char, size_t> m;
    for(char c : s) { m[c] += 1;}
    return m;
}

static string sorted(string s){ // 接收一个字符串，返回一个排序后的副本
    sort(begin(s), end(s));
    return s;
}

static bool is_vowel(char c){    // 计数函数的辅助函数
    char vowels[] {"aeiou"};
    return end(vowels) != find(begin(vowels), end(vowels), c);
}

static size_t vowel(const string &s){   // 对传入的元音字母进行计数
    return count_if(begin(s), end(s), is_vowel);
}

int main(){
    cin.unsetf(ios::skipws);    // 禁用ios::skipws，不让输入字符串分段
    string input {istream_iterator<char>{cin}, {}};
    input.pop_back();

    // 异步方式获得三个函数的返回值，async会启动一个新线程，让线程并发的完成这几个函数
    auto hist (async(launch::async, histogram, input));
    auto sorted_str (async(launch::async, sorted, input));
    auto vowel_count (async(launch::async, vowel, input));

    for(const auto &[c, count] : hist.get()){
        cout << c << ": " << count << endl;
    }

    cout << "Sorted string: " << quoted(sorted_str.get()) << endl;
    cout << "Total vowels: " << vowel_count.get() << endl;
}