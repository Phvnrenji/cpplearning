//support.cpp -- use external variable
//compile with external.cpp
#include <iostream>

extern double warming;

void update(double dt);
void local();

using std::cout;

void update(double dt){
   
    extern double warming;
   
    warming += dt;
    cout << "Updating global warming to " << warming;
    cout << " degrees.\n";
    
}

void local(){
    
    double warming = 0.8;
    
    cout << "Local warming = " << warming << " degrees.\n";
    cout << "But global warming = " << ::warming;       //作用域解析运算符(::)
                                                        //放在变量名前面时，该运算符表示使用变量的全局版本
    cout << " degrees.\n";
}