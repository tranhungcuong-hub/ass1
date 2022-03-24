#include<iostream>
#include<string>
#include <iomanip>

using namespace std;

void Split_string(string *array, int n, string cmd){
    size_t space = cmd.find(" ");
    array[0] = cmd.substr(0, space);
    array[1] = cmd.substr(space + 1, cmd.length());
}

int main(){
    float b = 5.505;
    string a = to_string(b);
    cout << a << endl;
    a.erase(a.find_last_not_of('0') + 1, string::npos);
    cout << a;
    return 0;
}