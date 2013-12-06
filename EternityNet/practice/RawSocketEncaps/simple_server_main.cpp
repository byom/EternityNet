#include"ServerSocket.h"
#include"SocketException.h"
#include <string>
#include <iostream>

int main(int argc, int argv[] )
{
	std::cout<< "running...\n";

	try{
		// Create the Socket
		ServerSocket server( 30000 );

		while (true)
		{
			ServerSocket newSock;
			server.accept( newSock );
			
			std::string data;
			try{
				while (true)
				{
					newSock >> data;
					newSock << data;

					std::cout<<"We get the msg form client: \""<< data <<"\"\n";
				}
			}catch (SocketException& ){	}
		}
	}
	catch( SocketException& e)
	{
		std::cout<< "Exception was caught:"<< e.description() << "\nExition.\n";
	}

}
