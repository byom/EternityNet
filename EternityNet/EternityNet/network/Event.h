#ifndef _ETERNITY_EVENT_H_
#define _ETERNITY_EVENT_H_
/*****************************************************************************\
	This file is part of EternityNet
	@file
	@module
	@author		Yangwl
	@date		2013-8-12
	@email      39441733@qq.com  & ywlfield@gmail.com
	@brief      Event used by epool(Multiplexer), and maped by Connection   
	@change
\*****************************************************************************/
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <sys/epoll.h>
#include <string>

#include "../utilities/NonCopyable.h"

using namespace ety;

// namespace Eternity
namespace ety    // บรฦด
{
class Connection;
typedef boost::shared_ptr<Connection> ConnectionPtr;
typedef boost::function<void(void)> EventCallback;
typedef boost::function<void(std::string&, ConnectionPtr)> MessageCallback;
typedef boost::function<ConnectionPtr&(void)> AcceptCallback;

enum EventType
{
	//READ_EVENT     = 02,
	//WRITE_EVENT    = 04,
	//ERROR_EVENT,
	NONE_EVENT,
	ACCEPT_EVENT     = 1<<6,
	CLOSE_EVENT		 = 2<<6,
	CONNECT_EVENT    = 3<<6,
	MESSAGE_EVENT    = 4<<6,
	WRITEEND_EVENT   = 5<<6,
	TIMEOUT_EVENT	 = 6<<6,
};

class Event:public NonCopyable
{
public:
	Event(int fd, int event = 0);

	~Event();

	void HandleEvent();

	void OnMsg(std::string&, ConnectionPtr);

	void SetEventCallback(int type, EventCallback cb);

	void BindMsgCallback(MessageCallback cb);			// handle message function defined by users

	void SetEvent(int type);

	bool GetInConnecting()
	{
		return mIsInConnecting;
	}
	void SetInConnecting(bool b)
	{
		mIsInConnecting = b;
	}

	int GetEvent()
	{
		return mEventType;
	}

	int Getfd() const
	{
		return mfd;
	}

private:
	int              mfd;
	int              mEventType;
	bool             mIsInConnecting;

	EventCallback    mFnAccept;
	EventCallback    mFnRead;
	EventCallback    mFnWrite;
	EventCallback    mFnClose;
	EventCallback    mFnConnect;
	EventCallback    mFnError;
	EventCallback    mFnWriteEnd;
	EventCallback    mTimerOut;
	MessageCallback  mFnMessage;
};
}
#endif
