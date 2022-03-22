// 03-optional.cpp
// 安全的标识失败--std::optional

#include <iostream>
#include <optional>

using namespace std;

using oint = optional<int>; // 封装一个整型类型，可能包含一个值，放到opeional中标识会给一个附加状态，表示当前对象没有值

oint read_int(){    // 用来表示函数返回失败的情况
    int i;
    if(cin >> i) {return {i};}
    return {};
}

oint operator+(oint a, oint b){ // 如果有值的话，两个数相加
    if(!a || !b) {return {};}
    return {*a + *b};
}

oint operator+(oint a, int b){  // 重载，可以直接和一个普通整数相加
    if(!a) {return {};}
    return {*a + b};
}

int main(){
    cout << "Please enter 2 integers.\n>";

    auto a {read_int()};
    auto b {read_int()};

    auto sum (a + b + 10);
    if(sum){
        cout << *a << " + " << *b << " + 10 = " << *sum << '\n';
    }
    else{
        cout << "sorry, the input was something else than 2 numbers \n";
    }
    
}

