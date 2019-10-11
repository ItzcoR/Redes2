#include <stdio.h> /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), bind(), and connect() */
#include <arpa/inet.h> /* for sockaddr_in and inet_ntoa() */
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXPENDING 5 /* Maximum outstanding connection requests */
#define RCVBUFSIZE 32 /* Size of receive buffer */

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

  printf("Server Socket: %d\n", servSock);

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
  int recvMsgSize;
  printf("Client Socket: %d\n", clntSocket);
  /* Receive message from client */
  if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
    DieWithError("First recv() failed") ;
  /* Send received string and receive again until end of transmission */
  while (recvMsgSize > 0) /* zero indicates end of transmission */
  {
    /* Echo message back to client */
    if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
      DieWithError("send() failed");
    /* See if there is more data to receive */
    if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
      DieWithError("Extra recv() failed") ;
  }
  close(clntSocket); /* Close client socket */
}


int main(int argc, char *argv[])
{

  /* Error handling function */
  /* TCP client handling function */

  int servSock; /* Socket descriptor for server */
  int clntSock; /* Socket descriptor for client */
  struct sockaddr_in echoServAddr; /* Local address */
  struct sockaddr_in echoClntAddr; /* Client address */
  unsigned short echoServPort; /* Server port */
  unsigned int clntLen; /* Length of client address data structure */

  if (argc != 2) /* Test for correct number of arguments */
  {
    fprintf(stderr, "Usage: %s <Server Port>\n", argv[0]) ;
    exit(1);
  }

  echoServPort = atoi(argv[1]); /* First arg: local port */
  /* Create socket for incoming connections */
  servSock = CreateTCPServerSocket(echoServPort);

  //if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
  //  DieWithError( "socket () failed") ;
  printf("Server Socket: %d\n", servSock);

  // Construct local address structure
  /*memset(&echoServAddr, 0, sizeof(echoServAddr)); // Zero out structure
  echoServAddr.sin_family = AF_INET; // Internet address family
  echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); // Any incoming interface
  echoServAddr.sin_port = htons(echoServPort); // Local port

  // Bind to the local address
  if (bind(servSock, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr)) < 0)
    DieWithError ( "bind () failed");

  // Mark the socket so it will listen for incoming connections
  if (listen(servSock, MAXPENDING) < 0)
    DieWithError("listen() failed") ;*/

  for (;;) /* Run forever */
  {
    /* Set the size of the in-out parameter */
    //clntLen = sizeof(echoClntAddr);
    /* Wait for a client to connect */
    //if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr,&clntLen)) < 0)
    //  DieWithError("accept() failed");
    /* clntSock is connected to a client! */
    //printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));
    clntSock = AcceptTCPConnection(servSock);
    printf("Client Socket: %d\n", clntSock);
    HandleTCPClient (clntSock) ;
  }
  /* NOT REACHED */
}
