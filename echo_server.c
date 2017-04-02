#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<errno.h>
#include<strings.h>
#include<unistd.h>
#include<arpa/inet.h>

#define ERROR -1
#define MAX_CLIENTS 2
#define MAX_DATA 1024

main(int argc, char **argv){
	struct sockaddr_in server;
	struct sockaddr_in client;
	int sock;
	int cli;
	int sockaddr_len=sizeof(struct sockaddr_in);
	int data_len;
	char data[MAX_DATA];

	if((sock=socket(AF_INET,SOCK_STREAM,0)) == ERROR){
		perror("Server Socket");
		exit(-1);
	}

	server.sin_family=AF_INET;
	server.sin_port = htons(atoi(argv[1]));
	server.sin_addr.s_addr = INADDR_ANY;
	bzero(&server.sin_zero,8);

	if((bind(sock,(struct sockaddr *)&server,sockaddr_len)) == ERROR){
		perror("Bind");
		exit(-1);
	}

	if((listen(sock,MAX_CLIENTS)) == ERROR){
		perror("listen");
		exit(-1);
	}

	while(1){
		if((cli=accept(sock,(struct sockaddr *)&client,&sockaddr_len)) == ERROR){
			perror("accept");
			exit(-1);
		}

		data_len=1;
		while(data_len){
			data_len=recv(cli,data,MAX_DATA,0);
			if(data_len){
				send(cli,data,data_len,0);
				data[data_len]='\0';
				printf("Sent: %s\n",data);
			}
		}

		printf("Client Disconnected\n");
		close(cli);
	}
	

}