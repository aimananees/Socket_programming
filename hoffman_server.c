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
#define BUFFER 1024

main(int argc, char **argv){
	struct sockaddr_in server;
	struct sockaddr_in client;
	int sock;
	int cli;
	FILE *fp;
	int s[80],f[80];
	int c1,c2,c4,c8;
	int i;
	int sockaddr_len=sizeof(struct sockaddr_in);
	

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

	printf("\n client connected");
	read(cli,f,80);
	printf("\nthe data\n");
	for(i=0;i<12;i++)	
	{
	printf("%d",f[i]);
	}
	c1=(f[11]^f[9]^f[7]^f[5]^f[3]^f[1]);
	c2=(f[10]^f[9]^f[6]^f[5]^f[2]^f[1]);
	c4=(f[8]^f[7]^f[6]^f[5]^f[0]);
	c8=(f[4]^f[3]^f[2]^f[1]^f[0]);
	if(!(c1==0&&c2==0&&c4==0&&c8==0))
		printf("\nerror bit :%d%d%d%d\n",c8,c4,c2,c1);
	else
		printf("no error\n");
	close(cli);
}


	
