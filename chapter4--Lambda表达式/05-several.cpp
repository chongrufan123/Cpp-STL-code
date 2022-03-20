// 05-several.cpp
// 使用同一输入调用多个函数

#include <iostream>

// 接受任意数量的参数，返回一个Lambda表达式，表达式通过这个参数调用所有已经提供的函数
template <typename ... Ts>
static auto multicall (Ts ...functions){    
    return [=](auto x){
        (void)std::initializer_list<int>{   // initializer_list当中包含一系列可以调用的函数对象
            ((void)functions(x), 0)...
        };
    };
}

template <typename F, typename ... Ts>
static auto for_each ( F f, Ts ...xs) {      // 接受一个函数f和一个参数包xs，参数包中每个参数都会传到f中运行，从而产生一系列的调用
    (void)std::initializer_list<int>{
        ((void) f(xs), 0)...
    };
}

static auto brace_print (char a, char b) {  // 返回一个可以接受一个参数的函数对象，对象中打印字符
    return [=] (auto x) {
        std::cout << a << x << b << ", ";
    };
}

int main(){
    auto f (brace_print('(', ')'));
    auto g (brace_print('[', ']'));
    auto h (brace_print('{', '}'));
    auto n1 ([](auto) {std::cout << "\n"; });
    auto call_fgh (multicall(f, g, h, n1));
    for_each(call_fgh, 1, 2, 3, 4, 5);

}