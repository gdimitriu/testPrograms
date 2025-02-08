/*
	Copyright 2000 Gabriel Dimitriu

	This file is part of Algorithms and Socket.
	This is the server implementation of problem CDS2.

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
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
#include<arpa/inet.h>
#include"itoa.c"
#define PORT_SERVER 13000
#define SIZE 1024
char buff[SIZE];
char buff2[SIZE];
char temp[SIZE];
char *temp1;
char port[]="Port ";
char adresa[]="Adresa ";
#define T 10
int main(int argc,char **argv)
{
int listen_socket;	//descriptor de socket
int server_socket;	//descriptor de socket
int client_len;		//longeur de la structure de l'adresse de client
struct sockaddr_in server_addr; 	//l'adresse de server
struct sockaddr_in client_addr;	//l'adresse de client
struct sockaddr_in temp_addr;		//l'adresse temporare pour deservir le client
socklen_t len;
int i,j,n;
	if((listen_socket=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		perror("Server socket error");
		exit(-1);
	}
	//l'adresse locale socket
	memset((char *)&server_addr,0,sizeof(server_addr)); //erase tout
	server_addr.sin_family=AF_INET;				//le type d'internet
	server_addr.sin_port=htons(PORT_SERVER);	//le port pour le server
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);//de n'emporte pas quelle adresse
	//conecte
	if(bind(listen_socket,(struct sockaddr *)&server_addr,sizeof(server_addr))<0)
	{
		perror("listen socket error");
		close(listen_socket);
		exit(-2);
	}
	if(listen(listen_socket,5)<0)
	{
		perror("listen socket error");
		close(listen_socket);
		exit(-3);
	}
	client_len=sizeof(client_addr);
	//dans ce moment le server peux accepte les clients
	while(1)
	{
		if((server_socket=accept(listen_socket,(struct sockaddr *)&client_addr,&client_len))<0)
		{
			perror("server accept error");
			close(listen_socket);
			exit(-4);
		}
		//il trate le client
		for(i=0;i<T;i++)
		{
			memset((char *)buff,0,sizeof(buff)); //erase tout
			recv(server_socket,buff,SIZE,0);
			send(server_socket,&"t",2,0);
		}
		close(server_socket);
	}
}