// 01-ratio.cpp
// 转换不同的时间单位--std::ratio
// 测量时间的类型一般放在std::chrono的命名空间中
// system_clock 系统的实时时钟，获得本地时间
// steady_clock 单调型的时间
// high_resolution_clock    STL中可以统计的最细粒度时钟周期的时钟

#include <iostream>
#include <chrono>
#include <ratio>
#include <cmath>
#include <iomanip>
#include <optional>

using namespace std;

using seconds = chrono::duration<double>;
using milliseconds = chrono::duration<double, ratio_multiply<seconds::period, milli>>;
using microseconds = chrono::duration<double, ratio_multiply<seconds::period, micro>>;

static pair<string, seconds> get_input(){
    string s;
    const auto tic (chrono::steady_clock::now());
    if(!(cin >> s)){    // 如果没有成功的话返回一个默认的元组对象
        return { {}, {}};
    }
    const auto toc (chrono::steady_clock::now());

    return {s, toc - tic};
}

int main(){
    while(1){
        cout << "Please type the word \"C++17\" as fast as you can.\n";

        const auto [user_input, diff] = get_input();    // 输入并检测时间

        if(user_input == "") {break; }
        if(user_input == "C++17"){
            cout << "Bravo. You did it in: " << endl << fixed << setprecision(2) << setw(12) << diff.count() << " seconds." << endl << setw(12);
            cout << milliseconds(diff).count() << " milliseconds.\n" << setw(12) << microseconds(diff).count() << " microseconds.\n";
            break;            
        }
        else{
            cout << "Sorry, your input does not match." << endl;
            cout << "You may try again.\n";
        }
    }
}