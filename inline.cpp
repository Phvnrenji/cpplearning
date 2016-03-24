//inline.cpp -- using an inline function
#include <iostream>

//an inline function definition
inline double square(double x) { return x * x;}

int main(){
    using namespace std;
    double a, b;
    double c = 13.0;
    
    a = square(5.0);
    b = square(4.5 + 7.5);  //内联函数可以传递表达式
    cout << "a = " << a << ", b = " << b << endl;
    cout << "c = " << c;
    cout << ", c squared = " << square(c++) << endl;    //内联函数和常规函数一样也是按值传递参数的，与宏定义的文本替换不同
    cout << "Now c = " << c << endl;
    return 0;
}