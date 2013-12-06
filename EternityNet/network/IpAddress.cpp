#include "IpAddress.h"
#include <stdlib.h>
#include <string.h>
#include "../utilities/LogUtil.h"

using namespace ety;

// const short INVALID_PORT = -1;

IpAddress::IpAddress(const std::string& ip, uint16_t port)
{
	memset(&mSockAddr, 0, sizeof(mSockAddr));
	if(port > INVALID_PORT)
	{
		mSockAddr.sin_family = AF_INET;   
		mSockAddr.sin_port = htobe16(port);

		if(::inet_pton(AF_INET, ip.c_str(), &mSockAddr.sin_addr) == -1)
		{
			fprintf(stderr,"ERR:inet_pton\n");
			mValid = false;  
		}
		else
			mValid = true;
	}
	else
		mValid = false;    
}

IpAddress::IpAddress(const std::string& port)
{
	short tPort = atoi(port.c_str());
	//bzero(&mSockAddr, sizeof(mSockAddr));
	memset(&mSockAddr, 0, sizeof(mSockAddr));

	if(tPort > INVALID_PORT)
	{
		mSockAddr.sin_family = AF_INET;
		mSockAddr.sin_addr.s_addr = htobe32(INADDR_ANY);
		mSockAddr.sin_port = htons(tPort);
		WriteLog("Sin_port:%d", htons(tPort) );
		mValid = true;
	}
	else
		mValid = false;
}

IpAddress::IpAddress(short  port)
{
	//bzero(&mSockAddr, sizeof(mSockAddr));
	memset(&mSockAddr, 0, sizeof(mSockAddr));

	if(port > INVALID_PORT)
	{
		mSockAddr.sin_family = AF_INET;
		mSockAddr.sin_addr.s_addr = htobe32(INADDR_ANY);
		mSockAddr.sin_port = htons(port);
		mValid = true;
	}
	else
		mValid = false;
}

IpAddress& IpAddress::operator=(const IpAddress &other)
{
	mSockAddr = other.mSockAddr;
	mValid = true;

	return *this;
}

IpAddress& IpAddress::operator=(const struct sockaddr_in addr)
{
	mSockAddr = addr;
	mValid = true;

	return *this;
}


bool IpAddress::operator==(const IpAddress &other) const
{
	return ( mSockAddr.sin_family == other.mSockAddr.sin_family &&
		 mSockAddr.sin_addr.s_addr == other.mSockAddr.sin_addr.s_addr && 
		 mSockAddr.sin_port == other.mSockAddr.sin_port );
}

bool IpAddress::operator==(const struct sockaddr_in addr) const
{
	return ( mSockAddr.sin_family == addr.sin_family &&
		 mSockAddr.sin_addr.s_addr == addr.sin_addr.s_addr && 
		 mSockAddr.sin_port == addr.sin_port );
}

void IpAddress::AddrToStr(const struct sockaddr_in& addr, char* buf, size_t size)
{
	char host[INET_ADDRSTRLEN] = "INVALID";
	::inet_ntop(AF_INET, &addr.sin_addr, host,sizeof(host));
	uint16_t port = be16toh(addr.sin_port);
	snprintf(buf, size,"%s:%u",host,port);
}

const char* IpAddress::AddrToStr(char *buf, size_t size)
{
	char host[INET_ADDRSTRLEN] = "INVALID";
	::inet_ntop(AF_INET, &mSockAddr.sin_addr, host,sizeof(host));
	uint16_t port = be16toh(mSockAddr.sin_port);
	snprintf(buf, size,"%s:%u",host,port);
	return buf;
}
