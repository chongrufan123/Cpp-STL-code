// 08-sample.cpp
// 对大vector进行采样
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <map>
#include <iomanip>

using namespace std;

int main(){
    const size_t data_points {100000};
    const size_t sample_points {100};
    const int mean {10};
    const size_t dev {3};

    // 设置随机数生成器
    random_device rd;
    mt19937 gen {rd()};
    normal_distribution<> d {mean, dev};

    vector<int> v;
    v.reserve(data_points);
    generate_n(back_insert_iterator(v), data_points, [&] {return d(gen);});  // 使用随机数对vector进行填充
    
    vector<int> samples;    // 放采样后的数据
    sample(begin(v), end(v), back_inserter(samples), sample_points, mt19937{random_device{}()});    // 进行采样，最后两个参数前者表示输入范围，后者确定采样点

    // copy(begin(samples), end(samples), ostream_iterator<int> {cout, ", "});
    map<int, size_t> hist;
    for(int i: samples) { ++hist[i]; }

    for(const auto &[value, count] : hist){ // 打印出直方图
        cout << setw(2) << value << " " << string(count, '*') << endl;
    }
}