#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <src/socket_client.h>

//#################### SOCKET CLIENT #############################

/*
  Paul Glotfelter

  11/02/2014
  
  A socket "client."  Intended to interface with a Java TCP server. 
  All of the functions have built-in error checking.
*/

//################################################################


//#################### HELPER FUNCTIONS  #########################

/* Error 

   Calls 'perror' with the message then exits the program.
*/

void error(const char *msg) {

  perror(msg);
  exit(0);
}

//################################################################


/*
  CONN:  Attempts to connect to server w/ hostname @ port.  Returns a
  socket file descriptor 
*/

int conn(char * hostname, int port) {

  int socketfd;

  struct sockaddr_in serv_addr;
  struct hostent *server;

  socketfd = socket(AF_INET, SOCK_STREAM, 0);

  //Ensure that host can be connected to...
  if (socketfd < 0) {
    error("ERROR opening socket");
  }

  server = gethostbyname(hostname);

  if (server == NULL) {
    fprintf(stderr,"ERROR, no such host\n");
    exit(0);
  }

  //Connect to the SocketServer.  Look into these structs a little
  //more so that I understand what's going on!
    
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
  serv_addr.sin_port = htons(port);

  if (connect(socketfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    error("ERROR connecting");
  }

  return socketfd;
}

/*

  DISCONN:  Closes a socket given a socket file descriptor
*/

int disconn(int socketfd) {

  return close(socketfd);
}

/*
  
  SEND: Given a socket file descriptor, sends a message
*/

int send(int socketfd, char * message) {

  int e = write(socketfd, message, strlen(message));       

  if (e < 0) {
    error("ERROR writing to socket");
  }

  return e;
}

