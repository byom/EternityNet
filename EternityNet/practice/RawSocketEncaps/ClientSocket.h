#ifndef CLientSocket_class
#define CLientSocket_class

#include"Socket.h"
#include"SocketException.h"

class ClientSocket : private Socket
{
public:
	ClientSocket( std::string _host, int _port);
	virtual ~ClientSocket(){};

	const ClientSocket& operator << (const std::string& ) const;
	const ClientSocket& operator >> ( std::string& ) const;
	
};


#endif
