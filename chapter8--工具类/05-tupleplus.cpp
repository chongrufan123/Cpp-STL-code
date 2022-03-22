// 05-tupleplus.cpp
// 使用元组快速构成数据结构

#include <iostream>
#include <tuple>
#include <list>
#include <utility>
#include <string>
#include <iterator>
#include <numeric>
#include <algorithm>

using namespace std;

template <typename T, typename ... Ts>
void print_args(ostream &os, const T &v, const Ts & ...vs){
    os << v;
    (void)initializer_list<int>{((os << ", " << vs), 0)...};    // 使用逗号将initializer_list中的元素隔开
}

template <typename ... Ts>  // 通过模板函数匹配任意元组类型
ostream& operator<<(ostream &os, const tuple<Ts...> &t){    // 对输出操作符进行重载
    auto print_to_os ([&os](const auto &...xs){ // 接受任意多个参数
        print_args(os, xs...);
    });
    os << "(";
    apply(print_to_os, t);  // 解包
    return os << ")";
}

template <typename T>
tuple<double, double, double, double> sum_min_max_avg(const T &range){  // 可以接受迭代范围的函数，可以对对应范围进行迭代，然后返回所有值的加和
    auto min_max(minmax_element(begin(range), end(range)));
    auto sum(accumulate(begin(range), end(range), 0.0));
    return {sum, *min_max.first, *min_max.second, sum / range.size()};
}

template <typename T1, typename T2>
static auto zip(const T1 &a, const T2 &b){  // 对两个元组进行zip操作
    auto z ([](auto ...xs){ // z接受任意数量的参数，返回另一个函数对象
        return [xs...](auto ...ys){ // 获取所有参数打包成xs
            return tuple_cat(make_tuple(xs, ys) ...);   // make_tuple将参数分组，tuple_cat接受任意数量的元组，解包之后放到一个元组中
        };
    });
    return apply(apply(z, a), b);   // 将所有输入元组的成员解包出来，也就是将a和b进行解包后放入z中，最后返回去
}

int main(){
    auto student_desc (make_tuple("ID", "Name", "GPA"));
    auto student (make_tuple(123456, "John Doe", 3.7));
    cout << student_desc << endl << student << endl;    // 使用重载的操作符进行打印
    cout << tuple_cat(student_desc, student) << endl;   // 将两个元组进行连接，然后打印
    auto zipped (zip(student_desc, student));   // 使用自己创建的zip进行连接
    cout << zipped << endl;

    auto numbers = {0.0, 1.0, 2.0, 3.0, 4.0};
    cout << zip(make_tuple("Sum", "Minimum", "Maximum", "Average"), sum_min_max_avg(numbers)) << endl;
}