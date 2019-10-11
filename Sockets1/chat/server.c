
// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 9090
int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread, valread2;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char buffer2[1024] = {0};
    char *hello1 = "EL servidor ha leido 1 mensaje ";
    char *hello = "EL servidor ha leido los 2 mensajes ";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))//opt y sizeof sirven para pasarle parametros al Socket
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    valread = read( new_socket , buffer, 1024);  //read y send son bloqueantes, el proceso se bloquea hasta que haya algo que ller en el buffer
    send(new_socket , hello1 , strlen(hello) , 0 );
    valread2 = read( new_socket , buffer2, 1024);
    //printf("%s\n",buffer );
    send(new_socket , hello , strlen(hello) , 0 );
    printf("He leido dos mensajes\n");
    return 0;
}
