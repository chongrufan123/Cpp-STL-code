// 05-map.cpp
// 向 std::map 实例中高效并有条件的插入元素
// 用到了C++17的内容，编译时需要加"--std=c++17"

#include <iostream>
#include <functional>
#include <list>
#include <map>
#include <utility>

using namespace std;

struct billionaire  // 一个结构体，代表对应的富人
{
    string name;
    double dollars;
    string country;
};
int main(){
    list<billionaire> billionaires {
        {"Bill Gates", 86.0, "USA"},
        {"Warren Buffet", 75.6, "USA"},
        {"Jeff Bezos", 72.8, "USA"},
        {"Amancio Ortega", 71.3, "Spain"},
        {"Mark Zuckerberg", 56.0, "USA"},
        {"Carlos Slim", 54.5, "Mexico"},
        // ...
        {"Bernard Arnault", 41.5, "France"},
        // ...
        {"Liliane Bettencourt", 39.5, "France"},
        // ...
        {"Wang Jianlin", 31.3, "China"},
        {"Li Ka-shing", 31.2, "Hong Kong"}
        // ...
    };  // 定义一个百万富翁的列表
    map<string, pair<const billionaire, size_t> > m; // 定义一个表，又国家名的字符串和一个组对构成，组对中是副本和计数器

    for (const auto &b : billionaires) {
        auto [iterator, success] = m.try_emplace(b.country, b, 1);  
        // try_emplace是C++17新添加的，第一个参数是插入的键，之后的参数是键对应的值
        // 插入成功返回一个pair(新节点在表中的位置的迭代器，bool变量)，插入不成功迭代器会指向冲突的位置。
        // 当这个键已经被插入过就会冲突，导致插入不成功

        if (!success) { // 冲突表示这个国家已经有人了
            iterator->second.second += 1;   // 迭代器的第二个是pair，pair的第二个是计数器
        }
    }

    for (const auto & [key, value] : m) {
        const auto &[b, count] = value;

        cout << b.country << " : " << count << " billionaires. Richest is "
             << b.name << " with " << b.dollars << " B$\n";
    }
}
