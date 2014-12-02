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

//#define IP_ADDR "192.168.1.10"

int main(int argc, char** argv)
{
  int socketHandle;

  // Create Socket
  if((socketHandle = socket(PF_INET, SOCK_STREAM, IPPROTO_IP)) < 0)
  {
    close(socketHandle);
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in socketInfo;
  int portNumber = 6600;

  // Initialize structure to zero
  bzero(&socketInfo, sizeof(sockaddr_in));

  // Set up socketInfo
  socketInfo.sin_family = PF_INET;
  socketInfo.sin_addr.s_addr = htonl(INADDR_ANY);
  socketInfo.sin_port = htons(portNumber);

  // Bind the socket
  if(bind(socketHandle, (struct sockaddr *) &socketInfo, sizeof(struct sockaddr_in)) < 0)
  {
    close(socketHandle);
    perror("bind");
    exit(EXIT_FAILURE);
  }

  listen(socketHandle, 1);

  int socketConnection;
  if((socketConnection = accept(socketHandle, NULL, NULL)) < 0)
  {
    close(socketHandle);
    exit(EXIT_FAILURE);
  }

  int rc = 0;
  char buf[1024];

  rc = recv(socketConnection, buf, 512, 0);
  buf[rc] = (char) NULL;

  std::cout << "Number of bytes read: " << rc << std::endl;
  std::cout << "Recieved: " << buf << std::endl;

  return 0;
}
