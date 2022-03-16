// 01-vector.cpp
// 擦除 / 移除 std::vector 元素

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void show(vector<int> &v);

int main(){
    vector<int> v{1, 2, 3, 2, 5, 2, 6, 2, 4, 8};    // 构造一个vector
    show(v);
    const auto new_end(remove(begin(v), end(v), 2));    // 移除一个容器中的某个元素，返回结果容器的结尾
    show(v);
    v.erase(new_end, end(v));   // 移除元素的范围
    show(v);

    const auto odd([](int i){return i % 2 != 0;});  // 构造一个谓词函数
    v.erase(remove_if(begin(v), end(v), odd), end(v));  // remove_if即移除谓语函数
    show(v);
    cout << "origin capacity is " << v.capacity() << endl;
    v.shrink_to_fit();   // 重新分配一段内存
    show(v);
    cout << "now the capacity is " << v.capacity() << endl;

    return 0;
}

void show(vector<int> &v){
    for(auto i : v){
        cout << i << ", ";
    }
    cout << "\n";
}