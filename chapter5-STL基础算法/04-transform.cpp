// 04-transform.cpp
// 改变容器内容
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

int main(){
    vector<int> v {1, 2, 3, 4, 5, 6};
    transform(begin(v), end(v), ostream_iterator<int>{cout, ", "}, [] (int i) {return i * i;}); // 将所有容器中的内容拷贝到ostream_iterator中，并接受一个函数对象，在拷贝过程中对每个元素进行操作
    cout << endl;

    auto int_to_string([] (int i) { // 辅助打印函数，使用stringstream辅助打印
        stringstream ss;
        ss << i << "^2 = " << i * i;
        return ss.str();
    });
    vector<string> vs;

    transform(begin(v), end(v), back_inserter(vs), int_to_string);  // 拷贝所有字符到vs中，在拷贝过程中执行上述函数
    copy(begin(vs), end(vs),ostream_iterator<string>{cout, "\n"});  // 打印
}