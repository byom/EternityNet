#ifndef _ETERNITY_MULTIPLEXER_H_
#define _ETERNITY_MULTIPLEXER_H_
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
#include <sys/epoll.h>
#include <errno.h>
#include <vector>
#include <map>

#include "Event.h"

using namespace ety;

// namespace Eternity
namespace ety    // บรฦด
{
typedef std::vector<Event*> EventArray;
typedef std::vector<struct epoll_event> EpollEventsArray;

class Multiplexer
{
public:
	Multiplexer();
	~Multiplexer();

	int AddEvent(Event& event);

	int DeleteEvent(Event& event);

	int ModifyEvent(Event& event);

	int GetActiveEvents(int timeout, EventArray& evArr);

private:
	int    mepfd;

	EventArray        mEventArray;
	EpollEventsArray  mEpollEventsArray;
	
};
}
#endif
