#ifndef _ETERNITY_IPADDRESS_H_
#define _ETERNITY_IPADDRESS_H_
/*****************************************************************************\
	This file is part of EternityNet
	@file
	@module
	@author		Yangwl
	@date		2013-8-12
	@email      39441733@qq.com  & ywlfield@gmail.com
	@brief              
	@change
\*****************************************************************************/

#include <endian.h>
#include <stdint.h>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <errno.h>

#define INVALID_PORT -1 

namespace ety
{

class IpAddress
{
public:
	IpAddress(){}
	~IpAddress(){}

	IpAddress(const std::string& ip, uint16_t port);
	IpAddress(const std::string& port);
	IpAddress(short port);
	IpAddress(const struct sockaddr_in& address):mSockAddr(address),mValid(true){}


	IpAddress  & operator=(const IpAddress &other);
	IpAddress  & operator=(const struct sockaddr_in addr);

	bool       operator==(const IpAddress &other) const;
	bool       operator==(const struct sockaddr_in addr) const;

	const char* AddrToStr(char *buf, size_t size);

	static void AddrToStr(const struct sockaddr_in& addr, char* buf, size_t size);

	bool IsValid(){ return mValid; }

	void SetSocdAddr(const struct sockaddr_in& addr)
	{
		mSockAddr = addr;
	}

	struct sockaddr_in& GetSockAddr() 
	{
		return mSockAddr;
	}

private:
	struct sockaddr_in mSockAddr;
	bool               mValid;
};

}

#endif
