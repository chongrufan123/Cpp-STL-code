// 01-copy.cpp
// 容器间相互复制元素

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <tuple>
#include <iterator>
#include <algorithm>

using namespace std;

namespace std   // 重载<<流操作，原来是没有的，现在加上
{
    ostream& operator<<(ostream &os, const pair<int, string> &p){
        return os << "(" << p.first << ", " << p.second << ")";
    }
} // namespace std

int main(){
    vector<pair<int, string>> v {   // 用pair填充vector
        {1, "one"}, {2, "two"}, {3, "three"}, {4, "fore"}, {5, "five"}
    };
    map<int, string> m; // 声明一个map变量，关联整型和字符串型
    copy_n(begin(v), 3, inserter(m, begin(m))); // copy_n将vector中的数据拷贝到map中，但是因为结构体不同，所以要用insert_iterator适配器进行变换

    auto shell_it (ostream_iterator<pair<int, string>>{ //打印map中的内容，ostream_iterator作为一个容器，将要输出的东西放到这里然后拷贝出去
        cout, ", "
    });

    copy(begin(m), end(m), shell_it); 
    cout << endl;

    m.clear();      //对m中的内容进行清理
    move(begin(v), end(v), inserter(m, begin(m)));  // 将vector中的内容全部移动到map中

    copy(begin(m), end(m), shell_it); 
    cout << endl;
    copy(begin(v), end(v), shell_it); 
    cout << endl;

    return 0;
}
