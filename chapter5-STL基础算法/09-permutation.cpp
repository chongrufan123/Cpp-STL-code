// 09-permutation.cpp
// 生成输入序列的序列

#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>

using namespace std;

int main(){
    vector<string> v {istream_iterator<string>{cin}, {}};
    sort(begin(v), end(v));
    do {
        copy(begin(v), end(v), ostream_iterator<string> {cout, ", "});
        cout << endl;
    }while(next_permutation(begin(v), end(v)));
    // next_permutation接受一组迭代器，当找到下一个置换时返回true，否则返回false
}