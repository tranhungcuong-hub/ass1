#ifndef __STACK_FRAME_H__
#define __STACK_FRAME_H__

#include <string>

/*
StackFrame declaration
*/
class StackFrame {
    class Node{
        string value;
        string code;
        Node* next;
        friend class StackFrame;
    public:
        Node(){
            this->value = "";
            this->code = "";
            this->next = NULL;
        }
        Node(string value, string code){
            this->value = value;
            this->code = code;
            this->next = NULL;
        }
    };
protected:
    Node* head;
    Node* tail;
    int count;
    int opStackMaxSize; // max size of operand stack
    int localVarArrSize; // size of local variable array
    int *local_array;
public:
    /*
    Constructor of StackFrame
    */
    StackFrame();
    void push(string val, string code) ;
    Node* pop() ;
    Node* top() ;
    bool empty() ;
    int size() ;
    void clear() ;
    /*
    Run the method written in the testcase
    @param filename name of the file
    */
    void run(std::string filename);
};



#endif // !__STACK_FRAME_H__
