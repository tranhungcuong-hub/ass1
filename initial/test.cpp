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
    int a = 11/3;
    cout << a;
    return 0;
}