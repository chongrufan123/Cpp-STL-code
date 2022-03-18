// 03-Iterative_Adapter.cpp
// 使用迭代适配器填充通用数据结构

#include <iostream>
#include <string>
#include <iterator>
#include <sstream>
#include <deque>

using namespace std;

int main(){
    istream_iterator<int> it_cin {cin};
    // istream_iterator是一种输入流迭代器，可以根据实例的具体特化类型，对流进行分析
    istream_iterator<int> end_cin;
    deque<int> v;       // 实例化一个队列
    copy(it_cin, end_cin, back_inserter(v));    // 使用back_inserter辅助函数将队列包在迭代器中
    // back_insert_iterator可以包装vector, deque, list等容器，会调用容器的push_back方法
    istringstream sstr {"123 456 789"}; // 将元素拷贝到队列中部，先使用字符串定义字符流实例
    auto deque_middle (next(begin(v), static_cast<int>(v.size()) / 2)); // 选择列表插入点
    copy(istream_iterator<int>{sstr}, {}, inserter(v, deque_middle));
    // insert_iterator在容器的中间位置插入新元素，第一个参数是容器的实例，第二个参数是迭代器的位置，也就是新元素插入的位置
    initializer_list<int> i12 {-1, -2, -3};
    copy(begin(i12), end(i12), front_inserter(v));  // 插入一些元素到队列中部
    // front_insert_iterator调用容器的push_front函数，可能会损失性能
    copy(begin(v), end(v), ostream_iterator<int> {cout, ", "}); // 将队列中的内容打印出来
    // ostream_iterator输出的流迭代器，推入输出流当中，第二个参数是一个字符串，可以放到各个元素之后，这样会容易插入逗号或换行什么的
    cout << endl;
}