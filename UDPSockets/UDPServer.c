#include <stdio.h> /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), bind(), and connect() */
#include <arpa/inet.h> /* for sockaddr_in and inet_ntoa() */
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ECHOMAX 255

void DieWithError(char *errorMessage)
{
  perror ( errorMessage) ;
  exit(1);
}

int main(int argc, char *argv[])
{

  int sock; /*Local Socket descriptor */
  struct sockaddr_in echoServAddr; /* Echo server address */
  struct sockaddr_in echoClntAddr;  /*Source adress for echo*/
  unsigned int cliAddrLen; /* Length of client address data structure */
  unsigned short echoServPort; /* Server port */
  char echoBuffer[ECHOMAX];
  int recvMsgSize;

  if (argc != 2) /* Test for correct number of arguments */
  {
    fprintf(stderr, "Usage: %s <UDP Server Port>\n", argv[0]) ;
    exit(1);
  }

  echoServPort = atoi(argv[1]); /* First arg: local port */
  /* Create socket for sending  reciving datagrams */
  if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    DieWithError(" socket () failed") ;

  /* Construct the local address structure */
  memset(&echoServAddr, 0, sizeof(echoServAddr)); /* Zero out structure */
  echoServAddr.sin_family = AF_INET; /* Internet address family */
  echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Server IP address */
  echoServAddr.sin_port = htons(echoServPort); /* Server port */
  //printf("Server Socket: %d\n", servSock);

  //Bind to local address
  if(bind(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) <0)
    DieWithError("bind() failed");
  for (;;) /* Run forever */
  {
    //Set size of the in-out parameter
    if ((recvMsgSize = recvfrom(sock,echoBuffer, ECHOMAX, 0,(struct sockaddr *)&echoClntAddr, &cliAddrLen))<0)
      DieWithError("recv_from() failed");
    printf("Manejando cliente:  %s\n", inet_ntoa (echoClntAddr.sin_addr) );
    if

  }
  /* NOT REACHED */
}
