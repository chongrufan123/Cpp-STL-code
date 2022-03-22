// 06-any.cpp
// 将void*替换为更加安全的std::any

#include <iostream>
#include <iomanip>
#include <list>
#include <any>
#include <iterator>

using namespace std;

using int_list = list<int>; // 对list<int>进行别名处理

void print_anything(const std::any &a){ // 可以打印任何东西
    if(!a.has_value()) {    // 进行类型比较，空
        cout << "Nothing.\n";
    }
    else if(a.type() == typeid(string)){    // 当传入的是字符串时
        cout << "It's a string: " << quoted(any_cast<const string&>(a)) << endl;    // quoted()使用双引号作为修饰
    }
    else if(a.type() == typeid(int)){   // 当传入的是int时
        cout << "It's an integer: " << any_cast<int>(a) << endl;
    }
    else if(a.type() == typeid(int_list)){
        const auto &l (any_cast<const int_list&>(a));
        cout << "It's a list: ";
        copy(begin(l), end(l), ostream_iterator<int>{cout, ", "});
        cout << endl;
    }
    else{
        cout << "Can't handle this item." << endl;
    }
}

int main(){
    print_anything({});
    print_anything("abc"s);
    print_anything(123);
    print_anything(int_list{1, 2, 3});
    print_anything(any(in_place_type_t<int_list>{}, {1, 2, 3}));    // in_place_type_t<int_list>{}表示一个空的对象，第二个参数是一个初始化列表，用来初始化int_list容器
}