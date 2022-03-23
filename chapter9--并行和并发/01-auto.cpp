// 01-auto.cpp
// 标准算法的自动并行

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <execution>    // add at c++17

using namespace std;

static bool odd(int n){return n % 2;}   // 谓词函数，判断数值的奇偶性

int main(){
    vector<int> d (2000000000); // 定义一个很大的vector
    mt19937 gen;    // 对随机数生成器进行实例化
    uniform_int_distribution<int> dis(0, 100000);   // 选择一种分布生成
    auto rand_num ([=] () mutable {return dis(gen);});

    generate(execution::par, begin(d), end(d), rand_num);   // 使用随机数将vector塞满，填上execution::par可以让代码可以自动化并行，多线程的进行填充
    sort(execution::par, begin(d), end(d));
    reverse(execution::par, begin(d), end(d));
    auto odds (count_if(execution::par, begin(d), end(d), odd));    // 计算奇数的个数
    cout << (100.0 * odds / d.size()) << "% of the numbers are odd." << endl;   // 打印奇数的比例
}