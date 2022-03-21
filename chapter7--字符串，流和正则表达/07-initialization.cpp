// 07-initialization.cpp
// 使用输入文件初始化复杂对象

#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

struct city
{
    string name;
    size_t population;
    double latitude;
    double longitube;
};

istream& operator>>(istream &is, city &c){      // 重载>>操作符，如果读取错误的话对之后的数据会不解析
    is >> ws;       // 去除前后的空格
    getline(is, c.name);
    is >> c.population >> c.latitude >> c.longitube;
    return is;
}

int main(){
    vector<city> l;
    copy(istream_iterator<city>{cin}, {}, back_inserter(l));    // 使用输入流的字符对vector进行填充
    for( const auto &[name, pop, lat, lon] : l){
        // 使用格式化输出，<< left << setw(15)，靠左输出，右边会比较整齐
        cout << left << setw(15) << name << " population: " << pop << " lat: " << lat << " lon: " << lon << endl;
    }
}
