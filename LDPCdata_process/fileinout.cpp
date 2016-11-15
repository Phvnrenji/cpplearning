//2016/11/15
//Dvnean
//Version: 2.0

#include <iostream>
#include <fstream>
#include <cstdlib>

const int FILE_SIZE = 60;
const int DATA_SIZE = 192;  //帧长

int main (){
    using namespace std;
    char filename[FILE_SIZE];
    //声明ifstream对象和ofstream对象， 之后便可使用open()方法将对象与特定文件联系起来
    ifstream inFile;
    ofstream outFile;
    cout << "Enter name of data file: ";
    cin.getline(filename, FILE_SIZE);
    inFile.open(filename);
    if(!inFile.is_open()){  //failed to open file
        cout << "Could not open the file " << filename << endl;
        cout << "Program terminating.\n";
        exit(EXIT_FAILURE);
    }

    int value;
    int data[DATA_SIZE];
    int count = 0;

    inFile >> value;
    while (inFile.good()){  //while input good and not at EOF
        ++count;
        data[count-1] = value;
        inFile >> value;
    }
    if(inFile.eof()){
        cout << "End of file reached.\n";
    }
    else if(inFile.fail()){
        cout << "Input terminated by data mismatch.\n";
    }
    else{
        cout << "Input terminated for unknown reason.\n";
    }
    if(count == 0){
        cout << "No data processed.\n";
    }
    else{
        cout << "Size of data: " << count << endl;
        outFile.open("data_out.txt");
        for(int i=0; i<count; i++){
            // cout << data[i];
            outFile << data[i];     //写数据到txt文件中
        }
        // cout << endl;
        outFile << "\nDone. The size of data is: " << count << endl;
    }
    //关闭文件
    outFile.close();
    inFile.close();
    return 0;
}