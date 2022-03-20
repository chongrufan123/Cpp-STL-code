// 06-map_insert.cpp
// 了解 std::map::insert 新的插入提示语义

#include <iostream>
#include <map>
#include <string>

using namespace std;

void show(map<string, size_t> &m);
int main(){
    map<string, size_t> m{ {"b", 1}, {"c", 2}, {"d", 3} };  // 创建一个map
    show(m);
    auto insert_it(end(m)); // 创建一个hint迭代器，指向end之前
    show(m);
    for(const auto &s : {"w", "x", "y", "z"}){
        insert_it = m.insert(insert_it, {s, 1});    // 用insert函数插入键和对应的值，返回此次插入位置之前的迭代器
        // 会首先尝试插入hint迭代器对应的位置，然后检查是否有序，如果无序，会不管hint，自动通过搜索二叉树实现插入到适当位置
        // 所以当输入一个错误的hint值时，会使得算法时间变慢
    }
    show(m);
    m.insert(end(m), {"a", 1}); // 使用insert插入数据时，会自动排序，此时插入的数据依然在整个数据的最左侧
    show(m);
    return 0;
}

void show(map<string, size_t> &m){
    for(const auto & [key, value] : m){
        cout << "\"" << key << "\": " << value << ", ";
    }
    cout << "\n";
}