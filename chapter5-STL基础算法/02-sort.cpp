// 02-sort.cpp
// 容器元素排序

/*
| 算法函数     | 作用                                                                                |
| ------------ | --------------------------------------------------------------------------------|
| sort         | 接受一定范围的元素，并对元素进行排序                                                   |
| is_sort      | 接受一定范围的元素，判断是否经过排序                                                   |
| shuffle      | 接受一定范围元素，打乱之                                                             |
| partial_sort | 接受一定范围的元素和另一个迭代器，前两个参数决定排序的范围，后两个参数决定不排序的范围。        |
| partial      | 能够接受谓词函数。所有元素都会在谓词函数返回true时，被移动到范围的前端。剩下的将放在范围的后方。 |

对于没有比较符的对象，需要自己提供一个比较符
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <random>

using namespace std;

static void print(const vector<int> &v){    // 打印vector中的整数
    copy(begin(v), end(v), ostream_iterator<int>{cout, ", "});
    cout << endl;
}

int main(){
    vector<int> v {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    random_device rd;   // 特定平台的非确定随机数生成器的标准接口
    mt19937 g {rd()};   // 随机数生成器，大随机数
    cout << is_sorted(begin(v), end(v)) << endl;    // 判断是否已经排序好了
    shuffle(begin(v), end(v), g);   // 打乱vector中的内容
    print(v);
    sort(begin(v), end(v)); // 对打乱的vector进行排序

    shuffle(begin(v), end(v), g);   // 打乱vector中的内容
    print(v);
    partition(begin(v), end(v), [](int i) { return i < 5; });   // 使用partition将数值小于5的排到前面
    print(v);
    
    shuffle(begin(v), end(v), g);   // 打乱vector中的内容
    print(v);
    auto middle (next(begin(v), int(v.size()) / 2));    //指向中间的数据的迭代器
    partial_sort(begin(v), middle, end(v));     // 只对前半部分进行排序
    print(v);

    struct mystruct{
        int a;
        int b;
    };

    vector<mystruct> mv{ {5, 100}, {1, 50}, {-123, 1000}, {3, 70}, {-10, 20}};  // 定义一个不是标准的容器的结构体

    sort(begin(mv), end(mv), [] (const mystruct &lhs, const mystruct &rhs){ return lhs.b < rhs.b;});    // 可以将比较函数作为第三个参数传入
    for (const auto &[a, b] : mv) { // 打印vector
    cout << "{" << a << ", " << b << "} ";
    }
    cout << '\n';

}