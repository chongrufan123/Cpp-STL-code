// 11-api.cpp
// 使用智能指针简化处理遗留API

#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Foo{
    string name;
    Foo(string n) : name{move(n)}{
        cout << "CTOR " << name << endl;
    }
    ~Foo(){
        cout << "DTOR " << name << endl;
    }
public:
    static Foo* create_foo(string s) {  // 类的创建
        return new Foo{move(s)};
    }
    static void destroy_foo(Foo *p) { delete p; }   // 类的销毁
};

static shared_ptr<Foo> make_shared_foo(string s){   // 创建一个共享指针并且自定义删除函数
    return {Foo::create_foo(move(s)), Foo::destroy_foo};
}

static unique_ptr<Foo, void (*)(Foo*)> make_unique_foo(string s){   // 对unique_ptr所持有的类型进行修改
    return {Foo::create_foo(move(s)), Foo::destroy_foo};
}

int main(){
    auto ps (make_shared_foo("shared Foo instance"));
    auto pu (make_unique_foo("unique Foo instance"));
}