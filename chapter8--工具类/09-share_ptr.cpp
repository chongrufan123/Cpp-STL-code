// 09-share_ptr.cpp
// 处理共享堆内存--std::shared_ptr
// share_ptr内部有一个计数器，只有当最后一个持有者销毁时，此处内存才会被销毁
// 和unique_ptr主要区别在于可复制性
// shared_ptr避免在循环引用的指针间进行，防止内存泄漏

#include <iostream>
#include <memory>

using namespace std;

class Foo{
public:
    string name;
    Foo(string n) : name{move(n)}{
        cout << "CTOR " << name << endl;
    }
    ~Foo(){
        cout << "DTOR " << name << endl;
    }
};

void f(shared_ptr<Foo> sp){ // 接受共享指针作为参数的方式
    cout << "f: use counter at " << sp.use_count() << endl;
}

int main(){
    shared_ptr<Foo> fa; // 声明一个空的共享指针
    {   // 两种方式构造Foo的shared_ptr指针
        cout << "Inner scope begin\n";
        shared_ptr<Foo> f1 {new Foo{"foo"}};
        auto f2 (make_shared<Foo>("bar"));
        cout << "f1's use counter at " << f1.use_count() << endl;
        fa = f1;    // 进行拷贝，这是计数器为2
        cout << "f1's use counter at " << f1.use_count() << endl;
    }   // 离开代码段，f1和f2被销毁，但是fa还存在
    cout << "Back to outer scope" << endl;

    cout << fa.use_count() << endl;

    cout << "first f() call" << endl;
    f(fa);  // 直接使用拷贝方式调用fa
    cout << "second f() call" << endl;
    f(move(fa));    // 将指针移动到函数中，用f去替代fa
    cout << "end of main()" << endl;


}