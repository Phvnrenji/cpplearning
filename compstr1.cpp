//compstr1.cpp --  comparing strings using arrays
//C-风格字符串的比较
#include <iostream>
#include <cstring>
int main(){
	using namespace std;
	char word[5] = "?ate";
	for(char ch = 'a';
		strcmp(word,"mate");
		ch++){
			word[0] = ch;
			cout << word <<endl;
		}
	return 0;
}