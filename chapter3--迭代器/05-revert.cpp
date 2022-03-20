#include <iostream>
#include <list>
#include <iterator>

using namespace std;

int main(){
    list<int> l {1, 2, 3, 4, 5};
    copy(l.rbegin(), l.rend(), ostream_iterator<int> {cout, ", "});
    cout << "\n";
    copy(make_reverse_iterator(end(l)), make_reverse_iterator(begin(l)), ostream_iterator<int>(cout, ", "));    // 如果容器不提供rbegin或rend的话，可以用工厂函数make_reverse_iterator替代

}