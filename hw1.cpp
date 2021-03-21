//12403 : Save Shetu
//2021/2/27
//B073040005§õ»Ê®x 
#include<iostream>
using namespace std;
int main()
{
	int i,sum=0,T,n;
	string input;
	cin>>T;
	for(int i=0;i<T;i++)
	{
		cin>>input;
		if(input == "donate")
		{
		cin>>n;
		sum+=n;	
		}
		else if(input == "report")
		cout<<sum<<endl;
	}
	
}
