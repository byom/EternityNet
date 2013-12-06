/*****************************************************************************\
	This file is part of EternityNet
	@file
	@module
	@author		Yangwl
	@date		2013-8-12
	@email      39441733@qq.com  & ywlfield@gmail.com
	@brief      temporary test file socket client
				used like ./filename ipaddress
	@change
\*****************************************************************************/

#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOCALHOST "192.168.146.129"
#define ETY_SERVER_PORT    801 
#define BUFFER_SIZE 1024
#define FILE_NAME_MAX_SIZE 512

int main(int argc, char **argv)
{

	struct sockaddr_in client_addr;
	bzero(&client_addr,sizeof(client_addr));
	client_addr.sin_family = AF_INET;
	client_addr.sin_addr.s_addr = htons(INADDR_ANY);//INADDR_ANY表示自动获取本机地址
	client_addr.sin_port = htons(0);    //0表示让系统自动分配一个空闲端口

	int client_socket = socket(AF_INET,SOCK_STREAM,0);
	if( client_socket < 0)
	{
		printf("Create Socket Failed!\n");
		exit(1);
	}
	//把客户机的socket和客户机的socket地址结构联系起来
	if( bind(client_socket,(struct sockaddr*)&client_addr,sizeof(client_addr)))
	{
		printf("Client Bind Port Failed!\n"); 
		exit(1);
	}

	//设置一个socket地址结构server_addr,代表服务器的internet地址, 端口
	struct sockaddr_in server_addr;
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	if(inet_aton(LOCALHOST, &server_addr.sin_addr) == 0) //服务器的IP地址来自程序的参数
	{
		printf("Server IP Address Error!\n");
		exit(1);
	}
	server_addr.sin_port = htons(ETY_SERVER_PORT);
	socklen_t server_addr_length = sizeof(server_addr);
	if(connect(client_socket,(struct sockaddr*)&server_addr, server_addr_length) < 0)
	{
		printf("Can Not Connect To %s!\n",LOCALHOST);
		exit(1);
	}

while(true)
{
	char buffer[BUFFER_SIZE];
	bzero(buffer,BUFFER_SIZE);
	printf("Please Input your message:\t");
	scanf("%s", buffer);

	send(client_socket,buffer,BUFFER_SIZE,0);

	//从服务器接收数据到buffer中
	bzero(buffer,BUFFER_SIZE);
	int length = 0;
	length = recv(client_socket,buffer,BUFFER_SIZE,0);
	if(length < 0)
	{
		printf("Recieve Data From Server %s Failed!\n", LOCALHOST);
		break;
	}
	printf("Recieve From Server %s:%s\n", LOCALHOST, buffer);
	bzero(buffer,BUFFER_SIZE);    

}

	close(client_socket);
	return 0;
}
