// 08-zip.cpp
// 构建 zip 迭代适配器

#include <iostream>
#include <vector>
#include <numeric>
// #include <valarray>

class zip_iterator{ // 创建zip迭代器
    using it_type = std::vector<double>::iterator;      // zip迭代器容器中保存两个迭代器
    it_type it1;
    it_type it2;
public:
    zip_iterator(it_type iterator1, it_type iterator2) : it1{iterator1}, it2{iterator2} {}  // 将传入的两个容器的迭代器进行保存，以便进行迭代
    zip_iterator & operator++() {   // 增加两个成员迭代器
        ++it1;
        ++it2;
        return *this;
    }
    bool operator!=(const zip_iterator& o) const {  // 如果两个迭代器来自不同的容器，那么他们一定会不相等
        return it1 != o.it1 && it2 != o.it2;
    }
    bool operator==(const zip_iterator & o) const{
        return !operator!=(o);
    }
    std::pair<double, double> operator*() const {   // 访问两个迭代器解引用的值
        return {*it1, *it2};
    }
};

namespace std{  // 让迭代器兼容STL算法
    template <>
    struct iterator_traits<zip_iterator> {
        using __iterator_category = std::forward_iterator_tag;
        using value_type = std::pair<double, double>;
        using difference_type = long int;
    };
}

class zipper{   // 定义范围类
    using vec_type = std::vector<double>;
    vec_type &vec1;
    vec_type &vec2;
public:
    zipper(vec_type &va, vec_type &vb) : vec1{va}, vec2{vb} {}
    zip_iterator begin() const {        // 指向开始位置
        return {std::begin(vec1), std::begin(vec2)};
    }
    zip_iterator end() const{       // 指向结束位置
        return {std::end(vec1), std::end(vec2)};
    }
};

int main(){
    using namespace std;
    vector<double> a {1.0, 2.0, 3.0};
    vector<double> b {4.0, 5.0, 6.0};
    zipper zipped {a, b};   // 直接使用两个vector对zipper类进行构造
    const auto add_product ([](double sum, const auto &p){  // 构造Lambda函数，将两个数相乘，然后进行累加
        return sum + p.first * p.second;
    });
    const auto dot_product(accumulate ( begin(zipped), end(zipped), 0.0, add_product)); // 调用accumulate将所有点积的值加起来
    cout << dot_product << endl;    // 打印结果

}