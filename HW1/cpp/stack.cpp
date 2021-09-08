#include "stack.h" 
#include<iostream>

StackNode::StackNode()
{
	data = 0;
	next = 0;
}

StackNode::StackNode(int x)
{
	data = x;
	next = 0;
}

Stack::Stack() 
{ 
	size = 0;
	bottom = 0;
} 

void Stack::push(int x) 
{ 
	StackNode *newnode = new StackNode(x);
	if(size == 0)
	{
		bottom = newnode;
	}
	else
	{
		StackNode *current;
		current = bottom;
		while(current->next != 0)
		{
		current = current->next;
		}
		current->next = newnode;
	}
	size++;
} 
 
int Stack::pop() 
{ 
	StackNode *temp;
	StackNode *current;
	int data;
	if(size == 0)
	data = -1;
	else
	{
		if(bottom->next == 0)
		{
		data = bottom->data;
		temp = bottom;
		bottom = 0;
		}
		else
		{
		current = bottom;
			while(current->next->next != 0)
			{
			current = current->next;
			}
		data = current->next->data;
		temp = current->next;
		current->next = 0;
		}
	delete temp;
	temp = 0;
	size--;
	}
	return data;
} 
 
Stack::~Stack() 
{ 
	if(size != 0)
	{
		while(size != 0)
		{
		std::cout<<size<<" \n";
		this->pop();
		}
	}
	delete bottom;
} 


