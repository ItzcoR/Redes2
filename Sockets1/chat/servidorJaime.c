// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#define PORT 8586

void *accept_conn( void *ptr ){
  char buffer[256];
  bzero(buffer, 256);
  int n;
  char* hello= "Saludos desde el server";
  int param = (intptr_t) ptr;
   memset(buffer, 0, 256);  
  n = recv((int) param, buffer, 256,0);
  if (n < 0) perror("ERROR Reading from socket");
  printf("%s\n\n**********\n\n", buffer);

  n = send((int)param, hello , strlen(hello), 0);
  if (n < 0)
    perror("ERROR Writing to socket");
}

int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread, valread2;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[256] = {0};
    int tamanioAux;
    char buffer2[256] = {0};
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
    while (1) {
      int *new_socket;
      new_socket = malloc(sizeof(int));
      *new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
      if (*new_socket<0)
      {
          perror("accept");
          exit(EXIT_FAILURE);
      }
      pthread_t *thread;
      thread = (pthread_t *) malloc(sizeof(pthread_t));
      pthread_create(thread, NULL, accept_conn, (void *)(intptr_t) *new_socket);
    }

    /*while(1){
        valread = read( new_socket , buffer, 1024);  //read y send son bloqueantes, el proceso se bloquea hasta que haya algo que ller en el buffer
        if(buffer2[0] == '.' || buffer[0] == '.')
        {
            printf("conexion terminada");
            break;
        }*/

        //valread = read( new_socket , buffer2, 1024);  //read y send son bloqueantes, el proceso se bloquea hasta que haya algo que ller en el buffer
        //send(new_socket , hello , strlen(hello) , 0 );
        //printf("%s\n%s\n",buffer2,buffer);
        //memset(buffer, 0, strlen(buffer));
        //memset(buffer2, 0, strlen(buffer2));
    //}
    return 0;
}
