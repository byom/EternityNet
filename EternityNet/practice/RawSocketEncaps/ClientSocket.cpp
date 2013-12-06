#include"ClientSocket.h"

ClientSocket::ClientSocket(std::string _host, int _port)
{
	if(!Socket::create() )
	{
		throw SocketException("Could not create client socket.");
	}

	if(!Socket::connect(_host, _port) )
	{
		throw SocketException("Could not connect to server.");
	}
}

const ClientSocket& ClientSocket::operator << (const std::string& _str ) const
{
	if( !Socket::send( _str ) )
	{
		throw SocketException("Could not write to socket.");
	}

	return *this;
}

const ClientSocket& ClientSocket::operator >> (std::string& _str) const
{
	if( !Socket::recv( _str ) )
	{
		throw SocketException( "Could not read from socket.");
	}

	return *this;
}
