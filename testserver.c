#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include<sys/sendfile.h>
#define PORT 4444
#define SIZE 1024
char webpage[] =
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html; charset=UTF-8\r\n\r\n"
    "<!DOCTYPE html>\r\n"
    "<html><head><title>SwordArtOnline</title>\r\n"
    "<style>body {background-color: blue}</style></head>\r\n"
    "<body><center><h1>StarBurstStream</h1><br>\r\n"
    "<img src=\"favicon.jpg\"></center></body></html>\r\n";
void write_file(int sockfd,char*buf){
    int n;
    FILE *fp;
    char *filename = "GetFileFromClient.txt";
    //char buffer[SIZE];

    fp = fopen(filename, "w");
    if(fp==NULL){
        perror("[-]Error in creating file...");
        exit(1);
    }
    /*while(1){
        n = recv(sockfd, buffer, SIZE, 0);
        if(n<=0){
            break;
            return;
        }
        printf("w,");
        fprintf(fp, "%s", buffer);
        bzero(buffer, SIZE);
    }*/
    //printf("strlen:%ld\n", strlen(buf));

    fwrite(buf, 1, strlen(buf), fp);
    bzero(buf, SIZE);
    fclose(fp);
    return;
}
int main()
{
    struct sockaddr_in serverAddr, newAddr;
    socklen_t sin_len = sizeof(newAddr);
    int sockfd, newSocket;
    char buf[2048];
    int fdimg,ret;
    pid_t childpid;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<0){
        printf("[-]Error in connection.\n");
		exit(1);
    }
    printf("[+]Server Socket is created.\n");
    memset(&serverAddr, '\0', sizeof(serverAddr));
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &open, sizeof(int));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("[-]Error in binding.\n");
		exit(1);
	}
	printf("[+]Bind to port %d\n", 4444);

	if(listen(sockfd, 10) == 0){
		printf("[+]Listening....\n");
	}else{
		printf("[-]Error in listening.\n");
	}

    while(1){
        newSocket = accept(sockfd, (struct sockaddr *)&newAddr, &sin_len);
        if(newSocket==-1){
            perror("connection failed....\n");
            continue;
        }
        printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));

        if(!fork()){
            /* child process */
            close(sockfd);
            memset(buf, 0, 2048);
            read(newSocket, buf, 2047);

            //printf("%s\n", buf);

            if(!strncmp(buf,"GET /favicon.jpg",16)){
                //printf("this_1\n");
                fdimg = open("favicon.jpg", O_RDONLY);
                sendfile(newSocket, fdimg, NULL, 100000);
                close(fdimg);
            }else if(!strncmp(buf,"GET /",5)){
                write(newSocket, webpage, sizeof(webpage) - 1);
                //printf("browser\n");
            }
            else{
                //printf("buf==%s\n", buf);
                write_file(newSocket,buf);
                printf("[+]Data written in the text file\n");
            }
            close(newSocket);
            printf("closing...\n");
            exit(0);
        }
        /*parent process*/
        close(newSocket);
    }

    return 0;
}