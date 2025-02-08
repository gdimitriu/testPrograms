/*
	Copyright 2000 Gabriel Dimitriu

	This file is part of Algorithms and Socket.
	This is the server implementation of problem CDS1.

    Algorithms and Socket is free software; you can redistribute it 
	and/or modify it under the terms of the GNU General Public License 
	as published by the Free Software Foundation; either version 2 of 
	the License, or (at your option) any later version.

    Algorithms and Socket is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Algorithms and Socket; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  
*/
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#define PORT_SERVER 13001
static int buf[10];
static int rez[10];
int main()
{
int listen_socket,server_socket,client_len;
struct sockaddr_in server_addr,client_addr;
int i;
	if((listen_socket=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		perror("error de server socket");
		exit(-1);
	}
	memset((char *)&server_addr,0,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(PORT_SERVER);
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	if(bind(listen_socket,(struct sockaddr *)&server_addr,sizeof(server_addr))<0)
	{
		perror("error server bind");
		close(listen_socket);
		exit(-2);
	}
	if(listen(listen_socket,5)<0)
	{
		perror("error de listen socket");
		close(listen_socket);
		exit(-3);
	}
	client_len=sizeof(client_addr);
	while(1)
	{
		if((server_socket=accept(listen_socket,(struct sockaddr *)&client_addr,&client_len))<0)
		{
			perror("error de accept socket");
			close(listen_socket);
			exit(-4);
		}
		recv(server_socket,buf,sizeof(buf),0);
		for(i=0;i<10;i++) rez[i]=0;
		for(i=0;i<10;i++) rez[buf[i]]++;
		send(server_socket,rez,sizeof(rez),0);
		close(server_socket);	
	}
}