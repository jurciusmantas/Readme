#include <winsock2.h>
#include <windows.h>
#define socklen_t int
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	WSADATA data;
	unsigned int port;
	int l_socket;
	
	int c_socket;
	
	int i,j;
	unsigned long NonBlock;
	FD_SET ReadSet;
	FD_SET WriteSet;
	
	struct sockaddr_in servaddr;
	struct sockaddr_in clientaddr1;
	struct sockaddr_in clientaddr2;
	
	socklen_t clientaddr1len;
	socklen_t clientaddr2len;
	
	int s_len;
	int r_len;
	
	char ServerBuffer[1024];
	char GitHubApiBuffer[1024];
	char ClientBuffer[1024];
	
	//Start config
	ServerBuffer[0] = '0';
	ClientBuffer[0] = '0';
	GitHubApiBuffer[0] = '0';
	
	if (argc != 2)
	{
		printf("USAGE: %s <port>\n", argv[0]);
		exit(1);
	}
	
	port = atoi(argv[1]);
	
	if ((port < 1) || (port > 65535))
	{
		printf("ERROR: INVALID PORT \n");
		exit(1);
	}
	
	WSAStartup(MAKEWORD(2,2),&data);
	
	
	//STEP 1
	//Server Socket CREATION with
	//socket() call
	l_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (l_socket < 0)
	{
		printf("ERROR: CANNOT CREATE LISTEN SOCKET \n");
		exit(1);
	}
	else
		printf("CREATING SOCKET - OK\n");
	
	//STEP 2
	//Server Socket BINDING with
	//bind() call
	
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(port);
	
	if (bind(l_socket, (struct sockaddr *)&servaddr, sizeof(servaddr)) <0)
	{
		printf("ERROR: BINDING LISTEN SOCKET \n");
		exit(1);
	}
	else
		printf("LISTEN SOCKET CREATING - OK\n");
	
	//STEP 3
	//Server Socket LISTENing with
	//listen() call
	if (listen(l_socket, 6) < 0)
	{
		printf("ERROR: LISTEN SOCKET \n");
		exit(1);
	}
	else
		printf("LISTEN SOCKET - OK\n");
	
	NonBlock = 1;
	if (ioctlsocket(l_socket, FIONBIO, &NonBlock) == SOCKET_ERROR)
	{
		printf("ERROR: MAKING LISTEN SOCKET NONBLOCKING FAILED\n");
		exit(1);
	}
	else
		printf("MAKING LISTEN SOCKET NONBLOCKING - OK\n");
	
	while(TRUE)
	{
		FD_ZERO(&ReadSet);
		FD_ZERO(&WriteSet);
		

		if (ServerBuffer[0] != '0') // start config
		{
			if (r_len == 0)
				FD_SET(c_socket, &ReadSet);
			else
				FD_SET(c_socket, &WriteSet);
		}
		
		FD_SET(l_socket, &ReadSet);
		
		if (select(c_socket + 1, &ReadSet, &WriteSet, NULL, NULL) == SOCKET_ERROR)
		{
			printf("ERROR: SELECT RETURNED SOCKET_ERROR");
			exit(1);
		}
		else
			printf("SELECT - OK\n");

		//Checking for arriving connections
		if (FD_ISSET(l_socket, &ReadSet))
		{	
			//STEP 5
			//Server Socket LISTENing with
			//listen() call
		
			if ((c_socket = accept(l_socket, NULL, NULL)) != INVALID_SOCKET )
			{
				// Make client socket non blocking
				NonBlock = 1;
				if (ioctlsocket(c_socket, FIONBIO, &NonBlock) == SOCKET_ERROR)
				{
					printf("ERROR: MAKING CLIENT SOCKET NONBLOCKING\n");
					exit(1);
				}
				
				printf("CLIENT SOCKET NONBLOCKING - OK\n");
				ServerBuffer[0] = '1'; //start config
				}
		}
		else
		{
			printf("ERROR: ACCEPTING SOCKET\n");
			exit(1);
		}
	
		
		
		//****************************\\
		//*******Handle message*******\\
		//****************************\\
		//Check if ReadSet or WriteSet 
		
			
		if (FD_ISSET(c_socket, &ReadSet))
		{	
			r_len = recv(c_socket, ClientBuffer, sizeof(ClientBuffer), 0);
			if(r_len == SOCKET_ERROR)
			{
				printf("ERROR: recv()");
			}
			else if (r_len == 0)
				printf("ASSERT: Gracefull close? \n");
			else
				printf("recv() - OK. CLIENT SENT %s\n", ClientBuffer);
			
			r_len = 0; //*TEMP* to set fd_set to read				
		}
	}
}