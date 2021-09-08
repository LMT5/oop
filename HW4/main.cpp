#include<iostream>
#include"lexer.h"
using namespace std;
int main()
{
	Lexer lexer;
	try
	{
		while(1)
		{
			const Token* t = lexer.scan();
			cout<<"Token: "<<t->toString() << endl;
		}
	}
	catch(const char *str)
	{
		cout<<str<<endl;
	}
	return 0;
}
