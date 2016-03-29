// strquote.cpp -- different designs
#include <iostream>
#include <string>
using namespace std;

string version1(const string & s1, const string & s2);
const string & version2(string & s1, const string & s2); // has side effect
const string & version3(string & s1, const string & s2); // bad design

int main(){
    string input;
    string copy;
    string result;
    
    cout << "Enter a string: ";
    getline(cin, input);
    copy = input;
    cout << "Your string as entered: " << input << endl;

    result = version1(input, "***");
    cout << "Your string enhanced: " << result << endl;
    cout << "Your original string: " << input << endl;

    result = version2(input, "###");
    cout << "Your string enhanced: " << result << endl;
    cout << "Your original string: " << input << endl;
    
    cout << "Resetting original string.\n";
    input = copy;
    result = version3(input, "@@@");    
    cout << "Your string enhanced: " << result << endl;
    cout << "Your original string: " << input << endl;
    
    return 0;
}

const string & version3(string & s1, const string & s2){ //指出该函数什么不能做
    string temp;
    temp = s2 + s1 + s2;
    return temp;    //不能通过编译
}
const string & version2(string & s1, const string & s2){
 
    s1 = s2 + s1 + s2;      
    return s1;   
}
string version1(const string & s1, const string & s2){
    
    string temp;
    temp = s2 + s1 + s2;
    return temp;
}