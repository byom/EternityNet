/*****************************************************************************\
	This file is part of EternityNet
	@file
	@module
	@author		Yangwl
	@date		2013-8-12
	@email      39441733@qq.com  & ywlfield@gmail.com
	@brief      this is a test demo main function 
				
	@change
\*****************************************************************************/
#include <stdio.h>
#include "EtyServer.h"
#include "../utilities/LogUtil.h"
#include "../utilities/ConfigUtil.h"


int main(int argc, char **argv)
{
	int port = 0;
	char servName[128] = {0}; 
	ConfigUtil::GetProfileString("Config.ini","EtyService","ServerName", servName);
	ConfigUtil::GetProfileInt("Config.ini","EtyService","Port", port);

	StartLog(servName);

	EtyServer demoServer(servName, port);
	demoServer.StartService();
}


