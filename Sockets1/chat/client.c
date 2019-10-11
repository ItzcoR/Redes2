// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#define PORT 8586

int main(int argc, char const *argv[])
{
	int sock = 0, valread, valread2;
	FILE *fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t re;
	char *fin=".250";
	int sd=1;
	fp= fopen("RandomNums0.txt","r");
	struct sockaddr_in serv_addr;
	char *hello = "Hello from client";
	char buffer[256] = {0};
	char buffer2[256] = {0};
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}
	/*if((fp= fopen("RandomNums0.txt","rb"))==NULL){
		printf("Error! opening file");
		// Program exits if the file pointer returns NULL.
		return 1;
	}*/
	while (1) {
		printf("%d\n",sd );
		if (sd == 0) {
				printf("Entré a la condicion de break%d\n",sd );
			break;
		}
		printf("%d\n",sd );
		send(sock , hello , strlen(hello) , 0 );
		valread= recv( sock , buffer, 256,0);
		//scanf("%d" , &sd);
		//printf("%d\n",sd );
		sleep(2);
	}
	//send(sock , hello , strlen(hello) , 0 );

	//while ((re = getline(&line, &len, fp) != -1)) {
		//printf("%s",line );
		//send(sock, strlen(line),sizeof(int),0);
		//send(sock, line, strlen(line),0);
		//sleep(1);
		//valread= recv( sock , buffer, 256,0);
		//valread= recv( sock , buffer, 1024,0);	//	printf("\n", );
		//send(sock, hello, strlen(hello),0);
		//sleep(1);
		//valread= recv( sock , buffer, 1024,0);
//	}
//	send(sock,fin,strlen(fin),0);

	//send(sock , hello , strlen(hello) , 0 );
	//printf("Enviando linea\n");
	//valread = read( sock , buffer, 1024);
	//printf("%s\n",buffer );
	//send(sock , hello , strlen(hello) , 0 );
	//printf("Hello message 2 sent\n");
	//valread = read( sock , buffer, 1024,0);
	//printf("%s\n",buffer );
	//scanf("Esperando input\n" );
	return 0;
}
