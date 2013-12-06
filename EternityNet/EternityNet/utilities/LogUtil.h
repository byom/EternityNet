
#ifndef _ETERNITY_LOG_UTIL_H_
#define _ETERNITY_LOG_UTIL_H_


#include"Singleton.h"
#include"Log.h"

 
#define StartLog(file) ety::Singleton<ety::Log>::Instance().initLog( file )

#define StartLogWithParam(file, nLine, nSize) \
	ety::Singleton<ety::Log>::Instance().initLog( file, nLine, nSize )

#define WriteLog(fmt, ...) ety::Singleton<ety::Log>::Instance().logInfo( fmt, ##__VA_ARGS__)
#define WriteErrLog(fmt, ...)  ety::Singleton<ety::Log>::Instance().logErr( fmt, ##__VA_ARGS__)
#define WriteDetailLog( file, line, fmt, ...)  ety::Singleton<ety::Log>::Instance().logDetail(file, line,  fmt, ##__VA_ARGS__)
#define WriteFatalLog(file, line, fmt, ...)  ety::Singleton<ety::Log>::Instance().logFatal(file, line,  fmt, ##__VA_ARGS__)

#define EnablePrintLog() ety::Singleton<ety::Log>::Instance().enablePrintToScreen( true );

#endif
