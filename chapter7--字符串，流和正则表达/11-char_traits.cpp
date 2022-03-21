// 11-char_traits.cpp
// 通过集成std::char_traits创建自定义字符串类
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

static constexpr char tolow(char c){
    switch (c)
    {
    case 'A'...'Z':
        return c - 'A' + 'a';
        break;
    
    default:
        return c;
        break;
    }
}
    
class lc_traits : public char_traits<char> {    // 继承标准字符特化类，将字符串的大写改变为小写
public:
    static constexpr
    void assign(char_type& r, const char_type& a){
        r = tolow(a);
    }
    static char_type* copy(char_type* dest, const char_type* src, size_t count){    // 将整个字符串拷贝到缓冲区，将所有源字符串映射到目标字符串，并对应其小写版本
        transform(src, src + count, dest, tolow);
        return dest;
    }
};

class ci_traits : public char_traits<char> {    // 对字符串做大小写敏感的比较
public:
    static constexpr bool eq(char_type a, char_type b){
        return tolow(a) == tolow(b);
    }
    static constexpr bool lt(char_type a, char_type b){
        return tolow(a) < tolow(b);
    }

    static constexpr int compare(const char_type* s1, const char_type* s2, size_t count){   // 比较两个字符串的长度
        for(; count; ++s1, ++s2, --count){
            const char_type diff (tolow(*s1) - tolow(*s2));
            if(diff < 0) { return -1; }
            else if (diff > 0) { return +1;}
        }
        return 0;
    }

    static constexpr const char_type* find(const char_type* p, size_t count, const char_type& ch){  // 大小写不敏感函数
        const char_type find_c {tolow(ch)};

        for(; count != 0; --count, ++p){
            if(find_c == tolow(*p)) {return p;}
        }
        return nullptr;
    }
};

using lc_string = basic_string<char, lc_traits>;    // 定义两种新的字符串类型
using ci_string = basic_string<char, ci_traits>;

ostream& operator<<(ostream& os, const lc_string& str){ // 输出流操作符重载
    return os.write(str.data(), str.size());
}
ostream& operator<<(ostream& os, const ci_string& str){
    return os.write(str.data(), str.size());
}

int main(){
    cout << " string: " << string("Foo Bar Baz") << endl
        << "lc_string: " << lc_string("Foo Bar Baz") << endl
        << "ci_string: " << ci_string("Foo Bar Baz") << endl;
    ci_string user_input {"MaGiG PaSsWoRd!"};
    ci_string password {"magic password!"};
    if (user_input == password){
        cout << "Passwords match: \"" << user_input << "\" == \"" << password << "\"" << endl;
    }
}