#include"ClientSocket.h"
#include"SocketException.h"
#include<string>
#include<iostream>

int main( int argc, int argv[] )
{
	try
	{
		
		ClientSocket client("localhost", 30000);
		std::string reply;
		
		try
		{
			client << "test message hello EternityNet. ";
			client >> reply;
		}catch( SocketException& ){}

		std::cout << "We received the response:\n\"" << reply << "\"\n";
	}
	catch ( SocketException& e)
	{
		std::cout << "Exception was caught:"<< e.description() << "\n";
	}
	
	return 0;
}
