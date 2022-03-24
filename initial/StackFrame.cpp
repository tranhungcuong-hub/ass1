#include "StackFrame.h"
#include <iostream>
#include <fstream>
#include "errors.h"
#include "constants.h"
using namespace std;

//define stackFrame constructor

StackFrame::StackFrame(){
    opStackMaxSize = OPERAND_STACK_MAX_SIZE;
    localVarArrSize = LOCAL_VARIABLE_ARRAY_SIZE;

    pStack = new operandStack();
    pSpace = new localVarSpace();
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

StackFrame::operandStack::Node::Node(string value, string code){
    this->value = value;
    this->code = code;
    this->next = NULL;
}

//////define operandStack functions
void StackFrame::operandStack::push(string val, string code){
    if (!head){
        head = tail = new Node(val, code);
    }
    else{
        tail->next = new Node(val, code);
        tail = tail->next;
    }
    count++;
}

StackFrame::operandStack::Node* StackFrame::operandStack::pop(){
    Node* temp = head;
    while (temp->next != tail){
        temp = temp->next;
    }
    tail = temp;
    temp = temp->next;
    tail->next = nullptr;
    count--;
    return temp;
}

StackFrame::operandStack::Node* StackFrame::operandStack::top(){
    return tail;
}

bool StackFrame::operandStack::empty(){
    if (count == 0) return true;
    return false;
}

int StackFrame::operandStack::size(){
    return count;
}

void StackFrame::operandStack::clear(){
    tail = nullptr;
    count = 0;

    while(head){
        Node* temp = head;
        head = head->next;
        temp->next = nullptr;
        delete temp;
    }
}

void StackFrame::operandStack::printArray(){
    Node* temp = head;

    while (temp != tail){
        cout << "value: " << temp->value << "   code: " << temp->code;
        cout << endl;
        temp = temp->next;
    }
    cout << "value: " << temp->value << "   code: " << temp->code << endl;
}


////
StackFrame::localVarSpace::localVarSpace(){
    pArray = new string[LOCAL_VARIABLE_ARRAY_SIZE];
}

void Split_string(string *array, int n, string cmd){
    size_t space = cmd.find(" ");
    array[0] = cmd.substr(0, space);
    array[1] = cmd.substr(space + 1, cmd.length());
}

void StackFrame::run(string filename) {
    ifstream fptr;

    fptr.open(filename);

    int cur_line = 1;
    while(fptr.good()){
        string line = "";
        getline(fptr, line);
        
        // Split command and value
        const int max_size = 2;
        string arr[max_size];
        Split_string(arr, max_size, line);

        // Load and Store Instructions
        if (arr[0] == "iadd"){              //1
            operandStack::Node* t1 = pStack->pop();
            operandStack::Node* t2 = pStack->pop();
            if (t1->code != "0" || t2->code != "0"){
                pStack->push(t2->value, t2->code);
                pStack->push(t2->value, t1->code);

                delete t1, t2;
                throw TypeMisMatch(cur_line);
            }            
            else{
                int val = stoi(t1->value) + stoi(t2->value);
                string value = to_string(val);

                pStack->push(value, "0");
                delete t1, t2;
            }
        }
        else if (arr[0] == "fadd"){         //2
            operandStack::Node* t1 = pStack->pop();
            operandStack::Node* t2 = pStack->pop();
            if (t1->code != "1" && t2->code != "1"){
                pStack->push(t2->value, t2->code);
                pStack->push(t2->value, t1->code);

                delete t1, t2;
                throw TypeMisMatch(cur_line);
            }            
            else{
                float val = atof(t1->value.c_str()) + atof(t2->value.c_str());
                string value = to_string(val);

                pStack->push(value, "0");
                delete t1, t2;
            }
        }
        else if(arr[0] == "iconst"){        //23
            pStack->push(arr[1], "0");
        }
        else if(arr[0] == "printStack"){ //check stack
            pStack->printArray();
        }
        else if(arr[0] == "fconst"){        //24
            pStack->push(arr[1], "1");
        }
        else if (arr[0] == "iload"){        //25
            int ind = stoi(arr[1]);
            if (pSpace->pArray[ind] != "0"){
                throw TypeMisMatch(cur_line);                
            }
            else{
                pStack->push(pSpace->pArray[ind + 1], "0");
            }
        }
        else if (arr[0] == "fload"){        //26
            int ind = stoi(arr[1]);
            if (pSpace->pArray[ind] != "1"){
                throw TypeMisMatch(cur_line);                
            }
            else{
                pStack->push(pSpace->pArray[ind + 1], "1");
            }
        }
        else if (arr[0] == "istore"){       //27
            int ind = stoi(arr[1]);

            operandStack::Node* temp = pStack->top();

            if (temp->code != "0"){
                throw TypeMisMatch(cur_line);                
            }
            else{
                temp = pStack->top();
                pSpace->pArray[ind] = temp->code;
                pSpace->pArray[ind + 1] = temp->value;
            }
        }
        else if (arr[0] == "fstore"){       //28
            int ind = stoi(arr[1]);

            operandStack::Node* temp = pStack->top();

            if (temp->code != "1"){
                throw TypeMisMatch(cur_line);                
            }
            else{
                temp = pStack->top();
                pSpace->pArray[ind] = temp->code;
                pSpace->pArray[ind + 1] = temp->value;
            }
        }
        // else if(arr[0] == "iload"){                     // check later
        //     int idx = stoi(arr[1]);
        //     c_stack.push(to_string(c_stack.local_array[idx + 1]), to_string(c_stack.local_array[idx]));
        // }
        // else if(arr[0] == "fload"){                     // check later
        //     int idx = stoi(arr[1]);

        // }
        // else if(arr[0] == "istore"){
            
        // }
        // else if(arr[0] == "fstore"){

        // }
        cur_line++;
    }
}