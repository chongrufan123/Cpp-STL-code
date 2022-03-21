// 01-string.cpp
// 创建、连接和转换字符串
#include <iostream>
#include <string>
#include <string_view>
#include <sstream>
#include <algorithm>

using namespace std;
using namespace std::literals;

int main(){
    string a {"a"};
    auto b ( "b"s );    // 可以用""s来进行string的构造
    string_view c { "c" };  // string_view可以不将字符串拷贝到内部内存中，而是对输入字符串直接引用
    auto d ("d"sv);     // 可以用""sv来进行string_view的构造
    cout << a << ", " << b << endl;
    cout << c << ", " << d << endl;
    cout << a + b << endl;      // 可以使用+将两个字符串结合在一起
    cout << a + string{c} << endl;   // 对于经过代理的来说，只有先获得代理的字符串之后才可以进行操作，也就是拷贝出来一份，因为string_view的数据没有终止符

    ostringstream o;    // 将任意变量通过流对象进行打印（类似cout），打印在字符串缓存
    o << a << " " << b << " " << c << " " << d;
    auto concatenated (o.str());    // 构造string对象
    cout << concatenated << endl;   // 打印在屏幕

    transform(begin(concatenated), end(concatenated), begin(concatenated), ::toupper);  // 将转换为大写字母
    cout << concatenated << endl;
}