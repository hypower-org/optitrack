#ifndef SOCKET_CLIENT_H
#define SOCKET_CLIENT_H

int conn(char * hostname, int port);
int disconn(int socketfd);
int send(int socketfd, char * message);

#endif
