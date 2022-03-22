#include "StackFrame.h"
#include <iostream>
#include <fstream>
#include "errors.h"
#include "constants.h"
using namespace std;


StackFrame::StackFrame() : opStackMaxSize(OPERAND_STACK_MAX_SIZE), localVarArrSize(LOCAL_VARIABLE_ARRAY_SIZE), 
                            head(NULL), tail(NULL), count(0), local_array(new int[localVarArrSize])  {}

void StackFrame::push(string val, string code){
    this->count++;
    if(head == nullptr){
        Node* temp = new Node(val, code);
        head = temp;
        tail = temp;
    }
    else{
        Node* newNode = new Node(val, code);
        tail->next = newNode;
        tail = newNode;
    }
}

StackFrame::Node* StackFrame::pop(){
    Node* newNode;
    if(this->head == nullptr){
        return 0;    
    }
    else{
        Node* temp = head;
        while(temp != tail){
            temp = temp->next;
        }
        tail = temp;
        temp = temp->next;
        newNode = temp;
        tail->next = nullptr;
        delete temp;
    }
    return newNode;
}

StackFrame::Node* StackFrame::top(){
    return this->tail;
}

bool StackFrame::empty(){
    if(this->count == 0)
        return true;
    return false;
}

int StackFrame::size(){
    return this->count;
}

void StackFrame::clear(){
    while(head != nullptr){
        this->pop();
    }
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
        string line = "";
        getline(fptr, line);
        
        // Split command and value
        int max_size = 2;
        string arr[max_size];
        Split_string(arr, max_size, line);

        if(arr[0] == "iconst"){
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