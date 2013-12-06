#include "ServerSocket.h"
#include "SocketException.h"

ServerSocket::ServerSocket(int _port)
{
	if ( !Socket::create() )
	{
		throw SocketException("Could not create server socket.");
	}

	if( !Socket::bind(_port) )
	{
		throw SocketException("Could not bind to port.");
	}

	if( !Socket::listen() )
	{
		throw SocketException("Could not listen to socket.");
	}
}

ServerSocket::~ServerSocket()
{
}

const ServerSocket& ServerSocket::operator << (const std::string& _str) const
{
	if( !Socket::send( _str ) )
	{
		throw SocketException("Could not write to socket.");
	}

	return *this;
}

const ServerSocket& ServerSocket::operator >> ( std::string& _str) const
{
	if( !Socket::recv( _str) )
	{
		throw SocketException("Could not read from socket.");
	}

	return *this;
}

void ServerSocket::accept( ServerSocket& _sock)
{
	if( !Socket::accept( _sock ) )
	{
		throw SocketException("Could not accept socket.");
	}
}
