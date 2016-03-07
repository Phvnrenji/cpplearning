//使用new和delete来储存通过键盘输入的字符串
//delete.cpp - - using the delete operator
#include <iostream>
#include <cstring>   //or string.h

using namespace std;

char* getname(void); //function prototype

int main()
{
	
	char* name ;// creat pointer but no storage 
	//返回值(地址)被赋给指针name，该指针是在main中定义的，但它指向getname函数中分配的内存块
	name = getname();
	cout << name << " at " << (int*)name << "\n";
	delete [] name;  //memory free 

	name = getname(); //reuse freed memory
	cout << name << " at " << (int*)name << "\n";
	delete [] name;//memory freed again
	return 0;

}


//函数getname使用cin将输入的单词放到temp数组中，然后使用new分配新内存
char* getname()
{
	char temp[80];
	cout << "Enter last name : ";
	cin >> temp;
	char* pn = new char[strlen(temp)+1];//使用strlen(temp)+1个字符来储存该字符串
	strcpy(pn, temp); //使用标准库函数strcpy将temp中的字符串复制到新的内存块中

	return pn;  //temp lost when function ends
}
