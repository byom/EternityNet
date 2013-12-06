#include "Multiplexer.h"
#include "../utilities/LogUtil.h"

using namespace ety;

const int DEFAULT_EVENTS_SIZE = 64;

Multiplexer::Multiplexer()
{
	mepfd = epoll_create1(EPOLL_CLOEXEC);
	mEventArray.resize( DEFAULT_EVENTS_SIZE );
	mEpollEventsArray.resize( DEFAULT_EVENTS_SIZE );
}

Multiplexer::~Multiplexer()
{
	::close(mepfd);
}


int Multiplexer::AddEvent(Event& event)
{
	struct epoll_event ev;
	bzero(&ev,sizeof ev);

	ev.events = event.GetEvent();
	ev.data.ptr = &event;

	// EF_TEMP to delete
	WriteLog("Epoll Set fd:%d", event.Getfd() );
	
	if ( epoll_ctl(mepfd, EPOLL_CTL_ADD, event.Getfd(), &ev ) == -1 )
	{
		WriteErrLog(" Epoll Add Event Error:%s", strerror(errno));
		return -1;
	}

	event.SetInConnecting(true);
	return 0;
}

int Multiplexer::DeleteEvent(Event& event)
{
	struct epoll_event ev;
	bzero(&ev,sizeof ev);

	ev.events = event.GetEvent();
	ev.data.ptr = &event;
	// EF_TEMP to delete
	WriteLog("Epoll Delete fd:%d", event.Getfd() );

	if ( epoll_ctl(mepfd, EPOLL_CTL_DEL, event.Getfd(), &ev ) == -1 )
	{
		WriteErrLog(" Epoll Delete Event Error:%s", strerror(errno));
		return -1;
	}

	event.SetInConnecting(false);
	return 0;
}

int Multiplexer::ModifyEvent(Event& event)
{
	struct epoll_event ev;
	bzero(&ev,sizeof ev);

	ev.events = event.GetEvent();
	ev.data.ptr = &event;
	// EF_TEMP to delete
	WriteLog("Epoll Modify fd:%d", event.Getfd() );

	if ( epoll_ctl(mepfd, EPOLL_CTL_MOD, event.Getfd(), &ev ) == -1 )
	{
		WriteErrLog(" Epoll Modify Event Error:%s", strerror(errno));
		return -1;
	}

	return 0;
}

// timeout:-1 never timeout
int Multiplexer::GetActiveEvents(int timeout, EventArray& evArr)
{
	int numb = -1;
	numb =::epoll_wait(mepfd, &(*mEpollEventsArray.begin()), static_cast<int>(mEpollEventsArray.size()), timeout);
	if( numb > 0 )
	{
		for(int i = 0; i < numb; i++)
		{
			//Set the Events with epoll_events_ which returned by epoll_wait()
			Event* ev = static_cast<Event *>(mEpollEventsArray[i].data.ptr);
			ev->SetEvent( mEpollEventsArray[i].events );
			evArr.push_back(ev);
		}
		//size_t size = epoll_events_.size();
		//if(static_cast<size_t>(numb) == size) 
		//{
		//	mEpollEventsArray.resize(size * 2); 
		//}
	}
	else if( numb == 0 )
	{
		// EF_TEMP to delete
		WriteLog("Epoll Is looping, but none active event ." );
	}
	else
	{
		WriteErrLog(" Epoll Wait Error:%s", strerror(errno));
		return -1;
	}

	return 0; 

}
