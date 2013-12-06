#ifndef _ETERNITY_CONNECTION_H_
#define _ETERNITY_CONNECTION_H_
/*****************************************************************************\
	This file is part of EternityNet
	@file
	@module
	@author		Yangwl
	@date		2013-8-12
	@email      39441733@qq.com  & ywlfield@gmail.com
	@brief      ����ֻ�������Ӻ�Ĺ���, ��д����. Accept������/MsgCallBack��Ϣ���� ����Server�ദ��
	@change
\*****************************************************************************/
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/scoped_ptr.hpp>

#include <sys/uio.h>
#include <string>

#include "../utilities/NonCopyable.h"
#include "IpAddress.h"
#include "Socket.h"
// #include "Buffer.h"

using namespace ety;

// namespace Eternity
namespace ety    // ��ƴ
{
class Event;
class Dispatcher;
class Connection;

typedef boost::shared_ptr<Connection> ConnectionPtr;
typedef boost::function<void(std::string&, ConnectionPtr)> MessageCallback;

enum ConnStatus
{
	ST_UNINIT = 0,
	ST_INITED,
	ST_ESTABLISHED,
	ST_CLOSED,
	ST_UNKNOWN
};

class Connection:public boost::enable_shared_from_this<Connection>, NonCopyable
{
public:
	Connection(const IpAddress& remote, const IpAddress& local, int fd);
    ~Connection();

	void SetConnState(ConnStatus s)
	{
		mConnState = s;
	}

	void SetDispatcher(Dispatcher* master)
	{
		 mDispatcher = master;
	}

	std::string GetConnName()
	{
		return mName;
	}

	void SetConnName(std::string name)
	{
		mName = name;
	}
	
	void BindMsgCallback(MessageCallback cb);

	void Ready();

	void SendMsg(std::string& msg);

	void SendStreamMsg(void *buf, size_t size);

	void ReadEvent();

	void WriteEvent();

	void CloseEvent();

	void ErrorEvent();

private:
	std::string      mName;

	ConnStatus       mConnState;
	IpAddress        mAddrRemote;
	IpAddress        mAddrLocal;
	Socket           mSock;

	Event*           mEventHander;
	Dispatcher*      mDispatcher;

	string           mMsgBuffer;
};

}
#endif
