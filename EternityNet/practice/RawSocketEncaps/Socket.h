#ifndef Socket_class
#define Socket_class

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>

const int MAXHOSTNAME = 200;
const int MAXCONNECTIONS = 5;
const int MAXRECV = 500;

class Socket
{
public:
	Socket();
	virtual ~Socket();

	// Server init
	bool create();
	bool bind(const int _port );
	bool listen() const;
	bool accept( Socket& ) const;

	// Client init
	bool connect (const std::string _host, const int _port );

	// 
	bool send(const std::string ) const;
	int recv( std::string& ) const;


	void setNonBlocking( const bool);
	bool isValid() const { return m_sock != -1; }

private:
	int m_sock;
	sockaddr_in m_addr;

};

#endif
