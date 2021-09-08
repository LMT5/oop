#include<iostream>
#include<typeinfo>
#include<ctime>
#include<cmath>
#include<map>
#include<clocale>
using namespace std;
int main()
{
	char c;
	int count = 0;
	while(1)
	{
		count++;
		c = cin.get();
		if(c == -1 || count >1000)
			break;
		cout<<c<<endl;
	}
	/*map<string, string> hashtable;
	hashtable["hello"] = "hi";
	cout<<hashtable["hello"]<<endl;*/
	/*int a = '1';
	char c = 'a';
	cout<<isdigit(a)<<endl;
	cout<<isdigit(c)<<endl;*/
	return 0;
}
