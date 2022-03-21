// 05-count.cpp
// 计算文件中的单词数量

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

template<typename T>
size_t wordcount(T &is){    // 创建一个输入迭代器，对输出字符进行标记，然后交给distance计算
    return distance(istream_iterator<string>{is}, {});  // distance接受两个迭代器作为参数，然后确认从一个迭代器到另一个需要多少距离
}

int main(int argc, char **argv){
    size_t wc;
    if(argc == 2){
        ifstream ifs{argv[1]};
        wc = wordcount(ifs);
    }
    else{
        wc = wordcount(cin);
    }
    cout << "there are " << wc << " words\n";
}