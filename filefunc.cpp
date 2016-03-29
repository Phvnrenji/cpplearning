//filefunc.cpp -- function with ostream & parameter
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

void file_it(ostream & os, double fo, const double fe[], int n);
const int LIMIT = 5;

int main(){
    ofstream fout;
    const char * fn = "ep-data.txt";
    fout.open(fn);
    if(!fout.is_open()){
        cout << "Can't open " << fn << ". Bye.\n";
        exit(EXIT_FAILURE);
    }
    double objective;
    cout << "Enter the focal length of your "
            "telescope objective in mm: ";
    cin >> objective;
    double eps[LIMIT];
    cout << "Enter the focal length, in mm, of " << LIMIT
         << " eyepiece:\n";
    for(int i = 0; i < LIMIT; ++i){
        cout << "Eyepiece #" << i + 1 << ": ";
        cin >> eps[i];
    }
    
    //将数据写入到文件ep-data.txt中：
    file_it(fout, objective, eps, LIMIT);
    
    //将同样的信息以同样的格式显示到屏幕上
    file_it(cout, objective, eps, LIMIT);
    cout << "Done.\n";
    
    return 0;
}

void file_it(ostream & os, double fo, const double fe[], int n){
    //参数os（其类型为ostream &）可以指向ostream对象（如cout）， 也可以指向ofstream对象（如fout）。
    ios_base::fmtflags initial; //setf返回调用它之前有效的所有格式化设置。ios_base::fmtflags 是存储这种信息所需的数据类型名称
                                //因此，将返回值赋给initial将存储调用file_it()之前的格式化设置，然后便可以使用变量initial作为
                                //参数来调用setf，将所有的格式化设置恢复到原来的值。
    
    //方法setf使得能够设置各种格式化状态
    initial = os.setf(ios_base::fixed); //将对象置于使用定点表示法的模式
    os.precision(0);    //方法percision指定显示多少位小数（假定对象处于定点模式下）
    os << "Focal length of objective: " << fo << " mm\n";
    os.setf(ios::showpoint);    //将对象置于显示小数点的模式，即使小数点部分为零
    os.precision(1);
    os.width(12);   //方法width设置下一次输出操作使用的字段宽度，该设置只在显示下一个值时有效，过后恢复默认(0)
    os << "f.l. eyepiece";
    os.width(15);
    os << "magnification" << endl;
    for(int i = 0; i < n; ++i){
        os.width(12);
        os << fe[i];
        os.width(15);
        os << int (fo/fe[i] + 0.5) << endl;
    }
    os.setf(initial);
}