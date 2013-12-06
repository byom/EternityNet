#include "Socket.h"
#include "string.h"
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <iostream>

Socket::Socket():
	m_sock(-1)
{
	memset( &m_addr, 0, sizeof(m_addr) );
}

Socket::~Socket()
{
	if (isValid())
	  ::close(m_sock);
}

bool Socket::create()
{
	m_sock = socket( AF_INET, SOCK_STREAM, 0);

	if( !isValid())
		return false;
	
	int opt = 1;
	if (setsockopt( m_sock, SOL_SOCKET, SO_REUSEADDR, ( const char* )&opt, sizeof(opt)) == -1 )
	  return false;

	return true;
}

bool Socket::bind( const int _port)
{
	if (!isValid() )
		return false;

	m_addr.sin_family = AF_INET;
	m_addr.sin_addr.s_addr = INADDR_ANY;
	m_addr.sin_port = htons(_port);

	int ret = ::bind(m_sock, (struct sockaddr*) &m_addr, sizeof(m_addr));

	if( ret == -1 )
	  return false;

	return true;
}

bool Socket::listen() const
{
	if (!isValid())
	  return false;

	int ret = ::listen( m_sock, MAXCONNECTIONS );

	if ( ret == -1 )
	  return false;

	return true;
}

bool Socket::accept( Socket& _newSock ) const
{
	int addrLen = sizeof( m_addr );
	_newSock.m_sock = ::accept( m_sock, (sockaddr*)&m_addr, (socklen_t*)&addrLen);

	if ( _newSock.m_sock <= 0 )
	  return false;
	else
	  return true;
}

bool Socket::send( const std::string _str) const
{
	int status = ::send( m_sock, _str.c_str(), _str.size(), MSG_NOSIGNAL);
	if ( status == -1 )
		return false;
	else
		return true;
}

int Socket::recv( std::string& _str) const
{
	char buf[ MAXRECV + 1 ];
	_str = "";
	memset( buf, 0, MAXRECV + 1 );

	int status = ::recv( m_sock, buf, MAXRECV, 0 );

	if ( status == -1 )
	{
		std::cout << "status == -1 Errno == " << errno << " in Socket::recv\n";
		return 0;
	}
	else if( status == 0 )
	{
		return 0;
	}
	else
	{
		_str = buf;
		return status;
	}
}

bool Socket::connect( const std::string _host, const int _port)
{
	if ( !isValid() ) return false;

	m_addr.sin_family = AF_INET;
	m_addr.sin_port = htons(_port);

	int status = inet_pton(AF_INET, _host.c_str(), &m_addr.sin_addr);

	if ( errno == EAFNOSUPPORT ) return false;

	status = ::connect( m_sock, (sockaddr*)&m_addr, sizeof(m_addr) );

	if(status == 0)
	  return true;
	else
	  return false;
}

void Socket::setNonBlocking( const bool _flag )
{
	int opts;
	
	opts = fcntl( m_sock, F_GETFL );
	if (opts < 0 )
		return;
	if (_flag)
		opts = ( opts | O_NONBLOCK );
	else
		opts = ( opts & ~O_NONBLOCK );

	fcntl( m_sock, F_SETFL, opts);
}
