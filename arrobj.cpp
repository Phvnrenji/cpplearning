//函数与array对象，传递指向对象的指针，让函数能够操作原始对象
//arrobj.cpp -- functions with array objects (C++11)
#include <iostream>
#include <string>
#include <array>
using namespace std;
const int Seasons = 4;
const array<string, Seasons> Snames =
	{"Spring", "Summer", "Fall", "Winter"};

void fill(array<double, Seasons> * pa);
void show(array<double, Seasons> da);

int main(){
	array<double, Seasons> expenses;
	fill(&expenses);
	show(expenses);
	return 0;
}

void fill(array<double, Seasons> * pa){
	for(int i=0; i<Seasons; i++){
		cout << "Enter " << Snames[i] << " expenses: ";
		cin >> (*pa)[i];
	}
}
void show(array<double, Seasons> da){
	double total = 0.0;
	cout << "\nExpenses\n";
	for(int i=0; i<Seasons; i++){
		cout << Snames[i] << ": $" << da[i] << endl;
		total += da[i];
	}
	cout << "Total Expenses: $" << total << endl;
}