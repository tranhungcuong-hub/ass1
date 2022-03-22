#include <iostream>
#include "StackFrame.h"
#include "errors.h"
using namespace std;

/*
Run the testcase written in `filename`
@param filename name of the file
*/
void test(string filename) {
    StackFrame *sf = new StackFrame();
    try {
        sf->run(filename);
    }
    catch (exception& e) {
        cout << e.what();
    }
    delete sf;
}

/*
Main function
*/
int main(int argc, char **argv) {
    if (argc < 2){
        cout << "One arg";
        return 1;
    }
    cout << "Two args";
    test(argv[1]);
    return 0;
}