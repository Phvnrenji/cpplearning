//variables with external and internal linkage
//外部变量，局部变量，外部静态变量的使用
#include <iostream>
int tom = 3;
int dick = 30;
static int harry = 300;

void remote_access();

int main(){
    using namespace std;
    cout << "main() reports the following addresses:\n";
    cout << &tom << " = &tom, " << &dick << " = &dick, "
         << &harry << " = &harry\n";
    remote_access();
    
    return 0;
}
