#include <iostream>

using namespace std;
const int ArSize = 6; 

int main(){
	//cout << "Enter your code : ______\b\b\b\b\b\b";
	//long code;
	int cnt = 0;
	//char line[ArSize];
	char code[ArSize] = {1,5,4,8,5,3};
	for(int i = 0; i < 3; i++){
		cout << "Enter your code : _____\b\b\b\b\b";
		char line[ArSize];
		cin.get(line, ArSize);
		for(int j = 0; j <= ArSize; j++){
			if(line[j] == code[j]){
				cnt++;
			}	
		}
		if(cnt < ArSize){
			cout << "Not correct !";
			continue;
		}
		else
			break;
	}
	if(cnt == ArSize)
		cout << "bingo";
	else
		cout << "boom";
	//cout << "\aYou entered " << code << "...\n";
	return 0;
}
