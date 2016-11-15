//2016/11/15
//Dvnean
//Version: 1.0

#include <iostream>
#include <fstream>
#include <cstdlib>

const int FILE_SIZE = 60;
const int DATA_SIZE = 192;

int main (){
    using namespace std;
    char filename[FILE_SIZE];
    ifstream inFile;
    cout << "Enter name of data file: ";
    cin.getline(filename, FILE_SIZE);
    inFile.open(filename);
    if(!inFile.is_open()){
        cout << "Could not open the file " << filename << endl;
        cout << "Program terminating.\n";
        exit(EXIT_FAILURE);
    }

    int value;
    int data[DATA_SIZE];
    int count = 0;

    inFile >> value;
    while (inFile.good()){
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
        for(int i=0; i<count; i++){
            cout << data[i];
        }
        cout << endl;
    }
    inFile.close();
    return 0;
}