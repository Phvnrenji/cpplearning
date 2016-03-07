//atrctfun.cpp -- functions with a structureargument
#include <iostream>
#include <cmath>

struct rect{
	double x;
	double y;
};

struct polar{
	double distance;
	double angle;
};

polar rect2polar(rect xypos);
void show_polar(polar dapos);

int main(){
	using namespace std;
	
	rect xy_point;
	cout << "Enter the x and y values: ";
	// cin >> xy_point.x;
	// cin >> xy_point.y;
	while(cin >> xy_point.x >> xy_point.y){
		polar po_point = rect2polar(xy_point);
		show_polar(po_point);
		cout << "Next two numbers (q to quit): ";	
	}
	cout << "Done.\n";
	
	return 0;
}

polar rect2polar(rect xypos){
	polar answer;
	
	answer.distance = 
		sqrt( xypos.x * xypos.x + xypos.y * xypos.y);
	answer.angle = atan2(xypos.y, xypos.x);
	/*
	使用水平和垂直坐标来计算距离：distance = sqrt(x*x + y*y)
	函数atan2()根据x和y的值计算角度：angle = atan2(y, x)
	以上两个函数是数学库中的函数，因此必须包含头文件cmath
	*/
	return answer;
}

void show_polar(polar dapos){
	using namespace std;
	const double Rad_to_deg = 57.29577951;
	
	cout << "distance = " << dapos.distance;
	cout << ", angle = " << dapos.angle * Rad_to_deg;
	cout << " degrees\n";
}