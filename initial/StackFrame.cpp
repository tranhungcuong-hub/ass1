#include "StackFrame.h"
#include <iostream>
#include <fstream>
#include "errors.h"
#include "constants.h"
using namespace std;

//define stackFrame constructor
StackFrame::StackFrame(){
    pStack = new operandStack();
    pSpace = new localVarSpace();

    opStackMaxSize = OPERAND_STACK_MAX_SIZE;
    localVarArrSize = LOCAL_VARIABLE_ARRAY_SIZE;
}

//// define class oprerandStack
StackFrame::operandStack::operandStack(){
    head = nullptr;
    tail = nullptr;
    count = 0;
}
                        
////// define class Node
////// constructor 
StackFrame::operandStack::Node::Node(){
    this->value = "";
    this->code = "";
    this->next = NULL;
}

StackFrame::operandStack::Node::Node(string name, string code){
    this->value = value;
    this->code = code;
    this->next = NULL;
}

//////define operandStack functions
void StackFrame::operandStack::push(string val, string code){
    
}

void Split_string(string *array, int n, string cmd){
    size_t space = cmd.find(" ");
    array[0] = cmd.substr(0, space);
    array[1] = cmd.substr(space + 1, cmd.length());
}

void StackFrame::run(string filename) {
    StackFrame c_stack;

    ifstream fptr;
    fptr.open(filename);
    while(fptr.good()){
        cout << filename << endl;
        string line = "";
        getline(fptr, line);
        
        // Split command and value
        const int max_size = 2;
        string arr[max_size];
        Split_string(arr, max_size, line);

        if(arr[0] == "iconst"){
            cout << arr[1] << endl;
            c_stack.push(arr[1], "0");
        }
        else if(arr[0] == "fconst"){
            c_stack.push(arr[1], "1");
        }
        else if(arr[0] == "iload"){                     // check later
            int idx = stoi(arr[1]);
            c_stack.push(to_string(c_stack.local_array[idx + 1]), to_string(c_stack.local_array[idx]));
        }
        else if(arr[0] == "fload"){                     // check later
            int idx = stoi(arr[1]);

        }
        else if(arr[0] == "istore"){
            
        }
        else if(arr[0] == "fstore"){

        }
    }
}