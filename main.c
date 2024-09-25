#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Iperfer_server.h"
#include "Iperfer_client.h"

int main(int argc, char *argv[]) {
  char client_buf[]={"-c"};
  char server_buf[]={"-s"};
  int port = 0;
  
  if (strncmp(argv[1], client_buf, 2) == 0)
  {
    //printf("You are client\n");
    //Iperfer -c -h <server hostname> -p <server port> -t <time>
    if (argc != 8)
    {
      printf("Error: missing or additional arguments\n");
    }
    port = atoi(argv[5]);
    if ( port < 1024 || port > 65535)
    {
      printf("Error: port number must be in the range 1024 to 65535\n");
      return -1;
    }
    char *ip = argv[3];
    char *port = argv[5];
    char *time = argv[7];
    Iperfer_client(ip, port, time);
  }else if (strncmp(argv[1], server_buf, 2) == 0){
    //printf("You are server\n");
    //Iperfer -s -p <listen port>
    if (argc != 4)
    {
      printf("Error: missing or additional arguments\n");
    }
    port = atoi(argv[3]); 
    if ( port < 1024 || port > 65535)
    {
      printf("Error: port number must be in the range 1024 to 65535\n");
      return -1;
    }
    Iperfer_server(port);
  }
  return 0;
}