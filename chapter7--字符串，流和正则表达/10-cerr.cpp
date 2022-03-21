// 10-cerr.cpp
// 使用特定代码段将输出重定向到文件

#include <iostream>
#include <fstream>

using namespace std;

class redirect_cout_region{
    using buftype = decltype(cout.rdbuf()); // 检查实体的声明类型

    ofstream ofs;
    buftype buf_backup;

public:
    explicit
    redirect_cout_region(const string &filename) : ofs{filename}, buf_backup{cout.rdbuf(ofs.rdbuf())} {}    // 构造函数
    redirect_cout_region() : ofs{}, buf_backup{cout.rdbuf(ofs.rdbuf())}{}   // 默认构造函数
    ~redirect_cout_region() { cout.rdbuf(buf_backup); } // 析构函数，对重定向进行恢复
};

void my_output_heavy_function(){    // 模拟有很多输出的函数
    cout << "some output" << endl;
    cout << "this function does really heavy work\n";
    cout << "... and lots of it...\n";
}

int main(){
    cout << "Readable from normal stdout\n";    // 进行一次标准打印
    {   
        redirect_cout_region _ {"output.txt"};   // 进行重定向
        cout << "Only visible in output.txt\n";
        my_output_heavy_function();
    }
    {
        redirect_cout_region _; // 不传递参数，所有的输出都会丢弃
        cout <<"This output will completely vanish\n";
    }
    cout << "Readable from normal stdout again\n";
}