#include"Socket.h"

#include<netinet/in.h>
#include<netinet/tcp.h>
#include<sys/fcntl.h>

using namespace ety;

Socket::~Socket()
{
	Close();
}

int Socket::Init()
{
	int sock = -1;
	if ( (sock = ::socket(AF_INET, SOCK_STREAM, 0)) == -1 )
	{
		WriteErrLog("Create Socket Error:%s", strerror(errno));
		return -1;
	}

	mSockfd = sock;
	return 0;
}

void Socket::Close()
{
	if ( INVALID_HANDLE == mSockfd )
		return;

	::close( mSockfd );
	return;
}

void Socket::Shutdown(int sd)
{
	// SHUT_RD, SHUT_WR, SHUT_RDWR
	int ret = ::shutdown(mSockfd, sd);
	if ( ret < 0 )
	{
		WriteErrLog("Shutdown Error:%s", strerror(errno));
	}
}

int Socket::Bind(IpAddress& addr)
{
	if (!addr.IsValid())
	{
		WriteErrLog("Invalid Address");
		return -1;
	}

	if ( ::bind(mSockfd, (struct sockaddr*)(&addr.GetSockAddr()), sizeof(addr.GetSockAddr())) == -1 )
	{
		WriteErrLog("Bind address error:%s", strerror(errno));
		return -1;
	}

	return 0;
}

int Socket::Connect(IpAddress& addr)
{
	if ( ::connect( mSockfd, (struct sockaddr*)(&addr.GetSockAddr()), sizeof(addr.GetSockAddr()) ) == -1 )
	{
		WriteErrLog("connect error:%s", strerror(errno) );
		return -1;
	}

	return 0;
}

int Socket::Listen()
{
	if ( ::listen(mSockfd, SOMAXCONN) == -1)
	{
		WriteErrLog("Listen Error:%d", strerror(errno));
		return -1;
	}

	return 0;
}

int Socket::Accept(IpAddress& addr)
{
	int sock = -1;
	socklen_t size = sizeof(struct sockaddr_in); 
	sock = ::accept( mSockfd, (struct sockaddr*)&addr.GetSockAddr(), &size);
	if ( -1 == sock )
	{
		WriteErrLog("Accept Socket Error:%s", strerror(errno));
		return -1;
	}

	return sock;
}

int Socket::GetSocketError(int sockfd)
{
	int ret = -1;
	int err = 0;
	socklen_t len = sizeof(err);
	ret = ::getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &err, &len);
	if (-1 == ret)
	{
		return ret;
	}
	else
	{
		return err;
	}
}

const IpAddress Socket::GetLocalAddress()
{
	;
}

const IpAddress Socket::GetPeerAddress()
{
	;
}

int Socket::SetIntOpt(int opt, bool b)
{
	int val = b;
	int ret = setsockopt(mSockfd, SOL_SOCKET, opt, &val, sizeof(val));
	if ( -1 == ret )
	{
		WriteErrLog("Set IntOpt Error:%s", strerror(errno));
		return ret;
	}

	return  ret;	
}

int Socket::SetReuseAddr(bool b)
{
	int val = b;
	int ret = setsockopt(mSockfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
	if ( -1 == ret )
	{
		WriteErrLog("Set ReuseAddr Error:%s", strerror(errno));
		return ret;
	}

	return  ret;	
}

int Socket::SetTimeOpt(int opt, int ms)
{
	struct timeval tv;
	tv.tv_sec = (int)(ms/1000);
	tv.tv_usec = (ms%1000) * 1000000;

	int ret = ::setsockopt(mSockfd, SOL_SOCKET, opt, &tv, sizeof(tv));
	if (ret == -1)
	{
		WriteErrLog("Set TimeOpt Error:%s", strerror(errno));
		return ret;
	}    
	return ret;
}

int Socket::SetTcpNoDelay(bool b)
{
	int val = b;
	int ret = setsockopt(mSockfd, IPPROTO_TCP, TCP_NODELAY, &val, sizeof(val));
	if ( -1 == ret )
	{
		WriteErrLog("Set TcpNoDelay Error:%s", strerror(errno));
		return ret;
	}

	return  ret;
}

int Socket::SetSoLinger(bool b, int sec)
{
	struct linger lgr;
	lgr.l_onoff = b;
	lgr.l_linger = sec;
	int ret = setsockopt(mSockfd, SOL_SOCKET, SO_LINGER, (const void *)(&lgr), sizeof(lgr));
	if ( -1 == ret )
	{
		WriteErrLog("Set SoLinger Error:%s", strerror(errno));
		return ret;
	}

	return  ret;
}

int Socket::SetNonBlocking(bool b)
{
	int ret = -1;
	int flags = ::fcntl(mSockfd, F_GETFL, 0);
	if (flags >= 0)
	{
		if(b)
		{
			flags |= O_NONBLOCK;
		}
		else
		{
			flags &= ~O_NONBLOCK; 
		}

		if (fcntl(mSockfd, F_SETFL, flags) >= 0)
		{
			ret = 0;
		}
	}

	return ret;	
}