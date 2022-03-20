// 05-find.cpp
// 在有序和无序的vector中查找元素

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <string>

using namespace std;

struct city{
    string name;
    unsigned population;
};

bool operator==(const city &a, const city &b){  // 重载==运算符
    return a.name == b.name && a.population == b.population;
}

ostream& operator<<(ostream &os, const city &city){  // 重载<<运算符
    return os << "{" << city.name << ", " << city.population << "}";
}

template <typename C>
static auto opt_print (const C &container){ // 对数据结构的end迭代器进行包装，是end返回end，否则返回相应的值
    return [end_it (end(container))] (const auto &item){
        if(item != end_it){
            cout << *item << endl;
        }
        else{
            cout <<"<end>\n";
        }
    };
}

int main(){
    const vector<city> c{
        {"Aachen", 246000},
        {"Berlin", 3502000},
        {"Braunschweig", 251000},
        {"Cologne", 1060000}
    };
    auto print_city (opt_print(c)); // 构造城市打印函数，返回vector容器的end
    {
        auto found_cologne (find(begin(c), end(c), city{"Cologne", 1060000}));  // 找到科隆，返回一个迭代器
        print_city(found_cologne);
    }
    {
        auto found_cologne (find_if(begin(c), end(c), [](const auto &item){ return item.name == "Cologne";}));  // find_if可以接受一个谓词函数作为函数对象
        print_city(found_cologne);
    }
    {
        auto population_more_than ([](unsigned i){ return [=] (const city &item){ return item.population > i;};});  // 构造谓词函数
        auto found_large(find_if(begin(c), end(c), population_more_than(2000000))); // 找到人口多余2百万的城市
        print_city(found_large);
    }
    const vector<int> v {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto print_int (opt_print(v));
    bool contains_7 {binary_search(begin(v), end(v), 7)};   // 二分查找binary_search返回一个布尔值，告诉函数是否找到了对应的元素，序列必定有序，否则出错
    cout << contains_7 << endl;
    auto [lower_it, upper_it]( equal_range(begin(v), end(v), 7));   // equal_range会返回一组迭代器，第一个指向第一个不小于给定值的元素，第二个指向第一个大于给定值的元素
    print_int(lower_it);
    print_int(upper_it);

    print_int(lower_bound(begin(v), end(v), 7));    // lower_bound只会返回第一个迭代器
    print_int(upper_bound(begin(v), end(v), 7));    // upper_bound只会返回第二个迭代器
}