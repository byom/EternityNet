#include "ConfigUtil.h"
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#define KEYVALLEN 1024

using namespace ety;

ConfigUtil::ConfigUtil(const string & fileName)
{
	mFilename = fileName;
}

ConfigUtil::~ConfigUtil()
{
}

const string& ConfigUtil::GetFileName() const
{
	return mFilename;
}

void ConfigUtil::SetSection(const string& section)
{
	mSection = section;
}

char* ConfigUtil::LeftTrim(char* output, const char *input)
{
	assert(input != NULL);
	assert(output != NULL);
	assert(output != input);
	for   (NULL; *input != '\0' && isspace(*input); ++input){
		;
	}
	return strcpy(output, input);
}

char* ConfigUtil::RightTrim(char* output, const char *input)
{
	char *p = NULL;
	assert(input != NULL);
	assert(output != NULL);
	assert(output != input);
	strcpy(output, input);
	for(p = output + strlen(output) - 1; p >= output && isspace(*p); --p){
		;
	}
	*(++p) = '\0';
	return output;
}

char* ConfigUtil::AllTrim(char* output, const char *input)
{
	char *p = NULL;
	assert(input != NULL);
	assert(output != NULL);
	LeftTrim(output, input);
	for   (p = output + strlen(output) - 1;p >= output && isspace(*p); --p){
		;
	}
	*(++p) = '\0';
	return output;
}

int ConfigUtil::PareseString(const char *profile,const  char *sect,const  char *keyname, char *value )
{
	assert(profile != NULL);
	assert(sect != NULL);
	assert(keyname != NULL);
	assert(value != NULL);

	char section[32],key[32];
	char *buf,*c;
	char buf_i[KEYVALLEN];
	char buf_o[KEYVALLEN];
	FILE *fp;
	int found=0;   /* 1 section 2 key */
	if( (fp=fopen( profile,"r" ))==NULL ){
		// WriteErrLog("openfile [%s] error [%s]\n",profile,strerror(errno));
		printf( "openfile [%s] error!\n",profile);
		return(-1);
	}
	fseek( fp, 0, SEEK_SET );
	memset( section, 0, sizeof(section) );
	sprintf( section,"[%s]", sect );

	while( !feof(fp) && fgets( buf_i, KEYVALLEN, fp )!=NULL ){
		LeftTrim(buf_o, buf_i);
		if( strlen(buf_o) <= 0 )
			continue;
		buf = NULL;
		buf = buf_o;

		if( found == 0 ){
			if( buf[0] != '[' ) {
				continue;
			} else if ( strncmp(buf,section,strlen(section))==0 ){
				found = 1;
				continue;
			}

		} else if( found == 1 ){
			if( buf[0] == '#' ){
				continue;
			} else if ( buf[0] == '[' ) {
				break;
			} else {
				if( (c = (char*)strchr(buf, '=')) == NULL )
					continue;
				memset( key, 0, sizeof(key) );

				sscanf( buf, "%[^=|^ |^\t]", key );
				if( strcmp(key, keyname) == 0 ){
					sscanf( ++c, "%[^\n]", value );
					char *value_o = (char *)malloc(strlen(value) + 1);
					if(value_o != NULL){
						memset(value_o, 0, sizeof(value_o));
						AllTrim(value_o, value);
						if(value_o && strlen(value_o) > 0)
							strcpy(value, value_o);
						free(value_o);
						value_o = NULL;
					}
					found = 2;
					break;
				} else {
					continue;
				}
			}
		}
	}
	fclose( fp );
	if( found == 2 )
		return(0);
	else
		return(-1);
}
// member function
int ConfigUtil::GetProfileString(char* keyname, char* value)
{
	if (mFilename.empty() || mSection.empty())
	{
		//WriteErrLog("Config filename or section not inilization");
		printf("Config filename or section not inilization");
		return -1;
	}

	return ConfigUtil::PareseString(mFilename.c_str(), mSection.c_str(), keyname, value );
}

int ConfigUtil::GetProfileInt(char* keyname, int& value)
{
	if (mFilename.empty() || mSection.empty())
	{
		//WriteErrLog("Config filename or section not inilization");
		printf("Config filename or section not inilization");
		return -1;
	}

	return ConfigUtil::GetProfileInt(mFilename.c_str(), mSection.c_str(), keyname, value);
}

// static function
int ConfigUtil::GetProfileString(const char* profile,const char* sect,const char* keyname, char* value)
{
	return ConfigUtil::PareseString(profile, sect, keyname, value );
}

int ConfigUtil::GetProfileInt(const char* profile,const char* sect,const char* keyname, int& value)
{
	char ret[KEYVALLEN];
	int res = ConfigUtil::PareseString(profile, sect, keyname, ret);
	if ( 0 != res )
	{
		// WriteErrLog("Read the key:%s Error!", keyname);
		value = 0;
		return res;
	}
	value = atoi(ret);
	return 0;
}
