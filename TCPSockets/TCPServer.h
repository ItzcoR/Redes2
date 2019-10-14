#include <stdio.h> /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), bind(), and connect() */
#include <arpa/inet.h> /* for sockaddr_in and inet_ntoa() */
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXPENDING 5 /* Maximum outstanding connection requests */
#define RCVBUFSIZE 255 /* Size of receive buffer */

void DieWithError(char *errorMessage) // Funcion de manejo de errores
{
  perror ( errorMessage) ;
  exit(1);
}

int CreateTCPServerSocket(unsigned short port)
{
  int sock; //Socket a crear
  struct sockaddr_in echoServAddr; // Estruntura con los datos del server
  if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    DieWithError( "socket () failed") ;

  /* Construct local address structure */
  memset(&echoServAddr, 0, sizeof(echoServAddr)); /* Zero out structure */
  echoServAddr.sin_family = AF_INET; /* Internet address family */
  echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
  echoServAddr.sin_port = htons(port); /* Local port */

  /* Bind to the local address */
  if (bind(sock, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr)) < 0)
    DieWithError ( "bind () failed");

  /* Mark the socket so it will listen for incoming connections */
  if (listen(sock, MAXPENDING) < 0)
    DieWithError("listen() failed") ;

  return sock;
}

int AcceptTCPConnection( int servSock){
  int clntSock;
  struct sockaddr_in echoClntAddr; /* Client address struct */
  unsigned int clntLen; /* Length of client address data structure */

  //printf("Server Socket: %d\n", servSock);

  /* Set the size of the in-out parameter */
  clntLen = sizeof(echoClntAddr);

  /* Wait for a client to connect */
  if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr,&clntLen)) < 0)
    DieWithError("accept() failed");

  /* clntSock is connected to a client! */
  printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));
  return clntSock;
}

void HandleTCPClient(int clntSocket)
{
  char echoBuffer[RCVBUFSIZE];
  char stringtoSend[RCVBUFSIZE];
  int recvMsgSize;
  printf("Client Socket: %d\n", clntSocket);
  

  while (1) // @ indicates end of transmission
  {
    /* Receive message from client */
    if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
      DieWithError("First recv() failed") ;
    printf("Client Socket: %d\n", clntSocket);
    printf("\nServer Recived:\n" );
    printf("%s\n",echoBuffer); /* Print the echo buffer */
    printf("Message to send to client:\n");
    fgets(stringtoSend,RCVBUFSIZE,stdin);
    if (stringtoSend[0] == '@'){
      printf("Entered break condition");
      break;
    }

    // Echo message back to client
    if (send(clntSocket, stringtoSend, sizeof(stringtoSend), 0) < 0)
      DieWithError("send() failed");
    // See if there is more data to receive
    //if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
    //  DieWithError("Extra recv() failed") ;
  }
  close(clntSocket); /* Close client socket */
}
