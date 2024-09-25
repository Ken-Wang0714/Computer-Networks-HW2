#include <stdio.h>            /*  standard I/O  */
#include <stdlib.h>           /*  standard library */
#include <string.h>           /*  string library */
#include <sys/socket.h>       /*  socket definitions */
#include <sys/types.h>        /*  socket types       */
#include <arpa/inet.h>        /*  inet (3) funtions         */
#include <unistd.h>
#include <time.h>

#define MAXDATASIZE 100 // max number of bytes we can get at once
//Iperfer -c -h <server hostname> -p <server port> -t <time>
int Iperfer_client(char *ip,char *port,char *set_time)
{
    int sockfd, numbytes;
    char buf[MAXDATASIZE];
    struct sockaddr_in server_addr; // connector’s address information
    int port_int = atoi(port);
    int set_time_int = atoi(set_time);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
       perror("socket");
       exit(1);
    }
    server_addr.sin_family = AF_INET; // host byte order
    server_addr.sin_port = htons(port_int); // short, network byte order
    server_addr.sin_addr.s_addr = inet_addr(ip);
    memset(&(server_addr.sin_zero), 0, 8); // zero the rest of the struct
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
       perror("connect");
       exit(1);
    }

    if ((numbytes=recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
       perror("recv");
       exit(1);
    }

    int set_numbytes=0;
    float total_send_numMbytes = 0,total_send_numbytes = 0,total_send_numKbytes = 0;
    time_t t1,t2;
    t1 = time(NULL);
    t2 = t1 + set_time_int;
    while(t1 < t2){
      t1 = time(NULL);
      set_numbytes=send(sockfd, "0", 1, 0);
      total_send_numbytes+=set_numbytes;
    }
    set_numbytes=send(sockfd, "1", 1, 0);
    total_send_numbytes += set_numbytes;
    total_send_numKbytes = total_send_numbytes / 1000;
    total_send_numMbytes = total_send_numKbytes / 1000;
    printf("sent=%.3f KB, rate=%.3f Mbps\n",total_send_numKbytes,total_send_numMbytes/set_time_int);

    close(sockfd);
    return 0;
}

