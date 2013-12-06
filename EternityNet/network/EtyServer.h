#ifndef _ETERNITY_ETYSERVER_H_
#define _ETERNITY_ETYSERVER_H_
/*****************************************************************************\
	This file is part of EternityNet
	@file
	@module
	@author		Yangwl
	@date		2013-8-12
	@email      39441733@qq.com  & ywlfield@gmail.com
	@brief      
				EF_TEMP_fix 吧OnMsg提取到EchoServer文件中, 本文件只包含公用成分.
	@change
\*****************************************************************************/
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <sys/epoll.h>

#include <string>
#include <map>
#include "../utilities/NonCopyable.h"
#include "../utilities/LogUtil.h"
#include "Acceptor.h"



using namespace ety;
using namespace std;

// namespace Eternity
namespace ety    // 好拼
{
class Event;
class Acceptor;
class Connection;
class Dispatcher;

typedef boost::shared_ptr<Connection>        ConnectionPtr;
typedef std::map<std::string, ConnectionPtr> ConnectionMap;

class IpAddress;
class Acceptor;
class Event;
class Dispatcher;
class Connection;
class EtyServer: public NonCopyable
{
public:

	EtyServer(const std::string& name, const std::string& port);
	EtyServer(const std::string& name, const short port);
	~EtyServer();

	void StartService();

	void Listen();

	bool IsListening()
	{
		return mIsListening;
	}

	void AcceptConnection();

	void CloseAConnection(ConnectionPtr connPtr);

	void Broadcast(string& msg);

	void OnMsg(std::string&, ConnectionPtr);

	void Quit(){ mQuit = true;  }
	void Exit(){ mQuit = true;  }

private:
	std::string	  mServerName;
	short         mServerPort;
	bool          mIsListening;
	bool          mQuit;

	Acceptor*     mAcceptor;
	Event*        mEventMaster;
	Dispatcher*   mDispatcher;
	ConnectionMap mConnMap;
	int           mConnID;
};
/////// code /////
}
#endif
