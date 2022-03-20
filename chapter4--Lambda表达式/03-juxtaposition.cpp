// 03-juxtaposition.cpp
// 并置函数
// 用到了C++17的内容，编译时需要加"--std=c++17"

#include <iostream>
#include <functional>

template <typename T, typename ...Ts>
auto concat(T t, Ts ...ts){
    if constexpr (sizeof...(ts) > 0){   // 检查在递归步骤中是否串联了多个函数
        return [=](auto ...parameters) {    // 里面是一个没有定义变量的Lambda函数
            return t(concat(ts...)(parameters...));
        };
    }
    else{
        return t;   // 到递归的末尾，返回函数t
    }
}

int main(){
    auto twice ([] (int i) {return i * 2;});    // 定义两个对象
    auto thrice ([] (int i) {return i * 3;});
    auto combined (
        concat(twice, thrice, std::plus<int>{}) // 将两个乘法器函数和一个STL函数放在一起，得到twice(thrice(plus(a, b)))
    );
    std::cout << combined(2, 3) << std::endl;
}