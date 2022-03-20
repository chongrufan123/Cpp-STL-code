// 07-descartes.cpp
// 编译时生成笛卡尔乘积
// 用到了C++17的内容，编译时需要加"--std=c++17"

#include <iostream>

using namespace std;
static void print(int x, int y){    // 对组对中的值进行打印
    cout << "(" << x << ", " << y << ")" << endl;
}

int main(){
    constexpr auto call_cart(   // constexpr可以在编译时求得函数和变量的值
        [=](auto f, auto x, auto ...rest) constexpr {   // 当x=1，rest=2, 3, 4时，会调用三次f(1, 2); f(1, 3); f(1, 4)
            (void)std::initializer_list<int>{
                (((x < rest) ? (void)f(x, rest) : (void)0)
                , 0)...
            };
        });
    constexpr auto cartesian ([=](auto ...xs)
    constexpr{
        return [=] (auto f) constexpr{
            (void)std::initializer_list<int>{
                ((void)call_cart(f, xs, xs...), 0)...
            };
        };
    });
    constexpr auto print_cart (cartesian(1, 2, 3));

    print_cart(print);
}