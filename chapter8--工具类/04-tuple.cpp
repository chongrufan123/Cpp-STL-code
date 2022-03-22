// 04-tuple.cpp
// 对元组使用函数

#include <iostream>
#include <iomanip>
#include <tuple>
#include <functional>
#include <string>
#include <list>

using namespace std;

static void print_student(size_t id, const string &name, double gpa){   // 将学生的相关信息打印
    cout << "Student " << quoted(name) << ", ID: " << id << ", GPA: " << gpa << endl;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
}

int main(){
    using student = tuple<size_t, string, double>;  // 给一组元组类型起一个别名
    student john {123, "John Doe"s, 3.7};
    {
        const auto &[id, name, gpa] = john;
        print_student(id, name, gpa);
    }
    cout << "-----------" << endl;
    auto arguments_for_later = {
        make_tuple(234, "John Doe"s, 3.7),
        make_tuple(345, "Billy Foo"s, 4.0),
        make_tuple(456, "Cathy Bar"s, 3.5),
    };
    for(const auto &[id, name, gpa] : arguments_for_later){ // 循环打印学生信息
        print_student(id, name, gpa);
    }
    
    cout << "-----------" << endl;
    apply(print_student, john); // 直接将元组应用于函数，函数可以接受一个函数指针或一个函数对象和一个元组，然后自动进行解包
    cout << "-----------" << endl;

    for(const auto &args : arguments_for_later){    // 在循环中也可以这样应用
        apply(print_student, args);
    }
    cout << "----------" << endl;
}