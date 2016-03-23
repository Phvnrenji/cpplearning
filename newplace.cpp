//newplace.cpp -- using placement new
//常规new运算符和定位new运算符之间的一些重要差别
#include <iostream>
#include <new>

const int BUF = 512;
const int N = 5;
char buffer[BUF];

int main(){
    using namespace std;
    double *pd1, *pd2;
    int i;
    cout << "Calling new and placement new:\n";
    pd1 = new double[N];            //use heap
    pd2 = new (buffer) double[N];   //use buffer array
    for(i = 0; i < N; ++i){
        pd2[i] = pd1[i] = 1000 + 20.0 * i;
    }
    cout << "Memory addresses:\n" << " heap: " << pd1
         << " static: " << (void *) buffer << endl;     //buffer是char指针，需要强制转换，不然输出一个字符串
    cout << "Memory contents:\n";
    for(i = 0; i < N; ++i){
        cout << pd1[i] << " at " << &pd1[i] << "; ";
        cout << pd2[i] << " at " << &pd2[i] << endl;
    }
    
    cout << "\nCalling new and placement new a second time:\n";
    double *pd3, *pd4;
    pd3 = new double[N];
    pd4 = new (buffer) double[N];
    for(i = 0; i < N; ++i){
        pd4[i] = pd3[i] = 1000 + 40.0 * i;        
    }
    cout << "Memory contents:\n";
    for(i = 0; i < N; ++i){
        cout << pd3[i] << " at " << &pd3[i] << "; ";
        cout << pd4[i] << " at " << &pd4[i] << endl;
    }
    
    cout << "\nCalling new and placement new a second time:\n";
    delete [] pd1;      //释放内存块，因此接下来再次调用new时，该内存块是可用的
    pd1 = new double[N];    
    pd2 = new (buffer + N * sizeof(double)) double[N];  //pd2改为指向buffer的N * sizeof(double)之后的内存块
    for(i = 0; i < N; ++i){
        pd2[i] = pd1[i] = 1000 + 60.0 * i;        
    }
    cout << "Memory contents:\n";
    for(i = 0; i < N; ++i){
        cout << pd1[i] << " at " << &pd1[i] << "; ";
        cout << pd2[i] << " at " << &pd2[i] << endl;
    }
    
    //delete只能用于指向常规new运算符分配的堆内存，而buffer指定的内存是静态内存，位于delete的管辖区域之外
    delete [] pd1;
    delete [] pd3;
    
    return 0;
}