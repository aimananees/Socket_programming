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
#define BUFFER 1024

main(int argc,char **argv){

	struct sockaddr_in remote_server;
	int sock;
	int input1[BUFFER];
	int digit1;
	int digit2;
	int operator;
	

	if((sock=socket(AF_INET,SOCK_STREAM,0)) == ERROR){
		perror("socket");
		exit(-1);
	}
	remote_server.sin_family=AF_INET;
	remote_server.sin_port=htons(atoi(argv[2]));
	remote_server.sin_addr.s_addr=inet_addr(argv[1]);
	bzero(&remote_server.sin_zero,8);

	if((connect(sock,(struct sockaddr *)&remote_server,sizeof(struct sockaddr_in))) == ERROR){
		perror("connect");
		exit(-1);
	}


	
		printf("Input in the form a+b: ");
		scanf("%[^\n]s",input1);
	
		write(sock,input1,sizeof(input1));

	close(sock);
}