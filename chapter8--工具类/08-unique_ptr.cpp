// 08-unique_ptr.cpp
// 自动化管理资源--std::unique_ptr
// 请尽可能的使用智能指针，而非new;delete

#include <iostream>
#include <memory>

using namespace std;

class Foo{
public:
    string name;

    Foo(string n) : name{move(n)} {cout << "CTOR " << name << endl;}
    ~Foo() {cout << "DTOR " << name << endl;}
};

void process_item(unique_ptr<Foo> p){   // 处理Foo类型实例，并将其名称进行打印
    if(!p) {return;}
    cout << "Processing " << p->name << endl;
}

int main(){
    {   // 两种创建Foo智能指针的办法
        unique_ptr<Foo> p1 {new Foo{"foo"}};
        auto p2(make_unique<Foo>("bar"));
    }   // 离开这个代码段，所创建的对象会自动销毁，并释放内存
    process_item(make_unique<Foo>("fool")); // unique指针的生命周期就在这个函数当中

    auto p1(make_unique<Foo>("foo2"));
    auto p2(make_unique<Foo>("foo3"));

    process_item(move(p1)); // 将p1移动到这个函数中，当这个函数返回时，p1销毁
    cout << "End of main()" << endl;
}