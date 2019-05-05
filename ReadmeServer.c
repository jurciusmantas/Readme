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
	int headerLenght;
	
	char Buffer[4096];
	char* lookingFor = "To download file click the link below:<br /><a href=";
	char* point;
	char* temp;
	char downloadLink[70];
	
	WSAStartup(MAKEWORD(2,2),&data);
	
	if (argc != 2 || strstr(argv[1], "s000.tinyupload.com/index.php?file_id=") == NULL)
	{
		printf("Please provide a tinyupload download link!\n");
		return 0;
	}
	
	if ( (he = gethostbyname( "s000.tinyupload.com" ) ) == NULL)
	{		
		printf("ERROR : gethostbyname() failed : %d\n" , WSAGetLastError());
		return 1;
	}
			
	addr_list = (struct in_addr **) he->h_addr_list;
		
	for(i = 0; addr_list[i] != NULL; i++) 
	{
		strcpy(ip , inet_ntoa(*addr_list[i]) );
	}
		
	printf("s000.tinyupload.com resolved to : %s\n", ip);
			
	memset(&servaddr, 0, sizeof(servaddr));
	servaddrlen = sizeof(servaddr);
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(ip);
	servaddr.sin_port = htons(80);
	
	if ((s = socket(AF_INET,SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("ERROR: creating socket failed : %d\n" , WSAGetLastError());
		//should set read set and return from if...
		exit(1);
	}		
		
	printf("Connecting to server...\n");
	if (connect(s, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
	{
		printf("ERROR: Connect with server failed : %d\n" , WSAGetLastError());
		//should set read set and return from if...
		exit(1);
	}			
	printf("Connected!\n");
	
	printf("Sending GET...\n");
	temp = strstr(argv[1], "/index");
	strcpy(Buffer, "GET ");
	strcat(Buffer, temp);
	strcat(Buffer, " HTTP/1.1\r\nHost: s000.tinyupload.com\r\n\r\n");
	send(s, Buffer, strlen(Buffer),0);
	printf("GET Sent!\n");
	
	printf("Receiving from server...\n");
	r_len = recv(s, Buffer, sizeof(Buffer), 0);
	realr_len = r_len;
	
	//show header
	headerLenght = getHeaderLenght(Buffer);
	if (headerLenght == 0)
	{
		printf("ERROR: Could not find header lenght!\n");
		exit(1);
	}
	printf("\nHEADER : -------------------------\n");
	fwrite(Buffer, 1, headerLenght, stdout);
	printf("\nEND OF HEADER --------------------\n\n");
	
	//get download link
	while (r_len > 0)
	{ 
		r_len = recv(s, Buffer, sizeof(Buffer), 0); 
		realr_len += r_len;
		point = strstr(Buffer, lookingFor);
		if(point != NULL)
		{
			strncpy(downloadLink, point+strlen(lookingFor)+1, 69);
			downloadLink[69] = '\0';
			break;
		}
	}
	
	printf("recv() %d bytes of data\n",realr_len);
	printf("--\nDownload link - %s\n--\n", downloadLink);
	closesocket(s);	
	
	/*******************/
	//FILE DOWNLOAD
	/*******************/
	
	printf("Starting file download\n",realr_len);
	
	if ((s2 = socket(AF_INET,SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("ERROR: creating socket failed : %d\n" , WSAGetLastError());
		exit(1);
	}		
		
	printf("Connecting to server...\n");
	if (connect(s2, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
	{
		printf("ERROR: Connect with server failed : %d\n" , WSAGetLastError());
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
	
	memset(&Buffer, 0, sizeof(Buffer));
	printf("Receiving from server...\n");
	point = NULL;
	realr_len = 0;
	r_len = recv(s2, Buffer, sizeof(Buffer), 0);
	if (r_len == 0 || strstr(Buffer, "HTTP/1.1 200 OK") == NULL)
	{
		printf("ERROR: Receiving from server.\n");
		exit(1);
	}
	realr_len += r_len;
	
	//header
	headerLenght = getHeaderLenght(Buffer);
	if (headerLenght == 0)
	{
		printf("ERROR: Could not find header lenght!");
		exit(1);
	}
	printf("\nHEADER : -------------------------\n");
	fwrite(Buffer, 1, headerLenght, stdout);
	printf("\nEND OF HEADER --------------------\n\n");
	
	// find filename from buffer
	point = NULL;
	point = strstr(Buffer, "filename=");
	if (point == NULL)
	{
		printf("ERROR: Could not find filename in header\n");
		exit(1);
	}
	
	int size = 0;
	// get filename
	for(;;)
	{
		if (*(point+10+size) != '"')
			size++;
		else 
			break;
	}
	
	char filename[size];
	strncpy(filename, point+10, size);
	filename[size] = '\0';
	
	// open file
	fp = fopen(filename, "wb");
	
	//write content
	point = NULL;
	point = strstr(Buffer, "\r\n\r\n");
	fwrite(point+4, sizeof(char), r_len - headerLenght - 4, fp);
	
	while (r_len > 0)
	{
		memset(&Buffer, 0, sizeof(Buffer));
		r_len = recv(s2, Buffer, sizeof(Buffer), 0);
		if (r_len == 0)
			break;
		realr_len += r_len;
		
		fwrite(Buffer, sizeof(char), r_len, fp);
	}
	
	printf("recv() %d bytes of data\n",realr_len);
	WSACleanup();
	closesocket(s2);
	fclose(fp);
	return 0;
}

int getHeaderLenght(char Buffer[])
{
	char* point = strstr(Buffer, "\r\n\r\n");
	if (point == NULL)
		return 0;
	
	int lenght = strlen(Buffer) - strlen(point);
	return lenght;
}