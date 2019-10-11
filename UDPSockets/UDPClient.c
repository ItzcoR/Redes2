#include <stdio.h> /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h> /* for sockaddr_in and inet_addr() */
#include <stdlib.h> /* for atoi() */
#include <string.h> /* for memset() */
#include <unistd.h> /* for close() */
#define RCVBUFSIZE 32
#define MAX_LIMIT 32
#define ECHOMAX 255
void DieWithError(char *errorMessage);

/* Size of receive buffer */

/* Error handling function */

int main(int argc, char *argv[])
{
  int sock; /* Socket descriptor */
  struct sockaddr_in echoServAddr; /* Echo server address */
  struct sockaddr_in fromAddr;  /*Source adress for echo*/
  unsigned short echoServPort;  /* Echo server port */
  unsigned short fromSize;      /* In-out del tamaño de direccion para recvfrom()*/
  char *servlP;                 /* Server IP address (dotted quad) */
  char *echoString;             /* String to send to echo server */
  char echoBuffer[ECHOMAX+1];  /* Buffer for echo string */
  int echoStringLen;   /* Length of string to echo */
  int respStringLen;/* Longitud de la respuesta recivida*/


  if ((argc< 3) || (argc> 4)) /* Test for correct number of arguments */
  {
    fprintf(stderr, "Usage: %s <Server IP> <Echo Word> [<Echo Port>]\n",  argv[0]);
    exit(1);
  }
  servlP = argv[1] ;/* First arg' server IP address (dotted quad) */
  echoString = argv[2] ;/* Second arg' string to echo */


  if (argc == 4)
    echoServPort = atoi(argv[3]); /* Use given port, if any */
  else
    echoServPort = 7;

    /* Create a datagram/UDP socket */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
      DieWithError(" socket () failed") ;
    /* Construct the server address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr)); /* Zero out structure */
    echoServAddr.sin_family = AF_INET; /* Internet address family */
    echoServAddr.sin_addr.s_addr = inet_addr(servlP); /* Server IP address */
    echoServAddr.sin_port = htons(echoServPort); /* Server port */
    /* Establish the connection to the echo server */
    if (bind(sock, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr)) < 0)
      DieWithError ( "bind () failed");

    echoStringLen = strlen(echoString) ; /* Determine input length */

    /* Send the string to the server */
    if (sendto(sock, echoString, echoStringLen, 0) != echoStringLen)
      DieWithError("sendto() sent a different number of bytes than expected");

    /* Receive the same string back from the server */
    fromSize = sizeof(fromAddr);

    if ((respStringLen = recvfrom(sock, echoBuffer, ECHOMAX, 0,
       (struct sockaddr *)&echoServAddr,sizeof(echoServAddr))) != echoStringLen)
      DieWithError("recvfrom() failed ");

    if(echoServAddr.sin_addr.s_addr != fromAddr.sin_addr.s_addr){
      fprintf(stderr, "Error: received a packet from an unknown source.\n", );
      exit(1);
    }
    echoBuffer[respStringLen] = '\0'; /* Terminate the string! */
    printf("Received: %s\n", echoBuffer); /* Print the echo buffer */

    printf("\n"); /* Print a final linefeed */
    getchar();
    close(sock);
    exit(0);
}
void DieWithError(char *errorMessage)
{
  perror ( errorMessage) ;
  exit(1);
}
