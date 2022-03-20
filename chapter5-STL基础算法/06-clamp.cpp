// 06-clamp.cpp
// 将 vector 中的值控制在特定数值范围内——std::clamp

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

static auto norm(int min, int max, int new_max){    // 忽略了最大值和最小值相等的情况，归一化的策略
    const double diff(max - min);
    return [=] (int val){
        return int((val - min) / diff * new_max);
    };
}

static auto clampval (int min, int max){  // 函数对象构造器clampval，返回一个函数对象捕获最小值和最大值，并调用clamp将值控制在一定范围
    return [=] (int val) -> int{
        return clamp(val, min, max);    // clamp函数直接对数据拦腰截断，会损失一些信息
    };
}

int main(){
    vector<int> v {0, 1000, 5, 250, 300, 800, 900, 321};    // 需要归一化的值
    const auto [min_it, max_it]( minmax_element(begin(v), end(v))); // minmax_element返回一个迭代器对，来表示最大的数和最小的数的位置
    // 实例化第二个vector，让其接受第一个vector中的值
    vector<int> v_norm;
    v_norm.reserve(v.size());
    transform(begin(v), end(v), back_inserter(v_norm), norm(*min_it, *max_it, 255));    // 将第一个vector的数据拷贝到第二个vector，在过程中使用归一化辅助函数，将范围限制在0~255
    copy(begin(v_norm), end(v_norm), ostream_iterator<int>{cout, ", "});    // 将结果打印出来
    cout << '\n';
    transform(begin(v), end(v), begin(v_norm),clampval(0, 255));    // 对vector使用clampval
    copy(begin(v_norm), end(v_norm), ostream_iterator<int>{cout, ", "});    // 将结果打印出来
    cout << '\n';
}