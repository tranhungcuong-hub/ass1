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
    if (head){
        if (count != 1){
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
        else{
            Node* temp = head;
            head = tail = nullptr;
            return temp;
        }
    }
    return nullptr;
}

StackFrame::operandStack::Node* StackFrame::operandStack::top(){
    if (tail) return tail;
    return nullptr;
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

void StackFrame::print(){
    if (!pStack->head) cout << "Empty Stack!" << endl;
    else{
    cout << "1. Stack: " << endl;
    operandStack::Node* temp = pStack->head;

    while (temp != pStack->tail){
        cout << "value: " << temp->value << "   code: " << temp->code;
        cout << endl;
        temp = temp->next;
    }
    cout << "value: " << temp->value << "   code: " << temp->code << endl;
    }

    if (!pSpace->count) cout << "Empty Array!" << endl;
    else{
    cout << "2. Array: " << endl;
    for (int i = 0; i < pSpace->count; i+=2){
        cout << "code: " << pSpace->pArray[i] << "   value: " << pSpace->pArray[i+1];
        cout << endl;
    }
    }
}


////
StackFrame::localVarSpace::localVarSpace(){
    count = 0;
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

        cout << arr[0] << " is loading..." << endl;
        // Load and Store Instructions
        if (arr[0] == "pop"){
            pStack->pop();
        }
        if (arr[0] == "top"){

        }
        if (arr[0] == "iadd"){              //1

            operandStack::Node* t1 = pStack->pop();
            operandStack::Node* t2 = pStack->pop();

            if (t1->code != "0" || t2->code != "0"){
                pStack->push(t2->value, t2->code);
                pStack->push(t1->value, t1->code);

                throw TypeMisMatch(cur_line);
            }            
            else{
                int val = stoi(t1->value) + stoi(t2->value);
                string value = to_string(val);

                pStack->push(value, "0");
            }
        }
        else if (arr[0] == "fadd"){         //2
            operandStack::Node* t1 = pStack->pop();
            operandStack::Node* t2 = pStack->pop();
            if (t1->code != "1" && t2->code != "1"){
                pStack->push(t2->value, t2->code);
                pStack->push(t1->value, t1->code);

                throw TypeMisMatch(cur_line);
            }            
            else{
                float val = atof(t1->value.c_str()) + atof(t2->value.c_str());
                string value = to_string(val);

                pStack->push(value, "0");
            }
        }
        else if(arr[0] == "idiv"){          //7
            operandStack::Node* t1 = pStack->pop();
            operandStack::Node* t2 = pStack->pop();
            if(t1->code != "0" && t2->code != "0"){
                pStack->push(t2->value, t2->code);
                pStack->push(t1->value, t1->code);
                delete t1, t2;
                throw TypeMisMatch(cur_line);
            }
            else if(t1->value == "0"){
                throw DivideByZero(cur_line);
            }
            else{
                int a = stoi(t2->value) / stoi(t1->value);
                
            }
        }

        else if(arr[0] == "iconst"){        //23
            pStack->push(arr[1], "0");
        }
        else if(arr[0] == "print"){         //check
            print();
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
            
            operandStack::Node* temp = pStack->pop();

            if (temp->code != "0"){
                cout << "Error" << endl;
                pStack->push(temp->value, temp->code);
                throw TypeMisMatch(cur_line);                
            }
            else{
                pSpace->pArray[ind] = temp->code;
                pSpace->pArray[ind + 1] = temp->value;
                pSpace->count += 2;
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
                pSpace->count += 2;
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