#include"IpAddress.h"
#include<stdio.h>
#include<iostream>

using namespace ety;
using namespace std;

int main()
{
	std::string str("127.0.0.1");
	//short port = 8080; 
	IpAddress addr("1010");

	IpAddress temp;
	temp = addr;

	int bufsize = 1024;
	char buf[bufsize];
	temp.AddrToStr(buf, bufsize);
	if( addr == temp )
	  cout<< " == is Valid"<<endl;

	std::cout<< buf <<std::endl;

	return 0;
}
