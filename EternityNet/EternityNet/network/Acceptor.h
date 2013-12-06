#ifndef _ETERNITY_ACCEPTOR_H_
#define _ETERNITY_ACCEPTOR_H_
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
#include <boost/shared_ptr.hpp>
#include <sys/socket.h>
#include "../utilities/NonCopyable.h"
#include "Socket.h"
#include "IpAddress.h"

using namespace ety;

// namespace Eternity
namespace ety
{

class Connection;
typedef boost::shared_ptr<Connection> ConnectionPtr;

class Acceptor: public NonCopyable
{
public:
	Acceptor(int port);

	Acceptor();

	~Acceptor();

	void Listen();

	ConnectionPtr Accept();

	//void SetConnectFD(int connfd)
	//{
	//	  mSockConnect.SetSocket(connfd);
	//}

	int GetConnectFd()
	{
		return mSockConnect.GetSocketfd();
	}

	int GetListenFd()
	{
		return mSockListen.GetSocketfd();

	}


private:
	Socket     mSockListen;
	Socket     mSockConnect;
	IpAddress  mAddr;
	bool       mIsEstablish;

};

}
#endif
