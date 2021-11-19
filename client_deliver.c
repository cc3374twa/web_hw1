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
#define SIZE 2048
void send_file(FILE*fp,int sockfd){
    char data[SIZE] = {0};
    while(fgets(data,SIZE,fp)!=NULL){
        if(send(sockfd,data,sizeof(data),0)==-1){
            perror("[-]Error in sending data.");
            exit(1);
        }
        bzero(data, SIZE);
    }
}
int main(){
    int port = 4444;
    int clientSocket, ret;
    struct sockaddr_in serverAddr;
    char buffer[2048];
    FILE *fp;
    char *filename = "sendthisfile.txt";
    
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Client Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Connected to Server.\n");
    printf("Hold on Client _ input any word to terminate and send filetext:  ");
	scanf("%s", &buffer[0]);
    fp = fopen(filename, "r");
    if(fp==NULL){
            perror("[-]Error in reading file...");
            exit(1);
    }

    send_file(fp, clientSocket);
    printf("[+]file data send successfully\n");

    close(clientSocket);
    printf("[+]disconnected from the server\n");

}   