#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

//#################### SOCKET CLIENT #############################

/*
  Paul Glotfelter
  
  A socket "client."  Intended to interface with a Java TCP server. 
  All of the functions have built-in error checking.
*/

//################################################################


//#################### HELPER FUNCTIONS  #########################

/* Error 

   Calls 'perror' with the message then exits the program
*/

void error(const char *msg) {

  perror(msg);
  exit(0);
}

//################################################################


int connect(char * hostname, int port) {

  int socketfd;

  struct sockaddr_in serv_addr;
  struct hostent *server;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  //Ensure that host can be connected to...
  if (sockfd < 0) {
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
  serv_addr.sin_port = htons(portno);

  if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    error("ERROR connecting");
  }

  return sockfd;
}

int disconnect(int socketfd) {

  return close(socketfd);
}

int send(int socketfd, char * message) {

  int e = write(socketfd, message, strlen(message));       

  if (e < 0) {
    error("ERROR writing to socket");
  }

  return e;
}


/*
int main(int argc, char *argv[]) {

  int sockfd, portno, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;

  char buffer[256];  //Buffer for sending messages

    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

    portno = atoi(argv[2]);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

	//Ensure that host can be connected to...
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    //Connect to the SocketServer.  Look into these structs a little
    //more so that I understand what's going on!
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    //Double to send to Java server

    double sending = 0.0;

    while (1) {

      //Here, the VRPN client could just receive the message and then
      //write it onto the socket...would be an easy way to do the communications

    	bzero(buffer,256);

	sleep(1);

	sprintf(buffer, "%lf", sending);

    	n = write(sockfd,buffer,strlen(buffer));

        if (n < 0) { 
          error("ERROR writing to socket");
        }
    }

    close(sockfd);
    return 0;
}

*/

int main(int argc, char * argv[]) {

  if (argc < 3) {
    fprintf(stderr,"usage %s hostname port\n", argv[0]);
    exit(0);
  }

  int port = atoi(argv[1]);
  char * hostname = argv[2];

  int socketfd = connect(hostname, port);
  
  char * msg = "How are you?";

  send(socketfd, msg);

  disconnect(socketfd);

  return 0;
}

