// 08-unordered_map.cpp
// std::unordered_map中使用自定义类型

// map中要求键的类型可以排序，但是unordered_map中不需要这样做，不需要对键的哈希值进行排序，只要为类型实现一个哈希函数和等同==操作符的实现
#include <iostream>
#include <unordered_map>

struct coord    // 自定义数据类型，不具备对应的哈希函数
{
    int x;
    int y;
};

bool operator==(const coord &l, const coord &r){    // 实现比较操作函数
    return l.x == r.x && l.y == r.y;
}

namespace std   // 创建一个特化的std::hash模板
{
    template<>
    struct hash<coord>{                 // 创建一个哈希模板
        using argument_type = coord;    // 使用using将特化类型进行别名
        using result_type = size_t;
        result_type operator() (const argument_type &c)     // 重载括号运算符
        const{
            return static_cast<result_type>(c.x) + static_cast<result_type>(c.y);
        }
    };
}

int main(){
    std::unordered_map<coord, int> m {
        { {0, 0}, 1 },
        { {0, 1}, 2 },
        { {2, 1}, 3 },
    };  // 创建一个基于哈希的map表
    for(const auto & [key, value] : m){
        std::cout << "{(" << key.x << ", " << key.y << "): " << value << "} ";
    }   // 输出map
    std::cout << "\n";
}
