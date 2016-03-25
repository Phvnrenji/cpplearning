//swaps.cpp -- sawaping with references and with pointers
//================================================================
// 引用变量：
// int rats; int & rodents = rats;
// &不是地址运算符，而是类型标识符的一部分
// 上述引用声明允许将rats和rodents互换----它们指向相同的值和内存单元
// 引用变量的主要用途是作为函数参数，具体地说是结构和对象参数
// 引用看上去很像伪装表示的指针，但是它们之间还是有差别的...
//================================================================
#include <iostream>

void swapr(int & a, int & b);
void swapp(int * p, int * q);
void swapv(int a, int b);

int main(){
    using namespace std;
    int wallet1 = 300;
    int wallet2 = 350;
    cout << "Wallet1 = $" << wallet1;
    cout << " Wallet2 = $" << wallet2 << endl;
    
    cout << "Using references to sawap contents again:\n";
    swapr(wallet1, wallet2);
    cout << "wallet1 = $" << wallet1;
    cout << " Wallet2 = $" << wallet2 << endl;
    
    cout << "Using pointers to sawap contents again:\n";
    swapp(&wallet1, &wallet2);
    cout << "wallet1 = $" << wallet1;
    cout << " Wallet2 = $" << wallet2 << endl;
    
    cout << "Tring to use passing by value:\n";
    swapv(wallet1, wallet2);
    cout << "wallet1 = $" << wallet1;
    cout << " Wallet2 = $" << wallet2 << endl;
    
    return 0;
}

void swapr(int & a, int & b){
    int temp;
    
    temp = a;
    a = b;
    b = temp;
}

void swapp(int * p, int * q){
    int temp;
    
    temp = *p;
    *p = *q;
    *q = temp;
}

void swapv(int a, int b){
    int temp;
    
    temp = a;
    a = b;
    b = temp;
}