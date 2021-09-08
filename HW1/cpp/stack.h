#ifndef __STACK_H__ 
#define __STACK_H__ 

class Stack;

class StackNode{
	private:
		int data;
		StackNode *next;
	public:
		StackNode();
		StackNode(int x);
	friend class Stack;
};

class Stack{ 
	private:
		StackNode *bottom;
		int size;
	public: 
		Stack();
		void push(int x); 
		int pop(); 
		~Stack(); 
}; 
 
#endif 

