#include "Dispatcher.h"
#include "../utilities/LogUtil.h"

#include <sys/epoll.h>
using namespace ety;

Dispatcher::Dispatcher()
{
}

Dispatcher::~Dispatcher()
{
	mActiveEvents.clear();
}

void Dispatcher::InitDispatcher()
{
}

void Dispatcher::GetEvents()
{

}

void Dispatcher::HanderEvents()
{
	mMultiplexer.GetActiveEvents( -1 , mActiveEvents );
	EventsArray::iterator itBegin= mActiveEvents.begin();
	WriteLog("Hander Events:%d.", mActiveEvents.size() );

	for(; itBegin != mActiveEvents.end(); itBegin++)
	{
		(*itBegin)->HandleEvent();
	}

	mActiveEvents.clear();
}

void Dispatcher::RegisterEvent(Event& ev)
{
	if(!ev.GetInConnecting())
	mMultiplexer.AddEvent(ev);
	else
	mMultiplexer.ModifyEvent(ev);
}

void Dispatcher::RemoveEvent(Event &ev)
{
	if(ev.GetInConnecting())
	mMultiplexer.DeleteEvent(ev);
}

void Dispatcher::ClearEventsState(Event &ev)
{
	ev.SetEvent(0);
	mMultiplexer.ModifyEvent(ev);
}
