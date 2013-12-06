#ifndef _ETERNITY_CONDITION_H_
#define _ETERNITY_CONDITION_H_
/*****************************************************************************\
 *	This file is part of EternityNet
 *	@file
 *	@module
 *	@author		Yangwl
 *	@date		2013-8-12
 *	@email      39441733@qq.com  & ywlfield@gmail.com
 *	@brief              
 *	@change
\*****************************************************************************/

#include <sys/time.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>

#include "Mutex.h"
#include "../utilities/NonCopyable.h"
namespace ety    // 好拼
{
using namespace ety;
class Condition : private NonCopyable
{
public:
	Condition()
	{
		::pthread_cond_init( &m_cond, NULL);
	}
	~Condition()
	{
		::pthread_cond_destroy(&m_cond);
	}

	void broadcast()
	{
		::pthread_cond_broadcast(&m_cond);
	}

	void signal()
	{
		::pthread_cond_signal(&m_cond);
	}

	void wait( )
	{
		::pthread_cond_wait(&m_cond, m_mutex.getMutex() );
	}

	void wait( const struct timeval& now, uint64_t tmSecond, uint64_t tmMicroSecond)
	{
		struct timespec timeout;
		memset( &timeout, 0, sizeof(struct timespec) );

		uint64_t nsSum = (tmMicroSecond + now.tv_usec) * 1000;
		if ( nsSum >1000000000 )
		{
			timeout.tv_sec = (now.tv_sec + tmSecond + 1);
			timeout.tv_nsec = nsSum - 1000000000;
		}
		else
		{
			timeout.tv_sec = now.tv_sec + tmSecond;
			timeout.tv_nsec = nsSum;
		}

		::pthread_cond_timedwait(&m_cond, m_mutex.getMutex(), &timeout);
	}

	inline void lockMutex()  { m_mutex.lock(); };
	inline void unlockMutex(){ m_mutex.unlock(); };

private:
	pthread_cond_t	m_cond;
	Mutex			m_mutex;
};
	
	
	/////// code /////
}
#endif
