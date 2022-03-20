// 11-map_count.cpp
// 实现词频计数器--std::map

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

string filter_punctuation(const string &s){  // 辅助函数，对输入的符号进行处理
    const char *forbidden {".,:;"};
    const auto idx_start (s.find_first_not_of(forbidden));
    const auto idx_end (s.find_last_not_of(forbidden));
    return s.substr(idx_start, idx_end - idx_start + 1);
}

int main(){
    map<string, size_t> words;
    int max_word_len(0);
    string s;
    while( cin >> s ){
        auto filtered (filter_punctuation(s));
        max_word_len = max<int>(max_word_len, filtered.length());
        ++ words[filtered];
    }
    vector<pair<string, size_t>>word_counts;    // 将map中的数据迁移到这里来，方便对词频按照频率排序
    word_counts.reserve(words.size());
    move(begin(words), end(words), back_inserter(word_counts)); // 将词频对应关系填充整个vector，让单词不会重复，不过会让元素从map中删除，可以减少不必要的拷贝

    sort(begin(word_counts), end(word_counts), [](const auto &a, const auto &b) {
        return a.second > b.second;
    }); // 按照第二个词进行比较，即.second
    cout << "# " << setw(max_word_len) << "<WORD>" << " #<COUNT>\n";
    for(const auto & [word, count] : word_counts){
        cout << setw(max_word_len + 2) << word << " #" << count << endl;
    }
}