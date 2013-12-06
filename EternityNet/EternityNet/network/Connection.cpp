#include "Connection.h"
#include "Event.h"
#include "Dispatcher.h"
#include "../utilities/LogUtil.h"


using namespace ety;

Connection::Connection(const IpAddress& remote, const IpAddress& local, const int fd):
 mConnState(ST_INITED),
 mAddrRemote(remote),
 mAddrLocal(local),
 mSock(fd),
 mEventHander( new Event(fd, 0) )
{
	mEventHander->SetEventCallback( EPOLLIN, boost::bind(&Connection::ReadEvent, this));
	mEventHander->SetEventCallback( EPOLLOUT, boost::bind(&Connection::WriteEvent, this));
	mEventHander->SetEventCallback( CLOSE_EVENT, boost::bind(&Connection::CloseEvent, this));
	mEventHander->SetEventCallback( EPOLLERR, boost::bind(&Connection::ErrorEvent, this));
}

Connection::~Connection()
{
 mDispatcher->ClearEventsState(*mEventHander);
 mDispatcher->RemoveEvent(*mEventHander);
 delete mEventHander;
}

void Connection::SendMsg(std::string& msg)
{
	mMsgBuffer = msg;

	WriteLog(" fd:%d - Handle Write Event!", mSock.GetSocketfd() );
	int bufLen = mMsgBuffer.size();
	size_t total = send(mEventHander->Getfd(), mMsgBuffer.c_str(), bufLen, 0);

	if (total > 0 )
	{
		printf("Send Msg:%s", mMsgBuffer.c_str());
	}else if (total = 0)
	{

	}else
	{
		WriteErrLog("Send Msg Error:%s", strerror(errno));
	}


	//SendStreamMsg((void*)(msg.c_str()), len);
}

void Connection::SendStreamMsg(void *buf, size_t size)
{
	// SendMsg;
	// send( sock, buf, size);
}

void Connection::ReadEvent()
{
	WriteLog(" fd:%d - Handle Read Event!", mSock.GetSocketfd() );
	char buf[1024];
	size_t total = read(mEventHander->Getfd(), buf, 1024);

	if (total > 0 )
	{
		printf("Get Msg:%s", buf);
	}else if (total = 0)
	{

	}else
	{
		WriteErrLog("Read Msg Error:%s", strerror(errno));
	}

	std::string msg(buf);
	mEventHander->OnMsg(msg, shared_from_this());

}

void Connection::WriteEvent()
{
	WriteLog(" fd:%d - Handle Write Event!", mSock.GetSocketfd() );
	int bufLen = mMsgBuffer.size();
	size_t total = send(mEventHander->Getfd(), mMsgBuffer.c_str(), bufLen, 0);

	if (total > 0 )
	{
		printf("Send Msg:%s", mMsgBuffer.c_str());
	}else if (total = 0)
	{

	}else
	{
		WriteErrLog("Send Msg Error:%s", strerror(errno));
	}

}

void Connection::CloseEvent()
{
	WriteLog(" fd:%d - Handle Close Event!", mSock.GetSocketfd());
	SetConnState(ST_CLOSED);
	mDispatcher->ClearEventsState(*mEventHander);
}

void Connection::ErrorEvent()
{
	WriteLog(" fd:%d - Handle Error Event!", mSock.GetSocketfd() );
}

void Connection::Ready()
{
	mEventHander->SetEvent(EPOLLIN);
	mDispatcher->RegisterEvent(*mEventHander);
}

void Connection::BindMsgCallback(MessageCallback cb)
{
	mEventHander->BindMsgCallback(cb); 
}
