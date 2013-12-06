#ifndef _ETERNITY_DISPATCHER_H_
#define _ETERNITY_DISPATCHER_H_
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
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/scoped_ptr.hpp>
#include <vector>

#include "../utilities/NonCopyable.h"
#include "Multiplexer.h"
#include "Event.h"

using namespace ety;

// namespace Eternity
namespace ety    // บรฦด
{
typedef std::vector<Event*> EventsArray;

class Connection;
class Dispatcher:public NonCopyable
{
public:
	Dispatcher();
	~Dispatcher();

	void InitDispatcher();

	void GetEvents();

	void HanderEvents();

	void RegisterEvent(Event& ev);

	void RemoveEvent(Event &ev);

	void ClearEventsState(Event &ev);


private:
	Multiplexer   mMultiplexer;
	EventsArray   mActiveEvents;

};
/////// code /////
}
#endif