/*
	Copyright 2000 Gabriel Dimitriu

	This file is part of Algorithms and Socket.
	This is the client implementation of problem CDS1.

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
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

#define SIZE 1024
#define PORT_SERVER 13001
static int buf[10];
static int rez[10];
int main(int argc,char **argv)
{
int client_socket;
int server_len;
struct sockaddr_in server_addr;
int i;
	if(argc<2){ printf("Introduisez le server\n");fflush(stdout);exit(-1);}
	if(argc==3) srand(atoi(argv[2]));
	memset((char *)&server_addr,0,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(PORT_SERVER);
	server_addr.sin_addr.s_addr=inet_addr(argv[1]);
	if((client_socket=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		perror("error de creation du socket");
		exit(-2);
	}
	if(connect(client_socket,(struct sockaddr *)&server_addr,sizeof(server_addr))<0)
	{
		perror("error de conectations du client");
		exit(-3);
	}
	for(i=0;i<10;i++) buf[i]=(int)(10.0*rand()/(RAND_MAX+1.0));
	send(client_socket,buf,sizeof(buf),0);
	recv(client_socket,rez,sizeof(rez),0);
	for(i=0;i<10;i++){printf(" %d ",buf[i]);fflush(stdout);}
	printf("\n");fflush(stdout);
	for(i=0;i<10;i++){printf(" %d ",rez[i]);fflush(stdout);}
	printf("\n");fflush(stdout);
	close(client_socket);
}