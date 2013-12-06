#ifndef _ETERNITY_CONFIGUTIL_H_
#define _ETERNITY_CONFIGUTIL_H_
/*****************************************************************************\
	This file is part of EternityNet
	@file
	@module
	@author		Yangwl
	@date		2013-8-12
	@email      39441733@qq.com  & ywlfield@gmail.com
	@brief      ★ 读取配置文件中的信息, 
				★ 该类在windows 和 linux 平台下都可以使用
				★ 格式类似:
					#配置文件信息的注释
					[ServerInfo]				
					ip=192.16.31.2
					port = 8080
				★ 其中#为注释, [sth] 为section , '=' 左右有无空格均可.

	@change
\*****************************************************************************/
#include <string>
#include <string.h>
using namespace std;

// namespace Eternity
namespace ety    // 好拼
{

class ConfigUtil
{
public:
	ConfigUtil(const string & fileName);

	virtual ~ConfigUtil(void);

	const string& GetFileName() const;

	void SetSection(const string& section);

	int GetProfileString( char* keyname, char* value);

	int GetProfileInt( char* keyname, int& value);

public:
	static int GetProfileString(const char* profile,const  char* sect,const  char* keyname, char* value);
	static int GetProfileInt(const char* profile,const  char* sect,const  char* keyname, int& value);

private:
	static char* LeftTrim(char* output, const char *input);
	static char* RightTrim(char* output, const char *input);
	static char* AllTrim(char* output, const char *input);

	static int PareseString(const char* profile,const char* sect,const char* keyname, char* value);

private:
	string mFilename;
	string mSection;
};

}
#endif
