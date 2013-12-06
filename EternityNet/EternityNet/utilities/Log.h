#ifndef _ETERNITY_LOG_H_
#define _ETERNITY_LOG_H_
/*****************************************************************************\
 *	This file is part of EternityNet
 *	@file
 *	@module
 *	@author		Yangwl
 *	@date		2013-8-12
 *	@email      39441733@qq.com  & ywlfield@gmail.com
 *	@brief      simple log        
 *	@change
 *  
 \*****************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdarg.h>
#include<sys/time.h>

#include<set>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

using namespace std;
namespace ety    // 好拼
{

	typedef enum
	{
		LOG_LEVEL_INFO = 0,
		LOG_LEVEL_DETAIL,
		LOG_LEVEL_ERROR,
		LOG_LEVEL_FATAL
	} loglevel;

	class Log
	{
	public:
		Log();
		~Log();

		void initLog(const char *fileName, int maxLine = 1024, int maxSize = 20480 );
		int enablePrintToScreen(bool flag);
	
		int logInfo(const char *fmt, ...);
		int logErr(const  char *fmt, ...);
		int logDetail(const char *file, int line, const char* fmt, ...);
		int logFatal(const char *file, int line, const char* fmt, ...);

	private:
		int open();
		int log(int level, const char *file, int line, const char* fmt, va_list ap);
		void printToFile(int level, const std::string& mesg);

	private:
		std::ofstream    mOstreamStat;
		std::ofstream    mOstreamErr;
	
	private:
		bool mStatLogOpened;
		bool mErrLogOpened;
		int  mMaxLine;
		int  mMaxSize;
		bool mPrintToScreen;

		char mStatLogPath[256];
		char mErrLogPath[256];
		char mFileName[256];

		int  mCurSnStat; // 当天日志文件序号
		int  mCurSnErr;

		int  mCurYear;
		int  mCurMon;
		int  mCurDay;

		int  mCurLineStat;
		int  mCurLineErr;
		int  mCurSizeStat;
		int  mCurSizeErr;

	};
}
#endif
