// 07-variant.cpp
// 存储不同的类型--std::variant
#include <iostream>
#include <variant>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

class cat {
    string name;
public:
    cat(string n) : name{n} {}
    void meow() const {
        cout << name << " says Meow!\n";
    }
};

class dog{
    string name;
public:
    dog(string n) : name{n} {}

    void woof() const {
        cout << name << " says Woof!\n";
    }
};

using animal = variant<dog, cat>;   // 定义一个animal类

template<typename T>
bool is_type(const animal &a){  // 动物判断谓词
    return holds_alternative<T>(a); // 检查a中是否有T
}

struct animal_voice // 双重函数对象
{
    void operator() (const dog &d) const {d.woof();}
    void operator() (const cat &c) const {c.meow();}
};

int main(){
    list<animal> l {cat{"Tuba"}, dog{"Balou"}, cat{"Bobby"}};

    // 使用索引进行打印
    for(const animal &a : l){
        switch (a.index())  // 使用index()获得索引，0号索引表示dog，1号索引表示cat
        {
        case 0:
            get<dog>(a).woof(); // 通过get<T>来获得内部的cat或dog实例
            break;
        case 1:
            get<cat>(a).meow();
            break;
        default:
            break;
        }
    }
    cout << "-------------" << endl;

    // 使用类型作为索引
    for(const animal & a : l){  
        if(const auto d(get_if<dog>(&a)); d){   // get_if<dog>返回一个指向dog类型的指针，如果dog实例没有在列表中，则返回null
            d->woof();
        }
        else if(const auto c (get_if<cat>(&a)); c){
            c->meow();
        }
    }
    cout << "--------------" << endl;

    // 直接使用visit方式
    for(const animal &a : l) {
        visit(animal_voice{}, a);   // visit接受一个函数对象和variant实例
    }
    cout << "---------------" << endl;

    cout << "There are " << count_if(begin(l), end(l), is_type<cat>) << " cats and " << 
    count_if(begin(l), end(l), is_type<dog>) << " dogs in the list." << endl;

    return 0;
}
