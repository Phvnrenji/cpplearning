//strgfun.cpp -- functions with a string argument
//将C—风格字符串作为参数的函数
#include <iostream>
unsigned int c_in_str(const char * str, char ch);
int main(){
	using namespace std;
	char mmm[15] = "minimum";
	// char *wail = "ululate"; 
	/*warning: deprecated conversion from string constant to ‘char*’ [-Wwrite-strings]*/
	/*
	将字符串作为参数传递给函数，则表示字符串的方式有三种：
	>>> char 数组
	>>> 用引号括起的字符串常量
	>>> 被设置位字符串的地址的char指针 (这里用这种方式报错?) 
	*/
	unsigned int ms = c_in_str(mmm, 'm');
	// unsigned int us = c_in_str(wail, 'u');
	cout << ms << " m characters in " << mmm << endl;
	// cout << us << " u characters in " << wail << endl;
	return 0; 
}

unsigned int c_in_str(const char * str, char ch){
	unsigned int count = 0;
	while (*str){
		if (*str == ch){
			count++;
		}
		str++;
	}
	return count;
}