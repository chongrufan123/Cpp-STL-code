// 03-tectonic.cpp
// 无需构造获取std::string

#include <iostream>
#include <string_view>

using namespace std;

void print(string_view v){  // string_view是不包含终止符的
    const auto words_begin (v.find_first_not_of(" \t\n"));  // 去除前面的空格
    v.remove_prefix(min(words_begin, v.size()));    // 收缩视图
    const auto words_end (v.find_last_not_of(" \t\n"));  // 去除后面的空格
    if(words_end != string_view::npos){ 
        v.remove_suffix(v.size() - words_end - 1);  // remove_suffix收缩到代理的大小
    } 
    cout << "length: " << v.length() << " [" << v << "]\n"; // 打印字符串代理及其长度
}

int main(int argc, char *argv[]){
    print(argv[0]);
    print({});
    print("a const char * array");
    print("an std::string_view literal"sv);
    print("an std::string instance"s);

    print(" \t\n foobar \n\t ");

    char cstr[] {'a', 'b', 'c'};
    print(string_view(cstr, sizeof(cstr)));
}