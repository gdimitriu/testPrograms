/*
	Copyright 2000 Gabriel Dimitriu

	This file is part of Algorithms and Socket.
	Program client pentru schimbat caractere mari in mici

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
#define IP_SERVER "127.0.0.1"
static char buf[SIZE];
int main()
{
int client_socket;
int server_len;
struct sockaddr_in server_addr;
	memset((char *)&server_addr,0,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(PORT_SERVER);
	server_addr.sin_addr.s_addr=inet_addr(IP_SERVER);
	if((client_socket=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		perror("eroare creare socket");
		exit(1);
	}
	if(connect(client_socket,(struct sockaddr *)&server_addr,sizeof(server_addr))<0)
	{
		perror("eroare conectare client");
		exit(2);
	}
	strcpy(buf,"mesaj");
	send(client_socket,buf,strlen(buf),0);
	recv(client_socket,buf,SIZE,0);
	write(1,buf,sizeof(buf));
	close(client_socket);
	exit(0);
}
	