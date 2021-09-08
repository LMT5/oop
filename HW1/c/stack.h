#ifndef __STACK_H__ 
#define __STACK_H__ 
 
#define STACK_SIZE 100 

struct node{
	int data;
	struct node *next;
};

typedef struct node node_t;

struct stack{ 
	int data; 
	struct node *next;
};
typedef struct stack stack; 
 
extern void push(struct stack* this, int x); 
extern int pop(struct stack* this); 
extern struct stack* new_stack(); 
extern void delete_stack(struct stack* stk); 
 
#endif 

