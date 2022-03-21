// 14-error.cpp
// 从std::iostream错误中获取可读异常

#include <iostream>
#include <fstream>
#include <system_error>
#include <cstring>

using namespace std;

int main(){
    ifstream f;
    f.exceptions(f.failbit | f.badbit); // 启动异常
    try{
        f.open("non_existant.txt");

        int i;
        f >> i;

        cout << "integer has value: " << i << endl;
    }
    catch(ios_base::failure& e){
        cerr << "Caught error: ";
        if(errno){  // errno告诉发生哪种级别的错误
            cerr << strerror(errno) << endl;
        }
        else{
            cerr << e.what() << endl;
        }
    }
}