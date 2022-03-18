// 12-multimap.cpp
// 实现写作风格助手用来查找文本中很长的句子--std::multimap

#include <iostream>
#include <iterator>
#include <map>
#include <algorithm>

using namespace std;

// 过滤掉空格，回车和制表符
string filter_ws(const string &s){
    const char *ws{" \r\n\t"};
    const auto a(s.find_first_not_of(ws));
    const auto b(s.find_last_not_of(ws));
    if(a == string::npos){
        return {};
    }
    return s.substr(a, b);
}

multimap<size_t, string> get_sentence_stats(const string &content){ // 声明一个multimap结构以及一些迭代器
    multimap<size_t, string> ret;
    const auto end_it (end(content));
    auto it1 (begin(content));      // it1总是指向句子的开头
    auto it2 (find(it1, end_it, '.'));      // it2指向句号
    while(it1 != end_it && distance(it1, it2) > 0){ // 当迭代器中还有字符时进入循环
        string s {filter_ws({it1, it2})};
        if(s.length() > 0){
            const auto words (count(begin(s), end(s), ' ') + 1);
            ret.emplace(make_pair(words, move(s)));
        }
        it1 = next(it2, 1); // 下一次循环迭代，it1指向it2的后一个字符
        it2 = find(it1, end_it, '.');   // it2指向下一个句号
    }
    return ret;

}

int main(){
    cin.unsetf(ios::skipws);
    string content {istream_iterator<char>{cin}, {}};
    for(const auto & [word_count, sentence] : get_sentence_stats(content)){
        cout << word_count << " words: " << sentence << endl;
    }
}