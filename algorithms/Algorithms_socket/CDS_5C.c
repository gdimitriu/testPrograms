/*
	Copyright 2000 Gabriel Dimitriu

	This file is part of Algorithms and Socket.
	This is the client implementation of problem CDS5.

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
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

#define SIZE 1024
#define PORT_SERVER 12345
static char buf[SIZE];
int main(int argc,char **argv)
{
int client_socket;
int server_len;
struct sockaddr_in server_addr;
	if(argc<2){ printf("Input the server\n");fflush(stdout);exit(-1);}
	memset((char *)&server_addr,0,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(PORT_SERVER);
	server_addr.sin_addr.s_addr=inet_addr(argv[1]);
	if((client_socket=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		perror("socket creation error");
		exit(1);
	}
	if(connect(client_socket,(struct sockaddr *)&server_addr,sizeof(server_addr))<0)
	{
		perror("error connection client");
		exit(2);
	}
	gets(buf);
	send(client_socket,buf,strlen(buf),0);
	recv(client_socket,buf,SIZE,0);
	write(1,buf,sizeof(buf));
	close(client_socket);
	exit(0);
}
	