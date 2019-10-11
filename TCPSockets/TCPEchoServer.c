#include "TCPServer.h"
#include <pthread.h> 

void *ThreadMain(void *args);

 /* Structura de argumentos que pasarle al hilo */
 struct ThreadArgs{
   int clntSock;
 };

int main(int argc, char *argv[])
{

  int servSock; /* Socket descriptor for server */
  int clntSock; /* Socket descriptor for client */
  unsigned short echoServPort; /* Server port */
  unsigned int clntLen; /* Length of client address data structure */
  pthread_t threadID;
  struct ThreadArgs *threadArgs;

  if (argc != 2) /* Test for correct number of arguments */
  {
    fprintf(stderr, "Usage: %s <Server Port>\n", argv[0]) ;
    exit(1);
  }

  echoServPort = atoi(argv[1]); /* First arg: local port */
  /* Create socket for incoming connections */
  servSock = CreateTCPServerSocket(echoServPort);
  //printf("Server Socket: %d\n", servSock);

  for (;;) /* Run forever */
  {
    clntSock = AcceptTCPConnection(servSock);
    /*Crear locaciones de memoria para el cliente*/
    if ((threadArgs = (struct ThreadArgs *) malloc(sizeof(struct ThreadArgs))) == NULL)
      DieWithError("malloc() failed");

    printf("Client Socket: %d\n", clntSock);
    threadArgs -> clntSock = clntSock;

    /* Crear hilo del cliente */
    if (pthread_create(&threadID, NULL, ThreadMain, (void *)threadArgs) != 0)
      DieWithError("pthread_create() failed");
    printf("with thread %ld\n", (long int) threadID);

  }
  /* NOT REACHED */
}

void *ThreadMain(void *threadArgs){
  int clntSock; /* descriptor del socket para la conexion del cliente*/

  /* Nos aseguramos de que los recursos del hilo sean liberados al return de la funcions */
  pthread_detach(pthread_self());

  /* Extraer descriptor de archivo del socket de la estructura de argumentos */
  clntSock = ((struct ThreadArgs *) threadArgs) -> clntSock;
  printf("1 Client Socket in thread struct: %d\n", clntSock);

  free(threadArgs); //Liberamos la memoria
  HandleTCPClient(clntSock);
  return(NULL);
}
