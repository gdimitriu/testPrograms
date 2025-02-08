/*
	Copyright 2000 Gabriel Dimitriu

	This file is part of Algorithms and Socket.
	Programul server	pentru schimbat caractere mari in mici

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
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#define PORT_SERVER 12345
#define SIZE 1024
static char buf[SIZE];
int main()
{
int listen_socket,	//descriptor de socket
	server_socket,		//descriptor de socket
	client_len;			//lungimea structurii adresei client
struct sockaddr_in
	server_addr,		//adresa serverului
	client_addr;		//adresa clientului
int i,n;
pid_t pid;
	if((listen_socket=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		perror("server socket error");
		exit(1);
	}
	//adresa locala socket
	memset((char *)&server_addr,0,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(PORT_SERVER);
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	//conectare
	if(bind(listen_socket,(struct sockaddr *)&server_addr,sizeof(server_addr))<0)
	{
		perror("eroare server bind");
		close(listen_socket);
		exit(2);
	}
	if(listen(listen_socket,5)<0)
	{
		perror("listen socket error");
		close(listen_socket);
		exit(3);
	}
	// NEAPARAT
	client_len=sizeof(client_addr);
	while(1)
	{
		if((server_socket=accept(listen_socket,(struct sockaddr *)&client_addr,&client_len))<0)
		{
			perror("server accept error");
			close(listen_socket);
			exit(4);
		}
		if((pid=fork())==0)
		{
			n=recv(server_socket,buf,SIZE,0);
			for(i=0;i<strlen(buf);i++)
				buf[i]-=32;
			send(server_socket,buf,strlen(buf),0);
		}
		close(server_socket);
	}
}