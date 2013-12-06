#ifndef _ETERNITY_TIMESTAT_H_
#define _ETERNITY_TIMESTAT_H_
/*****************************************************************************\
 *	This file is part of EternityNet
 *		@file
 *		@module
 *		@author		Yangwl
 *		@date		2013-8-12
 *		@email      39441733@qq.com  & ywlfield@gmail.com
 *		@brief  	seconds.micSeconds
 *					2013-8-12 22:43:22.123456
 *		@change
 *								\*****************************************************************************/
#include<stdio.h>
#include<stdint.h>
#include<string>

namespace ety
{

using std::string;

class TimeStat
{
public:
	TimeStat();

	explicit TimeStat(int64_t micSecSinceEpoch);

	string toString() const;
	string toFormatString() const;

	bool valid() const { return m_nMicSecSinceEpoch > 0; }
		
	int64_t micSecSinceEpoch() const { return m_nMicSecSinceEpoch; }

	static TimeStat now();

	static const int kMicSecPerSec = 1000 * 1000;

	inline TimeStat& operator=(const TimeStat& other)
	{
		m_nMicSecSinceEpoch = other.micSecSinceEpoch();
		return *this;
	}
private:
	int64_t m_nMicSecSinceEpoch;
};

inline bool operator==(const TimeStat& lhs, const TimeStat& rhs)
{
	return lhs.micSecSinceEpoch() == rhs.micSecSinceEpoch();
}
inline bool operator<(const TimeStat& lhs, const TimeStat& rhs)
{
	return lhs.micSecSinceEpoch() < rhs.micSecSinceEpoch();
}

} // end of namespace
#endif
