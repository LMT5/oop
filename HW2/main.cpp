#include<iostream>
#include"tar.h"
#include<vector>
#include<string>
using namespace std;
int main(int argc,char *argv[])
{
	TarFile tarfile(argv[1]);
	if(tarfile.IsValidTarFile())
	{
		tarfile.list();
	}
}
