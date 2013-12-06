#ifndef _ETERNITY_MUTEX_H_
#define _ETERNITY_MUTEX_H_
/*****************************************************************************\
 *	This file is part of EternityNet
 *	@file
 *	@module
 *	@author		Yangwl
 *	@date		2013-8-12
 *	@email      39441733@qq.com  & ywlfield@gmail.com
 *	@brief              
 *	@change
 *
\*****************************************************************************/

#include <pthread.h>
#include "../utilities/NonCopyable.h"

namespace ety    // 好拼
{
using namespace ety;

class Mutex : private NonCopyable
{
public:
	Mutex(int kind = PTHREAD_MUTEX_FAST_NP)
	{
		pthread_mutexattr_t attr;
		::pthread_mutexattr_init(&attr);
		::pthread_mutexattr_settype(&attr, kind);
		::pthread_mutex_init(&m_mutex, &attr);
	}

	~Mutex()
	{
		::pthread_mutex_destroy(&m_mutex);
	}

	inline void lock()
	{
		::pthread_mutex_lock(&m_mutex);
	}

	inline void unlock()
	{
		::pthread_mutex_unlock(&m_mutex);
	}

	pthread_mutex_t* getMutex()
	{
		return &m_mutex;
	}

private:
	pthread_mutex_t    m_mutex;

};

class AutoMutex : private NonCopyable
{
public:
	AutoMutex(Mutex& m):m_lock(m)
	{
		m_lock.lock();
	}

	~AutoMutex()
	{
		m_lock.unlock();
	}

private:
	Mutex& m_lock;
};

}

#endif
