#include <stdlib.h>
#include <stdio.h> 
#include "stack.h" 
void push(struct stack* this, int x)
{
	node_t* newnode;
	node_t* current;
	newnode = (node_t*) malloc(sizeof(node_t));
	newnode->data = x;
	newnode->next = NULL;
	if(this->next == NULL)
	{
		this->next = newnode;
	}
	else
	{
		current = this->next;
		while(current->next != NULL)
		{
			current = current->next;
		}
		current->next = newnode;
	}
} 
int pop(struct stack* this)
{
	node_t* current;
	node_t* temp;
	current = this->next;
	int Data;
	if(this->next == NULL)
	{
		Data = -1;
	}
	else if(this->next->next ==NULL)
	{
		temp = this->next;
		Data = this->next->data;
		this->next = NULL;
		free(temp);
	}
	else
	{
		while(current->next->next != NULL)
		{
			current=current->next;
		}
		Data = current->next->data;
		temp = current->next;
		current->next = NULL;
		free(temp);
	}
	return Data;
}
struct stack* new_stack()
{
	stack* new;
	node_t* newnode;
	new = (stack*) malloc(sizeof(stack));
	newnode = NULL;
	new->next = newnode;
	return new;
}
void delete_stack(struct stack* stk)
{
	if(stk->next != NULL)
	{
		while(stk->next != NULL)
		{
		pop(stk);
		}
	}
	free(stk);
}
