// 04-input.cpp
// 从用户的输入读取数值

#include <iostream>

using namespace std;

int main(){
    cout << "Please Enter two numbers: \n";
    int x;
    double y;
    if(cin >> x >> y){
        cout << "You entered: " << x << " and " << y << endl;
    }
    else{
        cout << "Oh no, that did not go well!\n";
        cin.clear();    // 清除输入流的错误状态
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 完成丢弃的任务，指定丢弃的数量，直到下一个换行符为止
    }
    cout << "now please enter some comma-separated names:\n";
    for(string s; getline(cin >> ws, s, ',');){ // ws首先对输入流进行预处理，防止出现开头有空格的现象
        if(s.empty()){break;}
        cout << "name: \"" << s << "\"\n";
    }
}
