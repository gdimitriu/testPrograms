/*
	Copyright 2000 Gabriel Dimitriu

	This file is part of Algorithms and Socket.
	This is the mesurement implementation of problem CDS2.

    Algorithms and Socket is free software; you can redistribute it 
	and/or modify it under the terms of the GNU General Public License 
	as published by the Free Software Foundation; either version 2 of 
	the License, or (at your option) any later version.

    Algorithms and Socket is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Petri Network; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  
*/
#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include"temps.c"
#define PORT_SERVER 13000
#define SIZE 1024
char buff[SIZE];
#define T 10
int main(int argc,char **argv)
{
struct timeval t1a[T],t2a[T];
int client_socket;	//le descriptor pour le socket
int server_len;		//la longeur de server
struct sockaddr_in server_addr;	//l'adresse de server
int i;
	if(argc<2)
	{
		printf("introduisez le IP de server\n");fflush(stdout);
		exit(1);
	}
	gettimeofday(&t1a[0],NULL);
	memset((char *)&server_addr,0,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(PORT_SERVER);
	server_addr.sin_addr.s_addr=inet_addr(argv[1]);
	if((client_socket=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		perror("l'error de socket");
		exit(-1);
	}
	if(connect(client_socket,(struct sockaddr *)&server_addr,sizeof(server_addr))<0)
	{
		perror("l'error conecte client");
		close(client_socket);
		exit(-2);
	}
	gettimeofday(&t2a[0],NULL);
	temps(t1a,t2a,1);
	for(i=0;i<T;i++)
	{
		gettimeofday(&t1a[i],NULL);
		memset((char *)buff,0,sizeof(buff));
		strcpy(buff,"a");
		send(client_socket,buff,strlen(buff),0);
		recv(client_socket,buff,SIZE,0);
		gettimeofday(&t2a[i],NULL);
	}
	temps(t1a,t2a,T);
	printf("%s\n",buff);fflush(stdout);
	close(client_socket);
}