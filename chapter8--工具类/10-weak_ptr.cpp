// 10-weak_ptr.cpp
// 对共享对象使用弱指针
// 只有最后一个指向对象的弱指针销毁，控制块才会被销毁，但此时内存块已经没有了
#include <iostream>
#include <iomanip>
#include <memory>

using namespace std;

struct Foo {
    int value;
    Foo(int i) : value{i} {}
    ~Foo() { cout << "DTOR Foo " << value << '\n'; }
};

void weak_ptr_info(const weak_ptr<Foo> &p){ // 对弱指针的信息进行打印，expired()表示弱指针指向的对象是否依然存在，use_count()告诉我们shared_ptr对象的引用次数
    cout << "------" << boolalpha << "\nexpired: " << p.expired() << "\nuse_count: " << p.use_count() << "\ncontent: ";
    if(const auto sp(p.lock()); sp){    // 访问对象时要调用lock函数，返回一个指向对象的共享指针
        cout << sp->value << endl;
    }
    else{
        cout << "<null>\n";
    }
}

int main(){
    weak_ptr<Foo> weak_foo; // 实例化一个空的弱指针
    weak_ptr_info(weak_foo);    // 打印空的弱指针
    {
        auto share_foo (make_shared<Foo>(1337));    // 实例化一个共享指针
        weak_foo = share_foo;   // 将共享指针拷贝给空指针，此时计数还为1
        weak_ptr_info(weak_foo);    // 打印空的弱指针
    }   // 离开代码段，Foo被销毁
    weak_ptr_info(weak_foo);    // 打印空的弱指针
}

