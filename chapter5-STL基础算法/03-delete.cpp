// 03-delete.cpp
// 从容器中删除指定元素

/*
| 算法函数     | 作用                                                                                                   |
| ------------ | ------------------------------------------------------------------------------------------------------ |
| remove       | 接受一个容器范围和一个具体的值作为参数，并且移除对应的值。返回一个新的end迭代器，用于修改容器的范围。  |
| replace      | 接受一个容器范围和两个值作为参数，将使用第二个数值替换所有与第一个数值相同的值。                       |
| remove_copy  | 接受一个容器范围，一个输出迭代器和一个值作为参数。并且将所有不满足条件的元素拷贝到输出迭代器的容器中。 |
| replace_copy | 与 std::replace 功能类似，但与 std::remove_copy 更类似些。源容器的范围并没有变化。                     |
| copy_if      | 与 std::copy 功能相同，可以多接受一个谓词函数作为是否进行拷贝的依据                                    |
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

void print(const vector<int> &v){   // 辅助打印函数
    copy(begin(v), end(v), ostream_iterator<int>{cout, ", "});
    cout << endl;
}

int main(){
    vector<int> v{1, 2, 3, 4, 5, 6, 7};
    print(v);
    {
        const auto new_end(remove(begin(v), end(v), 2));    // 将vector中的2移动到其他位置，返回新的末尾处的迭代器
        print(v);
        v.erase(new_end, end(v));   // 抹去最后的元素
        print(v);
    }
    {
        auto odd_number ([](int i) {return i % 2 != 0;});   // 定义一个Lambda表达式
        const auto new_end (remove_if(begin(v), end(v), odd_number));   // 当Lambda表达式为真的时候移除
        v.erase(new_end, end(v));
    }
    print(v);

    replace(begin(v), end(v), 4, 123);  // 将所有的4替换为123
    print(v);

    vector<int> v1{1, 2, 3, 4, 5, 6, 7}; // 重新初始化v和两个空的容器
    vector<int> v2;
    vector<int> v3;

    auto odd_number ([](int i) {return i % 2 != 0;});   // 判断奇偶的谓词函数
    auto even_number([] (int i) {return i % 2 == 0;});
    remove_copy_if(begin(v1), end(v1), back_inserter(v2), odd_number);  // 不满足谓词条件时进行拷贝
    copy_if(begin(v1), end(v1), back_inserter(v3), even_number);    // 满足谓词条件时进行拷贝

    print(v2);
    print(v3);
}