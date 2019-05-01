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
	SOCKET s;
	SOCKET s2;
	FILE * fp;
	
	struct hostent *he;
	struct in_addr **addr_list;
	char ip[100];
	
	struct sockaddr_in servaddr;
	socklen_t servaddrlen;		
	
	int s_len;
	int r_len, realr_len;
	int i;
	
	char Buffer[4096];
	char* lookingFor = "To download file click the link below:<br /><a href=";
	char* point;
	char downloadLink[70];
	
	WSAStartup(MAKEWORD(2,2),&data);
	
	/////////////
	if ( (he = gethostbyname( "s000.tinyupload.com" ) ) == NULL)
	{		
		//gethostbyname failed
		printf("ERROR : gethostbyname() failed : %d\n" , WSAGetLastError());
		return 1;
	}
			
	addr_list = (struct in_addr **) he->h_addr_list;
		
	for(i = 0; addr_list[i] != NULL; i++) 
	{
		//Return the first one;
		strcpy(ip , inet_ntoa(*addr_list[i]) );
	}
		
	printf("s000.tinyupload.com resolved to : %s\n", ip);
			
	memset(&servaddr, 0, sizeof(servaddr));
	servaddrlen = sizeof(servaddr);
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(ip);
	servaddr.sin_port = htons(80); // <- http
	//servaddr.sin_port = htons(443); // <- https
	
	if ((s = socket(AF_INET,SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("ERROR: creating s failed : %d\n" , WSAGetLastError());
		//should set read set and return from if...
		exit(1);
	}		
		
	printf("Connecting to server...\n");
	if (connect(s, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
	{
		printf("ERROR: Connect with s failed : %d\n" , WSAGetLastError());
		//should set read set and return from if...
		exit(1);
	}			
	printf("Connected!\n");
	
	printf("Sending GET...\n");
	// http://s000.tinyupload.com/index.php?file_id=78914622886860086395
	strcpy(Buffer, "GET /index.php?file_id=78914622886860086395 HTTP/1.1\r\nHost: s000.tinyupload.com\r\n\r\n");
	send(s, Buffer, strlen(Buffer),0);
	printf("GET Sent!\n");
	
	printf("Receiving from server...\n");
	r_len = recv(s, Buffer, sizeof(Buffer), 0);
	realr_len = r_len;
	
	//show header
	int found = 0;
	printf("\n%340.340s\n", Buffer);
	while (r_len > 0)
	{ 
		r_len = recv(s, Buffer, sizeof(Buffer), 0); 
		realr_len += r_len;
		point = strstr(Buffer, lookingFor);
		if(point != NULL && found == 0)
		{
			//point - pointer of the start of look 
			strncpy(downloadLink, point+strlen(lookingFor)+1, 69);
			printf("\n--\nDownload link - %s\n--\n", downloadLink);
			found = 1;
		}
	}
	
	printf("recv() %d bytes of data\n\n",realr_len);
	closesocket(s);	
	
	/*******************/
	//Now I dont know why but I need a new socket
	/*******************/
	printf("Starting file download\n",realr_len);
	
	if ((s2 = socket(AF_INET,SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("ERROR: creating s failed : %d\n" , WSAGetLastError());
		//should set read set and return from if...
		exit(1);
	}		
		
	printf("Connecting to server...\n");
	if (connect(s2, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
	{
		printf("ERROR: Connect with s failed : %d\n" , WSAGetLastError());
		//should set read set and return from if...
		exit(1);
	}			
	printf("Connected!\n");
	
	//SEND GET to get desired file;
	memset(Buffer, 0, sizeof(Buffer));
	strcpy(Buffer, "GET /");	
	strcat(Buffer, downloadLink);
	strcat(Buffer, " HTTP/1.1\r\nHost: s000.tinyupload.com\r\n\r\n");	
	
	printf("Sending GET...\n");
	send(s2, Buffer, strlen(Buffer),0);
	printf("GET Sent!\n");
	
	printf("Receiving from server...\n");
	r_len = recv(s2, Buffer, sizeof(Buffer), 0);
	realr_len = r_len;
	printf("\n%s\n", Buffer);
	while (r_len > 0)
	{ 
		r_len = recv(s2, Buffer, sizeof(Buffer), 0);
		if (r_len == 0)
			break;
		realr_len += r_len;
		printf("\n%s\n", Buffer);
	}
	
	printf("recv() %d bytes of data\n",realr_len);

	fp = fopen("test.txt" ,"w");
	memset(&lookingFor, 0, sizeof(lookingFor));
	point = strstr(Buffer, "\r\n\r\n");	
	printf("File downloaded\n",realr_len);
	fprintf(fp, point+4);
	WSACleanup();
	closesocket(s2);	
	return 0;
}