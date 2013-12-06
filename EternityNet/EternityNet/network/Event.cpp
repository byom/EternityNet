#include "Event.h"
#include "../utilities/LogUtil.h"

using namespace ety;

Event::Event(int fd, int event/* =0 */):
 mfd( fd ),
 mEventType(event),
 mIsInConnecting(false)
{

}

Event::~Event()
{
}

void Event::HandleEvent()
{
	WriteLog(" Handle Event:%d", mEventType );
	if ( mEventType & (EPOLLIN | EPOLLPRI | EPOLLRDHUP) )
	{
		WriteLog("Handle Read Event");
		mFnRead();
	}
	if ( mEventType & (EPOLLOUT) )
	{
		WriteLog("Handle Write Event");
		mFnWrite();
	}
	if( mEventType & (EPOLLERR | EPOLLHUP) )
	{
		WriteLog("Handle Error Event");
		mFnError();
	}
	if( mEventType == ACCEPT_EVENT )
	{
		WriteLog("Handle Accept Event");
		mFnAccept();
	}
}

void Event::OnMsg(std::string& msg, ConnectionPtr ptr)
{
	mFnMessage(msg, ptr);
}

//void Event::OnMsg(string& msg, ConnectionPtr ptr)
//{
//	//	mFnMessage(msg, ptr);
//}

void Event::SetEventCallback(int type, EventCallback cb)
{
	switch ( type )
	{
	case ACCEPT_EVENT:
		mFnAccept = cb;
		break;	
	case EPOLLIN:
	case EPOLLPRI:
	case EPOLLRDHUP:
		mFnRead = cb;
		break;
	case EPOLLOUT:
		mFnWrite = cb;
		break;
	case CLOSE_EVENT:
		mFnClose = cb;
		break;
	case CONNECT_EVENT:
		mFnConnect = cb;
		break;
	case EPOLLERR:
	case EPOLLHUP:
		mFnError = cb;
		break;
	case WRITEEND_EVENT:
		mFnWriteEnd = cb;
		break;
	case TIMEOUT_EVENT:
		mTimerOut = cb;
		break;
	}
}

void Event::BindMsgCallback(MessageCallback cb)
{
	mFnMessage = cb;
}

void Event::SetEvent(int type)
{
	mEventType = type;
}
