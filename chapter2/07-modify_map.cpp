// 07-modify_map.cpp
// 高效的修改 std::map 元素的键值
// 用到了C++17的内容，编译时需要加"--std=c++17"

// map的键一般是const类型，不允许用户进行修改，所以当确实不得不修改时，可以采用下述方法


#include  <iostream>
#include <map>

using namespace std;
template <typename M>
// 打印map的键和值
void print(const M &m){
    cout << "Race placement:\n";
    for(const auto &[placement, driver] : m){
        cout << placement << ": " << driver << endl;
    }
}

int main(){
    map<int, string> race_placement {
        {1, "Mario"}, {2, "Luigi"}, {3, "Bowser"},
        {4, "Peach"}, {5, "Yoshi"}, {6, "Koopa"},
        {7, "Toad"}, {8, "Donkey Kong Jr."}
    };  // 实例化一个map，表示驾驶员的初始的姓名和排位
    print(race_placement);  // 打印当前的map
    auto a(race_placement.extract(3));  // extract可以从map中删除元素，而且不会内存重分配
    auto b(race_placement.extract(8));  
    print(race_placement);  // 打印当前的map
    swap(a.key(), b.key()); // 交换键
    race_placement.insert(move(a));    // 将提取出来的节点插入到map
    race_placement.insert(move(b));
    print(race_placement);

    return 0;

}

