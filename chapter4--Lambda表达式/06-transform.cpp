// 06-transform.cpp
// 使用std::accumulate和Lambda函数实现transform_if

#include <iostream>
#include <iterator>
#include <numeric>

template <typename T>
auto map(T fn){ // 进行过滤，不进行变换
    return [=] (auto reduce_fn){
        return [=] (auto accum, auto input){
            return reduce_fn(accum, fn(input)); // Lambda里面嵌套了一个Lambda
        };
    };
}

template <typename T>
auto filter(T predicate){   // predicate是谓词函数
    return [=] (auto reduce_fn){
        return [=] (auto accum, auto input){    // 也是Lambda里面嵌套一个Lambda，后一个Lambda里面还有一个判断
            if(predicate(input)){   // 首先对input进行操作
                return reduce_fn(accum, input);
            }
            else{
                return accum;
            }
        };
    };
}

int main(){
    std::istream_iterator<int> it{std::cin};
    std::istream_iterator<int> end_it;      // 实例化输入迭代器，从标准输入中获取整数值
    auto even ([](int i) {return i % 2 == 0;}); // 调用谓词函数even，输入偶数时返回true
    auto twice ([] (int i) {return i * 2;});    // 调用变换函数twice，会对输入整数乘2处理
    auto copy_and_advance ([](auto it, auto input){ // 接受用户输入的整数值，使用输出迭代器输出
        *it = input;
        return ++it;
    });
    std::accumulate(it, end_it,         //accumulate会将所对应范围的数值进行累加默认是通过+进行累加，也可以自己提供累加函数 
    // 对标准输入进行迭代，通过输出迭代器将对应值发射到终端
        std::ostream_iterator<int>{std::cout, ","}, // 输出迭代器作为init，accumulate就不会做累加
        filter(even)(   // 自己提供的Lambda累加函数，filter捕获even谓词，返回一个函数，为一个包装了另一个二元函数的二元函数
            map(twice)(
                copy_and_advance    
            )
        ));
        // 将copy_and_advance包装到even过滤器中，再包装入twice引射器中
        std::cout << "\n";
}