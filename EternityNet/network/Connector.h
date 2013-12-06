#ifndef _ETERNITY_CONNECTOR_H_
#define _ETERNITY_CONNECTOR_H_
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
#include <boost/scoped_ptr.hpp>
#include"Connection.h"
#include"Socket.h"
#include"IpAddress.h"

using namespace ety;

// namespace Eternity
namespace ety
{
class Connector
{
public:
	Connector(const std::string& ip, short port):mServAddr(ip, port)
	{

	}
	~Connector(){}

	typedef boost::shared_ptr<Connection> ConnectionPtr;
	const ConnectionPtr& Connect()
	{
		mSock.Init();
		mSock.Connect(mServAddr);
		ConnectionPtr conn = new Connection(mServAddr, mSock.GetLocalAddress(), mSock.GetSocketfd() );
		WriteLog("Connection Establish-FD:%d ", mSock.GetLocalAddress(), mSock.GetSocketfd() );	
	
		return conn;
	}

	void Shutdonw(){ ::shutdown(mSock.GetSocketfd()); }
	void Close(){ ::close(mSock.GetSocketfd()); }

private:
	IpAddress     mServAddr;
	Socket        mSock;
	ConnectionPtr mConnection;
};

}
#endif