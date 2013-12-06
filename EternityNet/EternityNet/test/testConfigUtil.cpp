#include "../utilities/ConfigUtil.h"
#include "stdio.h"

int main()
{
	ety::ConfigUtil conf("./EtyServName.ini");
	conf.SetSection("ServerInfo");

	char ip[16];
	conf.GetProfileString("ip", ip);
	int port;
	conf.GetProfileInt("port", port);
	printf("%s\nport:%d\n",ip, port);
	getchar();

	return 0;
}
