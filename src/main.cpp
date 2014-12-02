// Tyler Travis - A01519795
// Clint Fernelius - A

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <netdb.h>
#include <errno.h>
#include <fstream>

#define PORTNUM 6600

int main(int argc, char** argv)
{
  // Remember to turn off the firewall

  FILE* fout = fopen("message.txt", "w");

  fprintf(fout,"Testing...\n");

  struct sockaddr_in client, server;
  int mySocket;
  socklen_t socksize = sizeof(sockaddr_in);

  bzero(&server, sizeof(sockaddr_in));
  server.sin_family = PF_INET;
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port = htons(PORTNUM);

  mySocket = socket(PF_INET, SOCK_STREAM, 0);
  if (mySocket < 0)
  {
    printf("Error: Error creating socket.\n");
    exit(0);
  }

  if (bind(mySocket, (struct sockaddr *) &server, sizeof(struct sockaddr)) < 0)
  {
    printf("Error: Could not bind socket to port.\n");
    exit(0);
  }

  if (listen(mySocket, 1))
  {
    printf("Error: Bad listening on socket.\n");
    exit(0);
  }

  int connected = accept(mySocket, (struct sockaddr *) &client, &socksize);

  int receive;
  char buffer[256];

  while (connected)
  {
    receive = 0;
    do
    {
      receive = recv(connected, buffer, sizeof(buffer)-1, 0);
      buffer[receive] = (char)NULL;
      std::cout << buffer;
    }while(receive != 0);

    close(connected);
    connected = accept(mySocket, (struct sockaddr *) &client, &socksize);
  }

  fclose(fout);
  return 0;
}
