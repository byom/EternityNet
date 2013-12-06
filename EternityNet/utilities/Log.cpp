#include<errno.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/syscall.h>

#include "../utilities/TimeStat.h"
#include "Log.h"

using namespace ety;

namespace ety{

const int Max_Length = 1024;
#define gettid() syscall(SYS_gettid)

	Log::Log()
	{
		mStatLogOpened = false;
		mErrLogOpened = false;

		mMaxLine = 1024; // 1W
		mMaxSize = 20480; // 20M
		mPrintToScreen = false;

		mCurYear = 0;
		mCurMon = 0;
		mCurDay = 0;

		mCurSnStat = 1;
		mCurSnErr = 1;
		mCurLineStat = 0;
		mCurSizeStat = 0;
		mCurLineErr = 0;
		mCurSizeErr = 0;
	}

	Log::~Log()
	{
	}

	void Log::initLog(const char *fileName, int maxLine, int maxSize )
	{
		strcpy( mFileName, fileName);
		sprintf( mStatLogPath, "./%sLog/Log/", fileName);	
		sprintf( mErrLogPath, "./%sLog/ErrLog/", fileName);

		mMaxLine = maxLine;
		mMaxSize = maxSize;

		open();
	}

	int Log::enablePrintToScreen(bool flag)
	{
		mPrintToScreen = flag;
		return mPrintToScreen;
	}

	int Log::open()
	{
		time_t timet = time(NULL);
		struct tm *tmp = localtime(&timet);

		mCurYear = tmp->tm_year;
		mCurMon = tmp->tm_mon;
		mCurDay = tmp->tm_mday;
	// mkdir log path
	char file[1024];
	sprintf(file, "./%sLog/", mFileName);
	int ret = access(file, F_OK);
	if (0 != ret )
	{
		ret = mkdir(file, 0777);
		if (0 != ret )
		{
			std::cout<< "Log::open() mkdir="<< file <<"failed: "<< strerror(errno) << std::endl;
			return -1;
		}
	}


	ret = access(mStatLogPath, F_OK);
	if (0 != ret )
	{
		ret = mkdir(mStatLogPath, 0777);
		if (0 != ret )
		{
			std::cout<< "Log::open() mkdir="<<mStatLogPath <<"failed: "<< strerror(errno) << std::endl;
			return -1;
		}
	}

	sprintf(file, "%s/%s%d-%d-%d", mStatLogPath, mFileName, mCurYear, mCurMon+1, mCurDay);
	ret = access(file, F_OK);
	if ( 0 != ret )
	{
		ret = mkdir(file, 0777);
		if ( 0 != ret )
		{
			std::cout<< "Log::open() mkdir="<< file <<"failed"<< strerror(errno) << std::endl;
			return -1;
		}
	}

	while(true)
	{
		sprintf(file,"%s/%s%d-%d-%d/%s_%d", mStatLogPath, mFileName, mCurYear, mCurMon+1, mCurDay, mFileName, mCurSnStat);
		ret = access(file, F_OK);
		if(0 == ret)
		{
			mCurSnStat++;
			continue;
		}
		break;
	}

	mOstreamStat.open(file);
	mStatLogOpened = true;


	// mkdir and open Error log
	char errfile[1024];
	ret = access(mErrLogPath, F_OK);
	if (0 != ret )
	{
		ret = mkdir(mErrLogPath, 0777);
		if (0 != ret )
		{
			std::cout<< "Log::open() mkdir="<<mErrLogPath <<"failed"<< strerror(errno) << std::endl;
			return -1;
		}
	}

	sprintf(errfile, "%s/%s%d-%d-%d", mErrLogPath, mFileName, mCurYear, mCurMon+1, mCurDay);
	ret = access(errfile, F_OK);
	if ( 0 != ret )
	{
		ret = mkdir(errfile, 0777);
		if ( 0 != ret )
		{
			std::cout<< "Log::open() mkdir="<< errfile <<"failed"<< strerror(errno) << std::endl;
			return -1;
		}
	}

	while(true)
	{
		sprintf(errfile,"%s/%s%d-%d-%d/%s_%d", mErrLogPath, mFileName, mCurYear, mCurMon+1, mCurDay, mFileName, mCurSnErr);
		ret = access(errfile, F_OK);
		if(0 == ret)
		{
			mCurSnErr++;
			continue;
		}
		break;
	}

	mOstreamErr.open(errfile);
	mErrLogOpened = true;

	return 0;
}


int Log::logInfo(const char* fmt, ...)
{
	if(!mStatLogOpened)
	{
	  cout<<"LogUtil Not Inited!!!"<<endl;
	  return -1;
	}
	va_list vl;
	va_start(vl, fmt);
	int ret = log(LOG_LEVEL_INFO, "", -1, fmt, vl);
	va_end(vl);

	return ret;
}

int Log::logErr(const char* fmt, ...)
{
	if(!mErrLogOpened)
	{
	  cout<<"LogUtil Not Inited!!!"<<endl;
	  return -1;
	}
	va_list vl;
	va_start(vl, fmt);
	int ret = log(LOG_LEVEL_ERROR, "", -1, fmt, vl);
	va_end(vl);

	return ret;
}

int Log::logDetail(const char *file, int line, const char* fmt, ...)
{
	if(!mStatLogOpened)
	{
	  cout<<"LogUtil Not Inited!!!"<<endl;
	  return -1;
	}
	va_list vl;
	va_start(vl, fmt);
	int ret = log(LOG_LEVEL_DETAIL, file, line, fmt, vl);
	va_end(vl);

	return ret;
}

int Log::logFatal(const char *file, int line,const char* fmt, ...)
{
	if(!mErrLogOpened)
	{
	  cout<<"LogUtil Not Inited!!!"<<endl;
	  return -1;
	}
	va_list vl;
	va_start(vl, fmt);
	int ret = log(LOG_LEVEL_FATAL, file, line, fmt, vl);
	va_end(vl);

	return ret;
}

int Log::log(int level, const char *file, int line, const char* fmt, va_list ap)
{
	char logMsg[Max_Length];
	if( -1 != line)
		sprintf( logMsg, "%s [%ld] %s %d:", TimeStat::now().toFormatString().c_str(), gettid(), file, line);
	else
		sprintf( logMsg, "%s [%ld]:", TimeStat::now().toFormatString().c_str(), gettid());

	int len = strlen( logMsg );
	vsnprintf(logMsg + len, Max_Length-len-2, fmt, ap);
	
	strcat(logMsg, "\n");
	logMsg[Max_Length-1] = '\0';

	std::ostringstream os;
	os << logMsg;

	printToFile( level, os.str() );

	if( mPrintToScreen )
	{
		std::cout << os.str();
	}
	
	return 0;
}

void Log::printToFile(int level, const std::string& mesg)
{
	time_t timep = time( NULL );
	struct tm *tmp = localtime(&timep);

	if( (mCurYear != tmp->tm_year) || (mCurMon != tmp->tm_mon) || (mCurDay != tmp->tm_mday) )
	{
		mOstreamStat.close();
		mOstreamStat.clear();

		mOstreamErr.close();
		mOstreamErr.clear();

		mCurYear = tmp->tm_year;
		mCurMon  = tmp->tm_mon;
		mCurDay  = tmp->tm_mday;
		
		mCurSizeStat = 0;
		mCurLineStat = 0;
		mCurSizeErr = 0;
		mCurLineErr = 0;
		mCurSnStat = 0;
		mCurSnErr = 0;

		//printf("did make different file 1\n");
		char file[1024];
	
		sprintf(file, "%s/%s%d-%d-%d", mStatLogPath, mFileName, mCurYear, mCurMon+1, mCurDay);
		mkdir(file, 0777);

		sprintf(file,"%s/%s%d-%d-%d/%s_%d", mStatLogPath, mFileName, mCurYear, mCurMon+1, mCurDay, mFileName, mCurSnStat);
		mOstreamStat.open(file);

		sprintf(file, "%s/%s%d-%d-%d", mErrLogPath, mFileName, mCurYear, mCurMon+1, mCurDay);
		mkdir(file, 0777);

		sprintf(file,"%s/%s%d-%d-%d/%s_%d", mErrLogPath, mFileName, mCurYear, mCurMon+1, mCurDay, mFileName, mCurSnErr);
		mOstreamErr.open(file);
	
		if( level == LOG_LEVEL_INFO || level == LOG_LEVEL_DETAIL )
		{
			mOstreamStat << mesg;
			mOstreamStat.flush();
			mCurLineStat += 1;
			mCurSizeStat += mesg.length();
		}
		if( level == LOG_LEVEL_ERROR || level == LOG_LEVEL_FATAL )
		{
			mOstreamErr << mesg;
			mOstreamErr.flush();
			mCurLineErr += 1;
			mCurSizeErr += mesg.length();
		}
	}
	// wirte LOG_LEVEL_INFO
	if( level == LOG_LEVEL_INFO || level == LOG_LEVEL_DETAIL )
	{
		mOstreamStat << mesg;
		mOstreamStat.flush();
		mCurLineStat += 1;
		mCurSizeStat += mesg.length();
	}
	if( level == LOG_LEVEL_ERROR || level == LOG_LEVEL_FATAL )
	{
		mOstreamErr << mesg;
		mOstreamErr.flush();
		mCurLineErr += 1;
		mCurSizeErr += mesg.length();
	}

	// check
	if( mCurLineStat >= mMaxLine || mCurSizeStat >= mMaxSize )
	{
		mOstreamStat.close();
		mOstreamStat.clear();

		mCurSnStat++;
		mCurLineStat = 0;
		mCurSizeErr = 0;

		char file[1024];
		
		sprintf(file,"%s/%s%d-%d-%d/%s_%d", mStatLogPath, mFileName, mCurYear, mCurMon+1, mCurDay, mFileName, mCurSnStat);
		mOstreamStat.open(file);

	}
	// check
	if( mCurLineErr >= mMaxLine || mCurSizeErr >= mMaxSize )
	{
		mOstreamErr.close();
		mOstreamErr.clear();
		
		mCurSnErr++;
		mCurLineErr = 0;
		mCurSizeErr = 0;
	
		char file[1024];
		sprintf(file,"%s/%s%d-%d-%d/%s_%d", mErrLogPath, mFileName, mCurYear, mCurMon+1, mCurDay, mFileName, mCurSnErr);
		mOstreamErr.open(file);
	}

}


} // end of namespace

