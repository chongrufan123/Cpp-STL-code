// 06-format.cpp
// 格式化输出

#include <iostream>
#include <iomanip>
#include <locale>

using namespace std;

void print_aligned_demo(int val, size_t width, char fill_char = ' '){   // 以不同的方式打印一个数值，能接受使用一种字符对宽度进行填充，默认为空格
    cout << "======================\n";
    cout << setfill(fill_char);
    cout << left << setw(width) << val << endl; // setw设置打印数字的最小字符数输出个数，left，right控制从哪边开始填充
    cout << right << setw(width) << val << endl;
    cout << internal << setw(width) << val << endl;
}

int main(){
    print_aligned_demo(123456, 15);
    print_aligned_demo(123456, 15, '_');;

    cout << hex << showbase;    // 告诉输出流输出的格式,十六进制
    print_aligned_demo(0x123abc, 15);

    cout << oct;    // 八进制
    print_aligned_demo(012345623, 15);

    cout << "A hex number with upper case letters: " << hex << uppercase << 0x1234abc << '\n';  // 将0x中的x转为大写字母，abc也转为大写字母
    cout << "A number: " << 100 << endl;
    cout << dec;    // 切换为十进制

    cout << "Oops. now in decimal again: " << 100 << endl;

    cout << "true/false values: " << true << ", " << false << endl;
    cout << boolalpha << "true/false values: " << true << ", " << false << endl;    // 通过boolalpha可以将true和false转换为文本形式输出
    cout << "doubles: " << 12.3 << ", " << 12.0 << ", " << showpoint << 12.0 << "\n";   // 配置浮点数，是否展示小数点
    cout << "scientific double: " << scientific << 123000000000.123 << endl;    // 科学计数法
    cout << "fixed double: " << fixed << 123000000000.123 << endl;  // 固定浮点计数法
    cout << "Very precise double: " << setprecision(10) << 0.000000001 << endl;
    cout << "Less precise double: " << setprecision(2) << 0.000001 << endl; // 设定输出位数（精度）

}