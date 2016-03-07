#include <iostream>

double harm_average(int x, int y);

int main(){
	using namespace std;
	int num1;
	int num2;
	double result;
	while(1){
		cout << "Please enter num 1: ";
		cin >> num1;
		cout << "Please enter num 2: ";
		cin >> num2;
		if (num1==0 || num2==0)
			break;
		else
			result = harm_average(num1, num2);
		cout << "The harmonic average of the two numbers is : " << result << endl;
	}

	return 0;
}

double harm_average(int x, int y){
	using namespace std;
	double harm;
	harm = 2.0*x*y/(x+y);
	return harm;
}

