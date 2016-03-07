//函数如何使用指针来处理数组
//arrfun.cpp -- functions with an array argument
#include <iostream>
const int ArSize = 8;
int sum_arr(int arr[], int n);
using namespace std;

int main(){
	int cookies[ArSize] = {1,2,4,8,16,32,64,128};
	cout << cookies << " = array address, ";
	cout << sizeof cookies << " = sizeof cookies\n";
	int sum = sum_arr(cookies, ArSize);
	cout << "Total cookies eaten: " << sum << endl;
	sum = sum_arr(cookies, 3);
	cout << "First three esters ate: " << sum << " cookies\n";
	sum = sum_arr(cookies + 4, 4);
	cout << "Last four eaters ate: " << sum << " cookies\n";
	return 0;
}

int sum_arr(int arr[], int n){
	int total = 0;
	cout << arr << " = arr, ";
	cout << sizeof arr << " = sizeof arr\n";
	for(int i=0; i<n; i++){
		total = total + arr[i];
	}
	return total;
}