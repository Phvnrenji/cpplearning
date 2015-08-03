//compstr2.cpp - - comparing strings using arrys
#include <iostream>
#include <string>
int main(){
	using namespace std;
	string word = "?ate";
	
	for(char ch = 'a'; word != "mate"; ++ch){
		word[0] = ch;
		cout << word <<endl;
	}
	return 0;
}