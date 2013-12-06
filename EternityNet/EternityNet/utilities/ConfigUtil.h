#ifndef _ETERNITY_CONFIGUTIL_H_
#define _ETERNITY_CONFIGUTIL_H_
/*****************************************************************************\
	This file is part of EternityNet
	@file
	@module
	@author		Yangwl
	@date		2013-8-12
	@email      39441733@qq.com  & ywlfield@gmail.com
	@brief      �� ��ȡ�����ļ��е���Ϣ, 
				�� ������windows �� linux ƽ̨�¶�����ʹ��
				�� ��ʽ����:
					#�����ļ���Ϣ��ע��
					[ServerInfo]				
					ip=192.16.31.2
					port = 8080
				�� ����#Ϊע��, [sth] Ϊsection , '=' �������޿ո����.

	@change
\*****************************************************************************/
#include <string>
#include <string.h>
using namespace std;

// namespace Eternity
namespace ety    // ��ƴ
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
