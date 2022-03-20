// 07-check.cpp
// 使用检查过的迭代器自动化检查迭代器代码
// 通过在编译时加-D_GLIBCXX_DEBUG编译选项来对STL的健壮性检查，可以方便找到bug

#include <iostream>
#include <vector>

int main(){
    std::vector<int> v{1, 2, 3};
    v.shrink_to_fit();      // 缩小vector的容积，可以加快迭代速度
    const auto it (std::begin(v));
    std::cout << *it << std::endl;

    v.push_back(123);   // 增加一个新数，由于vector只有3的长度，所以需要重新分配一个更大的内存块，然后删除旧内存块
    std::cout << *it << std::endl;  // bad
}