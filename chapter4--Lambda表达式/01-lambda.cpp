// 01-lambda.cpp
// 使用Lambda表达式定义函数

#include <iostream>
#include <string>

int main(){
    using namespace std;
    auto just_one ([](){ return 1;});   // 定义两个没有参数的Lambda函数
    auto just_two ([] {return 2;} );
    cout << just_one() << ", " << just_two() << endl;   // 输出函数的内容

    auto plus ([] (auto l, auto r){return l + r;}); // 定义一个有两个参数的加法Lambda函数
    cout << plus(1, 2) << endl;
    cout << plus(string{"a"}, "b") << endl;

    cout << [](auto l, auto r){return l + r;}(1, 2) << endl;    // Lambda也可以不适用变量，只是用到的时候定义
    auto counter([count = 0] () mutable {return ++ count;});    // 定义一个闭包，为了能让函数对获取的值进行修改，使用mutable关键字对函数进行修饰，使用mutable关键字可以使得其修饰的变量可以被修改，即使这个变量是被const修饰的
    for(size_t i {0}; i < 5; ++i){      // 调用5次counter()
        cout << counter() << ", ";
    }
    cout << endl;
    int a {0};
    auto incrementer ([&a] {++a;});     // 闭包，捕获已经存在的变量的引用
    for(size_t i {0}; i < 8; ++i){      // 调用8次incrementer()
        incrementer();
    }
    cout << a << endl;
    auto plus_ten ([=] (int x){ return plus(10, x); }); // 一个函数对象接受参数，并且传入另一个函数对象中进行保存

    std::cout << plus_ten(5) << std::endl;
}

// []中为捕获，()中为传入参数

