//static.cpp -- using a static local variable
//静态存储的持续性和无链接性
#include <iostream>
//constants
const int ArSize = 10;
//function prototype
void strcount(const char * str);

int main(){
    using namespace std;
    char input[ArSize];
    char next;
    
    cout << "Enter a line:\n";
    cin.get(input, ArSize);
    //方法cin.get(input, ArSize)将一直读取输入，直到到达行尾或读取了ArSize-1个字符为止。
    //它把换行符留在队列中。
    while(cin){
        cin.get(next);
        //使用cin.get(next)读取行输入后的字符
        while(next != '\n'){
            cin.get(next);          
        }
        strcount(input);
        cout << "Enter next line (empty line to quit):\n";
        //利用一个事实:试图使用get(char*,int)读取空行将导致cin为false，即结束循环
        cin.get(input, ArSize); 
    }
    cout << "Bye\n";
    return 0;
}

void strcount(const char * str){
    using namespace std;
    static int total = 0;   //静态变量只有在最初被设置为0，以后在两次函数调用之间，其值保存不变，固能够记录字符总数
    int count = 0;  //每次被调用时重置为0
    
    cout << "\"" << str << "\" contains ";
    while(*str++){
        count++;
    }               //数组长度为10，因此程序从每行读取的字符数都不超过9个
    total += count;
    cout << count << " characters\n";
    cout << total << " characters total\n";
}
