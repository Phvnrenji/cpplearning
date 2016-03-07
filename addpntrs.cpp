//指针、数组和指针算数
//addpntrs.cpp -- pointer addition
#include <iostream>
using namespace std;

int main(){
	
	double wages[3] = {1000.0,2000.0,3000.0};
	short stacks[3] = {3,2,1};
	
	//这是两种获取数组地址的方式
	double* pw = wages;     //数组的名字=地址
	short* ps = &stacks[0]; //运用地址操作符
	
	//with array element
	cout << "pw = " << pw <<", *pw = " << *pw <<endl;
	pw = pw + 1;
	cout << "add 1 to the pw pointer:\n";
	cout << "pw = " << pw <<", *pw = " << *pw << "\n\n";	

	cout << "ps = " << ps << ", *ps = " << *ps <<endl;
	ps = ps + 1;
	cout << "add 1 to the ps pointer:\n";
	cout << "ps = " << ps << ", *ps = " << *ps << "\n\n";


	cout << "access two elements with array notation\n";
	cout << "stacks[0] = " << stacks[0]
	     << " , stacks[1] = " << stacks[1] <<endl;
	
	cout << "access two elements with pointer notation\n";
	cout << "*stacks = " << *stacks
	     << ", *(stacks + 1) = " << *(stacks +1) <<endl;

	cout << sizeof(wages) << " = size of wages array\n";
	cout << sizeof(pw) << " = size of pw pointer\n";
	
	return 0;	
}
<<<<<<< HEAD

////////////////////////////////////////////////////////////////////////////////
//指针和数组基本等价的原因在于指针算数(pointer arithmetic)和C++内部处理数的方式
//当我们将证书变量加1后，其值将增加1；
//但将指针变量加1后，增加的量等于它指向的类型的字节数。
//将指向double的指针加1后，如果系统对double使用8个字节存储，则数值将增加8；
//将指向short的指针加1后，如果系统对short使用2个字节存储，则指针值将增加2。
//该程序还说明了了：C++将数组名解释为地址。
=======
>>>>>>> 985a94ea181bfb4122cfd5151943f4868095957d
