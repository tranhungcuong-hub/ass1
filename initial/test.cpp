#include<iostream>
#include<string>

using namespace std;

void Split_string(string *array, int n, string cmd){
    size_t space = cmd.find(" ");
    array[0] = cmd.substr(0, space);
    array[1] = cmd.substr(space + 1, cmd.length());
}

int main(){
    string a = "isum 3";
    int max_size = 2;
    string arr[max_size];
    Split_string(arr, max_size, a);
    cout << arr[0] << "\n" << arr[1] << endl;
    return 0;
}