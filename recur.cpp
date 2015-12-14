//递归-----函数自己调用自己
//recur.cpp -- using recursion
#include <iostream>
void countdown(int n);

int main(){
	countdown(4);
	return 0;
}

void countdown(int n){
	std::cout << "Counting down ..." << n << "(n at: " << &n << ")" << std::endl;
	if(n > 0)
		countdown(n-1);
	std::cout << n << ": kaboom! (n at: " << &n << ")\n" ;
}