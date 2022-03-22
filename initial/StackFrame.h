#ifndef __STACK_FRAME_H__
#define __STACK_FRAME_H__

#include <string>

using namespace std;
/*
StackFrame declaration
*/
class StackFrame {
    //Operand stack
    class operandStack{
        class Node{
            string value;
            string code;
            Node* next;
            friend class operandStack;
        public:
            Node(){};
            Node(string value, string code){};
        };
        friend class StackFrame;
        Node* head;
        Node* tail;
        int count;
    public:
        operandStack(){} ;
        void push(string val, string code) ;
        Node* pop() ;
        Node* top() ;
        bool empty() ;
        int size() ;
        void clear() ;
    };

    //Local variable space
    class localVarSpace{
        int* localVarArray;

        public:
        localVarSpace(){} ;
    };

    operandStack* pStack; // pointer to oprandStack
    localVarSpace* pSpace; // pointer to localVarSpace

    int opStackMaxSize; // max size of operand stack
    int localVarArrSize; // size of local variable array

    public:
    /*
    Constructor of StackFrame
    */
    StackFrame(){};
    
    /*
    Run the method written in the testcase
    @param filename name of the file
    */
    void run(std::string filename);
};



#endif // !__STACK_FRAME_H__
