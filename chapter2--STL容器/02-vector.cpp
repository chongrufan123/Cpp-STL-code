// 02-vector.cpp
// 以O(1)的时间复杂度删除未排序std::vector中的元素
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void show(std::vector<int> &v);

template <typename T>
void quick_remove_at(std::vector<T> &v, typename std::vector<T>::iterator it){
    if(it != std::end(v)){
        *it = std::move(v.back());  // 将最后一个元素放到要删掉的元素的位置上
        v.pop_back();           // 去掉最后一个元素
    }
}

template <typename T>
void quick_remove_at(std::vector<T> &v, int it){
    if(it < v.size()){
        v.at(it) = std::move(v.back());      // 将最后一个元素放到要删掉的元素的位置上
        v.pop_back();       // 去掉最后一个元素
    }
}



int main(){
    std::vector<int> v{123, 456, 789, 100, 200};        // 定义一个vector实例
    show(v);
    quick_remove_at(v, 2);
    show(v);
    quick_remove_at(v, std::find(std::begin(v), std::end(v), 123)); // 找到123的迭代器
    show(v);
}

/*
*   展示当前vector中的数值
*/
void show(std::vector<int> &v){
    for(auto i : v){
        cout << i << ", ";
    }
    cout << "\n";
}