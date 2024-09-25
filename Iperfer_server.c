#include <stdio.h>            /*  standard I/O  */
#include <stdlib.h>           /*  standard library */
#include <string.h>           /*  string library */
#include <sys/socket.h>       /*  socket definitions */
#include <sys/types.h>        /*  socket types       */
#include <arpa/inet.h>        /*  inet (3) funtions         */
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/select.h>
#include <time.h>

#define  BACKLOG   5
int Iperfer_server(int port)
{
    int  sockfd, new_fd; // listen on sock_fd, new connection on new_fd
    struct sockaddr_in   my_addr; // my address information
    struct sockaddr_in   their_addr; // connector’s address information
    socklen_t sin_size;

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    my_addr.sin_family = AF_INET; // host byte order
    my_addr.sin_port = htons(port); // short, network byte order
    my_addr.sin_addr.s_addr = INADDR_ANY; // automatically fill with my IP
    memset(&(my_addr.sin_zero), 0, 8); // zero the rest of the struct

    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
        perror("bind");
        exit(1);
    }
    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }
    int numbytes=0;

    float total_recv_bytes = 0, total_recv_Kbytes = 0, total_recv_Mbytes = 0;
    int recv_bytes = 0;
    time_t t1,t2;
    while(1) {                     // main accept() loop
    
        sin_size = sizeof(struct sockaddr_in);
        if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1) {
            perror("accept");
            continue;
        }
        
        if (send(new_fd, "Hello, world!\n", 14, 0) == -1)
            perror("send");

        char inputBuffer[1];
        t1= time(NULL);
        while(1){
            recv_bytes = recv(new_fd, inputBuffer, sizeof(inputBuffer), 0);
            /*printf("Get:%s\n", inputBuffer);
            printf("recv_bytes:%d\n", recv_bytes);*/
            total_recv_bytes+=recv_bytes;
            if(inputBuffer[0] == '1')
                break;
        }
        t2= time(NULL);
        total_recv_Kbytes = total_recv_bytes / 1000;
        total_recv_Mbytes = total_recv_Kbytes / 1000;
        printf("received=%.3f, KB rate=%.3f Mbps\n",total_recv_Kbytes, total_recv_Mbytes/(t2-t1));
        //printf("(t2-t1)=%ld\n",(t2-t1)); 
      
        close(new_fd); 
        break;
    } // end of while

    return 0;
}

