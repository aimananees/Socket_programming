#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<errno.h>
#include<strings.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<ctype.h>
#include <assert.h>
#define ERROR -1
#define MAX_CLIENTS 2
#define MAX_DATA 1024
#define BUFFER 1024

main(int argc, char **argv){
	struct sockaddr_in server;
	struct sockaddr_in client;
	int sock;
	int cli;
	//int ans;
	int sockaddr_len=sizeof(struct sockaddr_in);
	//For receiving
	char data[MAX_DATA];
	//For sending
	int input;

	if((sock=socket(AF_INET,SOCK_STREAM,0)) == ERROR){
		perror("Server Socket");
		exit(-1);
	}

	server.sin_family=AF_INET;
	server.sin_port=htons(atoi(argv[1]));
	server.sin_addr.s_addr=INADDR_ANY;
	bzero(&server.sin_zero,8);

	if((bind(sock,(struct sockaddr *)&server,sockaddr_len)) == ERROR){
		perror("Bind");
		exit(-1);
	}

	if((listen(sock,MAX_CLIENTS)) == ERROR){
		perror("listen");
		exit(-1);
	}

	if((cli=accept(sock,(struct sockaddr *)&client,&sockaddr_len)) == ERROR){
			perror("accept");
			exit(-1);
	}
	printf("Client connected: ");
	int data_len=1;
	
		read(cli,data,MAX_DATA);
		printf("%c\n",data[0]);
		printf("%c\n",data[1]);
		printf("%c\n",data[2]);

		int num1, num2;
        char op;
        num1=data[0]-'0';
        num2=data[2]-'0';
        printf("%d\n",num1);
		printf("%c\n",data[1]);
		printf("%d\n",num2);
        double ans;
        switch (data[1]) {
            case '+':
                ans = num1+num2;
                break;
            case '-':
                ans = num1-num2;
                break;
            case '*':
                ans = num1*num2;
                break;
            case '/':
               
                    ans = (double)num1/num2;
                break;
            case '%':
                    ans = num1%num2;
                break;
        }

        printf("%f",ans);
    
        //write(connfd,message,sizeof(message));


	close(sock);

}
