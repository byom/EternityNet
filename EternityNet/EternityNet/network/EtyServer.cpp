#include "EtyServer.h"
#include "Dispatcher.h"
#include "Connection.h"

// EF_TEMP_fix
#define SafeRelease(x) if(x) { delete (x); }

using namespace ety;

EtyServer::EtyServer(const std::string& name, const std::string& port):
 mConnID(0),
 mServerName(name)
{
	mServerPort  = atoi(port.c_str());
	mAcceptor    = new Acceptor(mServerPort);
	mDispatcher  = new Dispatcher();
}

EtyServer::EtyServer(const std::string& name, const short port):
 mConnID(0),
 mServerName(name),
 mServerPort(port)
{
	mAcceptor    = new Acceptor(port);
	mDispatcher  = new Dispatcher();
}

EtyServer::~EtyServer()
{
	for(ConnectionMap::iterator it(mConnMap.begin());
		it != mConnMap.end(); ++it)
	{
		ConnectionPtr conn = it->second;
		conn->CloseEvent();
	}

	SafeRelease( mAcceptor );
	SafeRelease( mEventMaster );
	SafeRelease( mDispatcher );
}

void EtyServer::Listen()
{
	mAcceptor->Listen();

	mEventMaster = new Event(mAcceptor->GetListenFd(), 0);
	
	mEventMaster->SetEvent(ACCEPT_EVENT);
	mEventMaster->SetEventCallback(ACCEPT_EVENT, boost::bind(&EtyServer::AcceptConnection,this));
	mDispatcher->RegisterEvent(*mEventMaster);

	mIsListening = true;
	WriteLog("EtyServer Started......");
}

void EtyServer::AcceptConnection()
{
	if( true != mIsListening )
	{
		WriteErrLog("EtyServer not in listening!!!");
		return;
	}

	WriteLog("Accept New Connection");
	
	ConnectionPtr connPtr = mAcceptor->Accept();
	if ( NULL == connPtr)
	{
		WriteErrLog("Something Error,Maybe:%s.", strerror(errno));
		return;
	}
	
	++mConnID;
	char buf[32];
	snprintf(buf, sizeof(buf), "%d#%d", mServerPort, mConnID);
	const std::string key = buf;
	connPtr->SetConnName(key);
	mConnMap[key] = connPtr;
	connPtr->SetDispatcher(mDispatcher);
	connPtr->BindMsgCallback(boost::bind(&EtyServer::OnMsg,this,_1,_2));
	connPtr->Ready();	
}

void EtyServer::CloseAConnection(ConnectionPtr connPtr)
{
	mConnMap.erase(connPtr->GetConnName() );
}

void EtyServer::StartService()
{
	mQuit = false;
	Listen();

	while( !mQuit)
	{
		mDispatcher->HanderEvents();
	}
}

void EtyServer::Broadcast(string& msg)
{
	// AutoPrintTimeinfo t; EF_TEMP_fix 可以添加一个测试时间的类.
	ConnectionMap::iterator it = mConnMap.begin();
	for (; it != mConnMap.end(); it++ )
	{
		if (it->second)
		{
			it->second->SendMsg(msg);
		}
	}
}

void EtyServer::OnMsg(std::string& msg, ConnectionPtr ptr)
{
	ptr->SendMsg(msg);
	// 
	// connPtr->SendMsg(msg);
}
