// 03-vector
// 快速或安全的访问std::vector实例的方法
#include <iostream>
#include <vector>
using namespace std;

int main(){
    const size_t container_size(1000);  // typedef unsigned long size_t 生成一个无符号长整型1000
    vector<int> v(container_size, 123);     // 在vector中放1000个123
    cout << "out of range element value: " << v[container_size + 10] << endl;   // 通过[]访问范围之外的元素

    cout << "out of range element value: " << v.at(container_size + 10) << endl;    // 通过at函数访问范围之外的元素

    // at函数和[]实现相同的内容，但是at函数会首先进行自检，保证访问的数组没有越界，所以执行时间也会稍微慢一点点
    return 0;
}