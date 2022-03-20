// 04-sort_of_vector.cpp
// 保持对std::vector实例的排序

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <cassert>

using namespace std;

void insert_sorted(vector<string> &v, const string &word);
void show(std::vector<string> &v);

int main(){
    vector<string> v {"some", "random", "words", "without", "order", "aaa", "yyy"}; // 创建一个随机的单词填充vector
    show(v);
    assert(false == is_sorted(begin(v), end(v)));   // 确定没有经过排序
    sort(begin(v), end(v));
    assert(true == is_sorted(begin(v), end(v)));    // 确定经过了排序
    show(v);
    insert_sorted(v, "foobar");
    insert_sorted(v, "zzz");
    show(v);


}
void insert_sorted(vector<string> &v, const string &word){
    const auto insert_pos (lower_bound(begin(v), end(v), word));    // lower_bound对新单词进行定位，头两个参数是容器的开头和结尾，最后一个参数是要插入的单词，函数会找到大于等于第三个参数的收个位置，然后返回该位置的迭代器
    v.insert(insert_pos, word);
}

/*
*   展示当前vector中的数值
*/
void show(std::vector<string> &v){
    for(auto &i : v){
        cout << i << ", ";
    }
    cout << "\n";
}